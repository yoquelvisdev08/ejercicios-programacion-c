"""
Módulo para generar documentos PDF con los resultados de la compilación.
"""

import os
import io
import re
from datetime import datetime
from reportlab.lib import colors
from reportlab.lib.pagesizes import letter, A4
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, Image as ReportLabImage, PageBreak, Table, TableStyle
from reportlab.platypus import Flowable, KeepTogether, CondPageBreak
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.units import inch, cm
from reportlab.lib.enums import TA_CENTER, TA_LEFT, TA_JUSTIFY
from reportlab.pdfgen import canvas
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from PIL import Image as PILImage
import traceback

from config.settings import PDF_CONFIG, EXERCISE_TYPES, GUI_CONFIG

class CppLogo(Flowable):
    """Un flowable personalizado para dibujar el logo de C++."""
    
    def __init__(self, width=1*inch, height=1*inch, background_color="#007AFF"):
        Flowable.__init__(self)
        self.width = width
        self.height = height
        self.background_color = background_color
    
    def draw(self):
        # Guardar estado
        self.canv.saveState()
        
        # Dibujar círculo de fondo
        self.canv.setFillColor(colors.HexColor(self.background_color))
        center_x = self.width / 2
        center_y = self.height / 2
        radius = min(self.width, self.height) / 2.2
        self.canv.circle(center_x, center_y, radius, fill=1)
        
        # Dibujar texto "C++"
        self.canv.setFillColor(colors.white)
        self.canv.setFont("Helvetica-Bold", radius * 0.8)
        text_width = self.canv.stringWidth("C++", "Helvetica-Bold", radius * 0.8)
        text_height = radius * 0.8 * 0.4  # Aproximación de la altura
        self.canv.drawString(center_x - text_width/2, center_y - text_height/2, "C++")
        
        # Restaurar estado
        self.canv.restoreState()

class PDFGenerator:
    """Clase para generar documentos PDF con los resultados de la compilación."""
    
    def __init__(self, output_path):
        """Inicializa el generador de PDF."""
        self.output_path = output_path
        self.elements = []
        self.programs = []  # Lista para almacenar información de programas para el índice
        self.setup_styles()
        
        # Patrones para la coloración de sintaxis de C++
        self.cpp_syntax = {
            'keywords': [
                'auto', 'break', 'case', 'catch', 'class', 'const', 'continue', 'default', 
                'delete', 'do', 'else', 'enum', 'explicit', 'export', 'extern', 'false', 
                'for', 'friend', 'goto', 'if', 'inline', 'namespace', 'new', 'operator', 
                'private', 'protected', 'public', 'return', 'sizeof', 'static', 'struct', 
                'switch', 'template', 'this', 'throw', 'true', 'try', 'typedef', 'typename',
                'using', 'virtual', 'volatile', 'while', 'and', 'or', 'not', 'int', 'float',
                'double', 'char', 'bool', 'void', 'unsigned', 'signed', 'long', 'short'
            ],
            'preprocessor': [
                '#include', '#define', '#ifndef', '#ifdef', '#endif', '#pragma', '#if', '#else', '#elif'
            ],
            'stl': [
                'std::', 'vector', 'string', 'map', 'set', 'list', 'deque', 'queue', 'stack',
                'algorithm', 'iostream', 'fstream', 'sstream', 'iomanip', 'array', 'tuple'
            ]
        }
        
        # Crear el documento con márgenes reducidos
        self.doc = SimpleDocTemplate(
            output_path,
            pagesize=A4,  # A4 es ligeramente más alto que letter, optimizando espacio
            rightMargin=0.5*inch,  # Reducir márgenes
            leftMargin=0.5*inch,
            topMargin=0.5*inch,
            bottomMargin=0.5*inch,
            title="Recopilación de Programas C++",
            author="Compilador C++ Avanzado",
            subject="Programas C++ compilados",
            creator="Compilador C++ Avanzado"
        )
    
    def setup_styles(self):
        """Configura los estilos del documento."""
        self.styles = getSampleStyleSheet()
        
        # Estilo para el título principal
        self.styles.add(ParagraphStyle(
            name='CustomTitle',
            parent=self.styles['Title'],
            fontSize=24,
            spaceAfter=10,  # Reducido
            alignment=TA_CENTER
        ))
        
        # Estilo para subtítulos
        self.styles.add(ParagraphStyle(
            name='CustomHeading',
            parent=self.styles['Heading1'],
            fontSize=14,  # Reducido
            spaceBefore=10,  # Reducido
            spaceAfter=5,  # Reducido
            textColor=colors.HexColor(GUI_CONFIG['theme']['primary'])
        ))
        
        # Estilo para código
        self.styles.add(ParagraphStyle(
            name='CodeStyle',
            parent=self.styles['Code'],
            fontSize=9,  # Reducido
            fontName='Courier',
            spaceBefore=5,  # Reducido
            spaceAfter=5,  # Reducido
            leftIndent=10  # Reducido
        ))
        
        # Estilo para texto normal
        self.styles.add(ParagraphStyle(
            name='CustomBody',
            parent=self.styles['Normal'],
            fontSize=10,  # Reducido
            spaceBefore=3,  # Reducido
            spaceAfter=3  # Reducido
        ))
        
        # Estilo para el índice
        self.styles.add(ParagraphStyle(
            name='IndexEntry',
            parent=self.styles['Normal'],
            fontSize=11,
            leftIndent=10,
            spaceBefore=2,
            spaceAfter=2
        ))
        
        # Estilo para encabezados de sección
        self.styles.add(ParagraphStyle(
            name='SectionHeader',
            parent=self.styles['Heading2'],
            fontSize=12,
            spaceBefore=10,
            spaceAfter=5,
            textColor=colors.HexColor(GUI_CONFIG['theme']['primary'])
        ))
        
        # Estilo compacto para info de programa
        self.styles.add(ParagraphStyle(
            name='ProgramInfo',
            parent=self.styles['Normal'],
            fontSize=9,
            textColor=colors.HexColor(GUI_CONFIG['theme']['text_secondary'])
        ))
        
        # Añadir portada
        self.add_cover_page()
    
    def add_cover_page(self):
        """Añade una portada al documento con información introductoria e índice."""
        # Logo C++
        logo = CppLogo(width=2*inch, height=2*inch)
        self.elements.append(logo)
        self.elements.append(Spacer(1, 10))
        
        # Título principal
        self.elements.append(Paragraph(
            "Recopilación de Programas C++",
            self.styles['CustomTitle']
        ))
        
        # Añadir información del autor
        self.styles.add(ParagraphStyle(
            'Author',
            parent=self.styles['CustomBody'],
            fontSize=12,
            spaceBefore=5,
            spaceAfter=10,
            alignment=TA_CENTER,
            textColor=colors.HexColor(GUI_CONFIG['theme']['primary'])
        ))
        
        self.elements.append(Paragraph(
            "Desarrollado por: Yoquelvis Jorge Abreu",
            self.styles['Author']
        ))
        
        # Añadir estilo para la introducción
        self.styles.add(ParagraphStyle(
            'Introduction',
            parent=self.styles['CustomBody'],
            fontSize=10,
            spaceBefore=10,
            spaceAfter=10,
            leftIndent=20,
            rightIndent=20,
            alignment=TA_JUSTIFY,
            leading=14
        ))
        
        # Texto de introducción (reducido)
        intro_text = """
        <strong>Acerca de esta herramienta:</strong><br/>
        Esta aplicación es un compilador y visualizador avanzado para programas C++, 
        que automatiza el proceso de compilación, ejecución y documentación.<br/><br/>
        
        <strong>Características principales:</strong><br/>
        • Compilación automática con g++<br/>
        • Ejecución con captura de pantalla<br/>
        • Generación de PDF con código y resultados<br/>
        • Análisis del código<br/>
        • Procesamiento de múltiples archivos
        """
        
        self.elements.append(Paragraph(
            intro_text,
            self.styles['Introduction']
        ))
        
        # Fecha de generación
        self.styles.add(ParagraphStyle(
            'GenerationDate',
            parent=self.styles['CustomBody'],
            fontSize=9,
            spaceBefore=10,
            spaceAfter=10,
            alignment=TA_CENTER,
            textColor=colors.HexColor(GUI_CONFIG['theme']['text_secondary'])
        ))
        
        self.elements.append(Paragraph(
            f"Generado el {datetime.now().strftime('%d/%m/%Y a las %H:%M:%S')}",
            self.styles['GenerationDate']
        ))
        
        # Reservar espacio para el índice (se completará después)
        self.elements.append(Paragraph(
            "Índice de Programas",
            self.styles['SectionHeader']
        ))
        self.elements.append(Spacer(1, 10))
        self.index_position = len(self.elements)  # Marcar posición del índice
        
        # Añadir un separador de página
        self.elements.append(PageBreak())
    
    def update_index(self):
        """Actualiza el índice con los programas añadidos."""
        # Si no hay programas, no hacer nada
        if not self.programs:
            return
        
        # Crear entradas de índice
        index_elements = []
        for i, (program_name, program_type) in enumerate(self.programs, 1):
            icon = EXERCISE_TYPES.get(program_type, EXERCISE_TYPES['default'])['icon']
            entry_text = f"{i}. {icon} {program_name}"
            index_elements.append(Paragraph(
                entry_text,
                self.styles['IndexEntry']
            ))
            index_elements.append(Spacer(1, 2))
        
        # Insertar en la posición guardada
        self.elements[self.index_position:self.index_position] = index_elements
    
    def add_program(self, program_info, style_type=None):
        """Añade un programa al PDF con su código y captura de pantalla."""
        try:
            # Extraer información básica
            if isinstance(program_info, dict):
                program_name = program_info.get('name', 'Programa sin nombre')
            else:
                program_name = str(program_info)
            
            # Registrar para el índice
            self.programs.append((program_name, style_type or 'default'))
            
            # Contenedor para mantener elementos juntos cuando sea posible
            program_elements = []
            
            # Encabezado con ícono según tipo
            icon = EXERCISE_TYPES.get(style_type, EXERCISE_TYPES['default'])['icon']
            header_text = f"{icon} Programa: {program_name}"
            program_elements.append(Paragraph(
                header_text,
                self.styles['CustomHeading']
            ))
            
            # Información del programa en formato compacto
            if isinstance(program_info, dict) and program_info.get('type'):
                info_text = f"Tipo: {program_info.get('type', 'No especificado')} | "
                if 'complexity' in program_info:
                    info_text += f"Complejidad: {program_info.get('complexity', 'N/A')}/100 | "
                if 'requires_input' in program_info:
                    info_text += f"Requiere entrada: {'Sí' if program_info.get('requires_input') else 'No'}"
                
                program_elements.append(Paragraph(
                    info_text,
                    self.styles['ProgramInfo']
                ))
            
            program_elements.append(Spacer(1, 5))
            
            # Código fuente
            if program_info.get('source_code'):
                # Obtener el código original
                source_code = program_info['source_code']
                
                # Crear un estilo para el encabezado del código
                self.styles.add(ParagraphStyle(
                    name='CodeHeader',
                    parent=self.styles['SectionHeader'],
                    fontSize=12,
                    fontName='Courier-Bold',
                    textColor=colors.black,
                    alignment=TA_LEFT,
                    spaceBefore=10,
                    spaceAfter=2,
                    backColor=colors.white,
                    borderWidth=0,
                    borderPadding=4
                ))
                
                # Crear un estilo para las instrucciones de copia
                self.styles.add(ParagraphStyle(
                    name='CopyInstructions',
                    parent=self.styles['ProgramInfo'],
                    fontSize=9,
                    alignment=TA_LEFT,
                    textColor=colors.HexColor('#777777'),
                    spaceBefore=0,
                    spaceAfter=5,
                    backColor=colors.white,
                    borderWidth=0,
                    borderPadding=0
                ))
                
                # Estilo para código con formato de syntax highlighting
                self.styles.add(ParagraphStyle(
                    name='SyntaxHighlightedCode',
                    parent=self.styles['CodeStyle'],
                    fontSize=11,
                    fontName='Courier',
                    spaceBefore=15,  # Espacio para instrucciones
                    spaceAfter=10,
                    leftIndent=10,
                    rightIndent=10,
                    backColor=colors.white,
                    borderWidth=1,
                    borderColor=colors.HexColor("#CCCCCC"),
                    borderPadding=10,
                    borderRadius=0,
                    leading=14,
                    wordWrap=False  # Mantener el formato exacto
                ))
                
                # Aplicar syntax highlighting al código
                lines = source_code.split('\n')
                highlighted_lines = []
                
                for line in lines:
                    # Escapar HTML
                    escaped_line = line.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')
                    # Aplicar coloración de sintaxis 
                    highlighted_line = self.apply_cpp_syntax_highlighting(escaped_line)
                    highlighted_lines.append(highlighted_line)
                
                # Unir líneas con breaks HTML
                highlighted_code = '<br/>'.join(highlighted_lines)
                
                # Título distintivo para la sección de código
                program_elements.append(Paragraph(
                    "/* Código Fuente */",
                    self.styles['CodeHeader']
                ))
                
                # Instrucciones claras para copiar
                program_elements.append(Paragraph(
                    "Para usar este código: Seleccione todo (Ctrl+A / Cmd+A) → Copie (Ctrl+C / Cmd+C)",
                    self.styles['CopyInstructions']
                ))
                
                # Crear párrafo con el código con syntax highlighting
                code_para = Paragraph(
                    highlighted_code,
                    self.styles['SyntaxHighlightedCode']
                )
                
                # Añadir el código al documento
                program_elements.append(code_para)
                program_elements.append(Spacer(1, 15))
            
            # Captura de pantalla optimizada
            if program_info.get('screenshot'):
                screenshot_path = program_info['screenshot']
                try:
                    # Verificar si el archivo existe
                    if not os.path.exists(screenshot_path):
                        # Si no existe el PNG, intentar con JPG
                        jpg_path = screenshot_path.replace('.png', '.jpg')
                        if os.path.exists(jpg_path):
                            screenshot_path = jpg_path
                        else:
                            raise FileNotFoundError(f"No se encuentra la captura de pantalla: {screenshot_path}")
                    
                    # Verificar el tamaño del archivo
                    if os.path.getsize(screenshot_path) < 100:
                        raise ValueError(f"La captura de pantalla es demasiado pequeña: {os.path.getsize(screenshot_path)} bytes")
                    
                    print(f"Agregando imagen desde: {screenshot_path} (Tamaño: {os.path.getsize(screenshot_path)} bytes)")
                    
                    # Optimizar la imagen para el PDF
                    with PILImage.open(screenshot_path) as img:
                        # Convertir a RGB si es necesario
                        if img.mode not in ('RGB', 'RGBA'):
                            print(f"Convirtiendo imagen de modo {img.mode} a RGB")
                            img = img.convert('RGB')
                        
                        # Redimensionar si es muy grande
                        original_width, original_height = img.size
                        max_width = 6.5 * inch  # Ancho máximo (ajustado a márgenes)
                        if original_width > max_width:
                            ratio = max_width / original_width
                            new_width = int(original_width * ratio)
                            new_height = int(original_height * ratio)
                            img = img.resize((new_width, new_height), PILImage.LANCZOS)
                            print(f"Imagen redimensionada de {original_width}x{original_height} a {new_width}x{new_height}")
                        
                        # Optimizar calidad
                        img_buffer = io.BytesIO()
                        img.save(img_buffer, format='JPEG', quality=85, optimize=True)
                        img_buffer.seek(0)
                        
                        # Añadir la imagen optimizada
                        program_elements.append(Paragraph(
                            "🖼️ Resultado de la Ejecución:",
                            self.styles['SectionHeader']
                        ))
                        
                        img_width = min(original_width, int(max_width))
                        img_height = int((img_width / original_width) * original_height)
                        
                        img = ReportLabImage(img_buffer, width=img_width, height=img_height)
                        program_elements.append(img)
                        program_elements.append(Spacer(1, 10))
                
                except Exception as e:
                    print(f"Error al procesar la imagen: {str(e)}")
                    traceback.print_exc()
                    program_elements.append(Paragraph(
                        f"Error al procesar la captura de pantalla: {str(e)}",
                        self.styles['Normal']
                    ))
            
            # Salida del programa en formato compacto
            if program_info.get('output'):
                # Evaluar longitud de la salida
                output_text = program_info['output']
                if len(output_text) > 1000:  # Si es muy largo, truncar
                    output_text = output_text[:1000] + "...\n[Resultado truncado por extensión]"
                
                program_elements.append(Paragraph(
                    "📊 Información de Compilación:",
                    self.styles['SectionHeader']
                ))
                
                output_para = Paragraph(
                    f"<pre>{output_text.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')}</pre>",
                    self.styles['CodeStyle']
                )
                program_elements.append(output_para)
            
            # Usar KeepTogether para intentar mantener el contenido unido cuando sea posible
            # Pero dividirlo en secciones lógicas para permitir saltos de página si es necesario
            
            # Sección 1: Encabezado y código
            self.elements.append(KeepTogether(program_elements[:4]))  # Encabezado, info y título de código
            
            # El resto de elementos se añaden directamente
            self.elements.extend(program_elements[4:])
            
            # Separador entre programas (más compacto)
            self.elements.append(Spacer(1, 20))
            self.elements.append(Paragraph(
                "─" * 80,  # Línea horizontal como separador
                self.styles['CustomBody']
            ))
            self.elements.append(Spacer(1, 10))
            
        except Exception as e:
            print(f"Error al añadir programa al PDF: {str(e)}")
            traceback.print_exc()
            self.elements.append(Paragraph(
                f"Error al procesar el programa: {str(e)}",
                self.styles['Normal']
            ))
    
    def save(self):
        """Guarda el documento PDF final."""
        try:
            print(f"\nGenerando PDF en: {self.output_path}")
            
            # Actualizar el índice antes de construir
            self.update_index()
            
            # Asegurar que el directorio de salida existe
            os.makedirs(os.path.dirname(self.output_path), exist_ok=True)
            
            # Intentar generar el PDF directamente en la ruta final
            try:
                self.doc.build(self.elements)
                
                # Verificar si el PDF se creó correctamente
                if os.path.exists(self.output_path) and os.path.getsize(self.output_path) > 0:
                    print(f"PDF generado correctamente: {self.output_path}")
                    print(f"Tamaño: {os.path.getsize(self.output_path) / 1024:.2f} KB")
                    return True
                else:
                    print(f"El PDF no se generó correctamente en {self.output_path}")
            except Exception as direct_error:
                print(f"Error al generar el PDF directamente: {direct_error}")
                traceback.print_exc()
                
                # Si falló la generación directa, intentar con archivo temporal
                temp_path = f"{self.output_path}.temp.pdf"
                temp_doc = SimpleDocTemplate(
                    temp_path,
                    pagesize=A4,
                    rightMargin=0.5*inch,
                    leftMargin=0.5*inch,
                    topMargin=0.5*inch,
                    bottomMargin=0.5*inch
                )
                
                try:
                    temp_doc.build(self.elements)
                    
                    # Si llegamos aquí, la generación fue exitosa
                    # Verificar si se creó el archivo temporal
                    if os.path.exists(temp_path) and os.path.getsize(temp_path) > 0:
                        # Renombrar al nombre final
                        if os.path.exists(self.output_path):
                            try:
                                os.remove(self.output_path)
                            except Exception as rm_error:
                                print(f"Error al eliminar archivo PDF existente: {rm_error}")
                                # Si no podemos eliminar, usamos un nombre alternativo
                                self.output_path = f"{self.output_path.replace('.pdf', '')}_new.pdf"
                                print(f"Usando nombre alternativo: {self.output_path}")
                        
                        # Copiar el archivo temporal al final
                        import shutil
                        shutil.copy2(temp_path, self.output_path)
                        
                        # Eliminar el temporal
                        try:
                            os.remove(temp_path)
                        except:
                            pass
                            
                        print(f"PDF generado mediante archivo temporal: {self.output_path}")
                        print(f"Tamaño: {os.path.getsize(self.output_path) / 1024:.2f} KB")
                        return True
                    else:
                        print(f"Error: El archivo temporal {temp_path} no se creó correctamente")
                except Exception as temp_error:
                    print(f"Error al generar el PDF con archivo temporal: {temp_error}")
                    traceback.print_exc()
            
            # Verificar una última vez si el PDF existe
            if os.path.exists(self.output_path) and os.path.getsize(self.output_path) > 0:
                print(f"PDF encontrado a pesar de los errores: {self.output_path}")
                return True
                
            return False
            
        except Exception as e:
            print(f"Error al generar el PDF: {e}")
            traceback.print_exc()
            
            # Intentar recuperación de errores
            try:
                # Verificar si tenemos elementos
                if not self.elements:
                    print("No hay elementos para generar el PDF")
                    return False
                
                # Intentar generar un PDF simplificado como último recurso
                recovery_path = self.output_path.replace('.pdf', '_recovery.pdf')
                print(f"Intentando recuperación en: {recovery_path}")
                
                # Filtrar elementos problemáticos (como imágenes que podrían estar causando errores)
                simplified_elements = []
                for element in self.elements:
                    if not isinstance(element, ReportLabImage):
                        simplified_elements.append(element)
                
                # Generar el PDF simplificado
                doc = SimpleDocTemplate(
                    recovery_path,
                    pagesize=A4,
                    rightMargin=0.5*inch,
                    leftMargin=0.5*inch,
                    topMargin=0.5*inch,
                    bottomMargin=0.5*inch
                )
                
                doc.build(simplified_elements)
                
                if os.path.exists(recovery_path) and os.path.getsize(recovery_path) > 0:
                    print(f"Se generó un PDF de recuperación: {recovery_path}")
                    print("Nota: Este PDF puede no contener todas las imágenes")
                    # Copiar el archivo de recuperación al nombre original
                    import shutil
                    shutil.copy2(recovery_path, self.output_path)
                    return True
                else:
                    # Una última verificación
                    if os.path.exists(self.output_path) and os.path.getsize(self.output_path) > 0:
                        print(f"PDF encontrado a pesar de todos los errores: {self.output_path}")
                        return True
                    return False
                
            except Exception as recovery_error:
                print(f"Error en la recuperación del PDF: {recovery_error}")
                # Verificación final
                if os.path.exists(self.output_path) and os.path.getsize(self.output_path) > 0:
                    print(f"PDF encontrado después de todos los intentos: {self.output_path}")
                    return True
                return False

    def save_pdf(self):
        """Alias para el método save para mantener compatibilidad."""
        return self.save()

    def apply_cpp_syntax_highlighting(self, code_line):
        """Aplica coloración de sintaxis a una línea de código C++.
        
        Args:
            code_line (str): Línea de código C++ escapada para HTML
            
        Returns:
            str: Línea con coloración de sintaxis aplicada
        """
        # Ya debe estar escapada para HTML (& < >)
        
        # Colorear comentarios (tienen prioridad sobre todo lo demás)
        if '//' in code_line:
            comment_pos = code_line.find('//')
            comment = code_line[comment_pos:]
            code_line = code_line[:comment_pos] + f'<font color="#6A9955">{comment}</font>'
            return code_line
            
        # Colorear strings
        code_line = re.sub(r'(".*?")', r'<font color="#CE9178">\1</font>', code_line)
        
        # Colorear caracteres
        code_line = re.sub(r"('.')", r'<font color="#CE9178">\1</font>', code_line)
        
        # Colorear directivas de preprocesador
        for directive in self.cpp_syntax['preprocessor']:
            if directive in code_line:
                code_line = code_line.replace(directive, f'<font color="#C586C0">{directive}</font>')
                break
        
        # Colorear palabras clave
        for keyword in self.cpp_syntax['keywords']:
            # Asegurar que no se colorean partes de otras palabras
            pattern = r'\b' + keyword + r'\b'
            code_line = re.sub(pattern, f'<font color="#569CD6">{keyword}</font>', code_line)
        
        # Colorear tipos/clases de STL
        for stl_item in self.cpp_syntax['stl']:
            if stl_item in code_line:
                code_line = code_line.replace(stl_item, f'<font color="#4EC9B0">{stl_item}</font>')
        
        # Colorear números
        code_line = re.sub(r'\b(\d+)\b', r'<font color="#B5CEA8">\1</font>', code_line)
        
        return code_line

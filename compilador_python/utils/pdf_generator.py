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
        self.code_elements = []  # Nueva lista para elementos de código
        self.results_elements = []  # Nueva lista para elementos de resultados
        self.analysis_elements = []  # Nueva lista para elementos de análisis
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
        """Configura los estilos para el documento PDF."""
        self.styles = getSampleStyleSheet()
        
        # Crear estilos personalizados
        self.styles.add(ParagraphStyle(
            name='DocumentTitle',
            parent=self.styles['Title'],
            fontName='Helvetica-Bold',
            fontSize=24,
            leading=30,
            alignment=TA_CENTER,
            spaceAfter=20
        ))
        
        self.styles.add(ParagraphStyle(
            name='ChapterTitle',
            parent=self.styles['Title'],
            fontName='Helvetica-Bold',
            fontSize=18,
            leading=24,
            alignment=TA_LEFT,
            spaceAfter=12,
            textColor=colors.HexColor("#2C3E50")
        ))
        
        self.styles.add(ParagraphStyle(
            name='CustomHeading',
            parent=self.styles['Heading1'],
            fontName='Helvetica-Bold',
            fontSize=16,
            leading=20,
            spaceBefore=12,
            spaceAfter=6,
            textColor=colors.HexColor("#2C3E50")
        ))
        
        self.styles.add(ParagraphStyle(
            name='ProgramTitle',
            parent=self.styles['Heading2'],
            fontName='Helvetica-Bold',
            fontSize=14,
            leading=18,
            spaceBefore=10,
            spaceAfter=5,
            textColor=colors.HexColor("#2C3E50")
        ))
        
        self.styles.add(ParagraphStyle(
            name='SectionHeader',
            parent=self.styles['Heading3'],
            fontName='Helvetica-Bold',
            fontSize=12,
            leading=16,
            spaceBefore=8,
            spaceAfter=4,
            textColor=colors.HexColor("#34495E")
        ))
        
        self.styles.add(ParagraphStyle(
            name='CustomBody',
            parent=self.styles['Normal'],
            fontSize=11,
            leading=14,
            spaceBefore=6,
            spaceAfter=6
        ))
        
        self.styles.add(ParagraphStyle(
            name='ProgramInfo',
            parent=self.styles['Normal'],
            fontSize=10,
            leading=12,
            spaceBefore=2,
            spaceAfter=6,
            textColor=colors.HexColor("#555555")
        ))
        
        self.styles.add(ParagraphStyle(
            name='CodeStyle',
            parent=self.styles['Code'],
            fontName='Courier',
            fontSize=9,
            leading=12,
            leftIndent=20,
            spaceBefore=6,
            spaceAfter=6,
            backColor=colors.HexColor("#F5F5F5"),
            borderWidth=1,
            borderColor=colors.HexColor("#DDDDDD"),
            borderPadding=5,
            borderRadius=3
        ))
        
        self.styles.add(ParagraphStyle(
            name='TableHeader',
            parent=self.styles['Normal'],
            fontSize=10,
            leading=12,
            alignment=TA_CENTER,
            fontName='Helvetica-Bold',
            textColor=colors.HexColor("#FFFFFF"),
            backColor=colors.HexColor("#3498DB")
        ))
        
        self.styles.add(ParagraphStyle(
            name='IndexEntry',
            parent=self.styles['Normal'],
            fontSize=11,
            leading=14,
            leftIndent=10,
            spaceBefore=2,
            spaceAfter=2,
            textColor=colors.HexColor("#2980B9")
        ))
        
        self.styles.add(ParagraphStyle(
            name='FooterStyle',
            parent=self.styles['Normal'],
            fontSize=8,
            textColor=colors.gray,
            alignment=TA_CENTER
        ))
        
        # Configurar el documento
        self.doc = SimpleDocTemplate(
            self.output_path,
            pagesize=A4,
            rightMargin=0.5*inch,
            leftMargin=0.5*inch,
            topMargin=0.5*inch,
            bottomMargin=0.5*inch
        )
    
    def create_cover_page(self):
        """Crea la página de portada y retorna los elementos."""
        elements = []
        
        # Espacio superior reducido
        elements.append(Spacer(1, 0.5*inch))  # Reducido de 1 inch a 0.5 inch
        
        # Título principal
        elements.append(Paragraph(
            "<b>INFORME DE PROGRAMAS C++</b>",
            self.styles['DocumentTitle']
        ))
        
        # Fecha y hora de generación
        current_datetime = datetime.now().strftime("%d/%m/%Y %H:%M:%S")
        elements.append(Paragraph(
            f"Generado el {current_datetime}",
            self.styles['CustomBody']
        ))
        
        # Resumen de contenido (más compacto)
        elements.append(Spacer(1, 0.2*inch))  # Reducido de 0.5 inch a 0.2 inch
        n_programs = len(self.programs)
        elements.append(Paragraph(
            f"Este informe contiene {n_programs} programa{'s' if n_programs != 1 else ''} C++ con sus respectivos códigos fuente y resultados de ejecución.",
            self.styles['CustomBody']
        ))
        
        # Descripción del contenido (más compacto)
        elements.append(Spacer(1, 0.2*inch))  # Reducido de 0.5 inch a 0.2 inch
        elements.append(Paragraph(
            "<b>Contenido del informe:</b>",
            self.styles['SectionHeader']
        ))
        elements.append(Paragraph(
            "• Sección 1: Códigos fuente de todos los programas<br/>• Sección 2: Resultados de ejecución de los programas<br/>• Sección 3: Análisis técnico y oportunidades de mejora",
            self.styles['CustomBody']
        ))
        
        # Nota explicativa (más compacta)
        elements.append(Spacer(1, 0.2*inch))  # Reducido de 0.5 inch a 0.2 inch
        elements.append(Paragraph(
            "<i>Nota: El informe está organizado por secciones para facilitar la lectura y análisis. La sección de análisis técnico incluye evaluación detallada de cada programa y recomendaciones de mejora.</i>",
            self.styles['ProgramInfo']
        ))
        
        return elements
    
    def update_index(self):
        """Crea o actualiza el índice con los programas procesados."""
        if not self.programs:
            return
        
        # Añadir título del índice (más compacto)
        self.elements.append(Spacer(1, 0.1*inch))  # Añade un pequeño espacio
        self.elements.append(Paragraph(
            "Índice de Programas",
            self.styles['CustomHeading']
        ))
        
        # Añadir descripción más compacta
        self.elements.append(Paragraph(
            "La siguiente tabla muestra los programas incluidos en este informe:",
            self.styles['CustomBody']
        ))
        
        self.elements.append(Spacer(1, 0.1*inch))  # Reducido de 0.2 inch a 0.1 inch
        
        # Datos para la tabla de índice
        data = [["Nº", "Programa", "Tipo"]]
        
        for i, program in enumerate(self.programs, 1):
            row = [
                str(i),
                program['name'],
                program['type'].capitalize()
            ]
            data.append(row)
        
        # Crear tabla
        col_widths = [0.5*inch, 4*inch, 1.5*inch]
        table = Table(data, colWidths=col_widths)
        
        # Estilo de tabla (igual que antes)
        table_style = TableStyle([
            ('BACKGROUND', (0, 0), (-1, 0), colors.HexColor("#3498DB")),
            ('TEXTCOLOR', (0, 0), (-1, 0), colors.whitesmoke),
            ('ALIGN', (0, 0), (-1, 0), 'CENTER'),
            ('FONTNAME', (0, 0), (-1, 0), 'Helvetica-Bold'),
            ('FONTSIZE', (0, 0), (-1, 0), 11),
            ('BOTTOMPADDING', (0, 0), (-1, 0), 8),
            ('TOPPADDING', (0, 0), (-1, 0), 8),
            ('BACKGROUND', (0, 1), (-1, -1), colors.white),
            ('TEXTCOLOR', (0, 1), (-1, -1), colors.black),
            ('ALIGN', (0, 1), (0, -1), 'CENTER'),
            ('ALIGN', (1, 1), (1, -1), 'LEFT'),
            ('ALIGN', (2, 1), (2, -1), 'CENTER'),
            ('FONTNAME', (0, 1), (-1, -1), 'Helvetica'),
            ('FONTSIZE', (0, 1), (-1, -1), 10),
            ('BOTTOMPADDING', (0, 1), (-1, -1), 6),
            ('GRID', (0, 0), (-1, -1), 0.5, colors.lightgrey),
            ('VALIGN', (0, 0), (-1, -1), 'MIDDLE'),
        ])
        
        # Aplicar el estilo a la tabla
        table.setStyle(table_style)
        
        # Añadir la tabla al documento
        self.elements.append(table)
        self.elements.append(Spacer(1, 0.2*inch))  # Reducido de 0.3 inch a 0.2 inch
    
    def add_program(self, program_info, style_type=None):
        """Añade un programa al PDF con su código y captura de pantalla."""
        try:
            program_name = program_info.get('name', 'Programa sin nombre')
            
            # Agregar a la lista de programas para el índice
            self.programs.append({
                'name': program_name,
                'type': style_type or 'general'
            })
            
            # Crear elementos para la sección de código (más compactos)
            code_elements = []
            
            # Título del programa
            code_title = f"Programa: {program_name}"
            code_elements.append(Paragraph(
                code_title,
                self.styles['ProgramTitle']
            ))
            
            # Información del programa
            code_elements.append(Paragraph(
                f"Tipo: {style_type or 'General'}",
                self.styles['ProgramInfo']
            ))
            
            # Obtener el código original
            source_code = program_info['source_code']
            
            # Crear un estilo para el encabezado del código (con menos espacio)
            self.styles.add(ParagraphStyle(
                name='CodeHeader',
                parent=self.styles['SectionHeader'],
                fontSize=12,
                fontName='Courier-Bold',
                textColor=colors.black,
                alignment=TA_LEFT,
                spaceBefore=5,  # Reducido de 10 a 5
                spaceAfter=2,
                backColor=colors.white,
                borderWidth=0,
                borderPadding=4
            ))
            
            # Crear un estilo para las instrucciones de copia (con menos espacio)
            self.styles.add(ParagraphStyle(
                name='CopyInstructions',
                parent=self.styles['ProgramInfo'],
                fontSize=9,
                alignment=TA_LEFT,
                textColor=colors.HexColor('#777777'),
                spaceBefore=0,
                spaceAfter=3,  # Reducido de 5 a 3
                backColor=colors.white,
                borderWidth=0,
                borderPadding=0
            ))
            
            # Estilo para código con formato de syntax highlighting (más compacto)
            self.styles.add(ParagraphStyle(
                name='SyntaxHighlightedCode',
                parent=self.styles['CodeStyle'],
                fontSize=11,
                fontName='Courier',
                spaceBefore=10,  # Reducido de 15 a 10
                spaceAfter=5,    # Reducido de 10 a 5
                leftIndent=10,
                rightIndent=10,
                backColor=colors.white,
                borderWidth=1,
                borderColor=colors.HexColor("#CCCCCC"),
                borderPadding=8,  # Reducido de 10 a 8
                borderRadius=0,
                leading=14,
                wordWrap=False
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
            code_elements.append(Paragraph(
                "/* Código Fuente */",
                self.styles['CodeHeader']
            ))
            
            # Instrucciones claras para copiar
            code_elements.append(Paragraph(
                "Para usar este código: Seleccione todo (Ctrl+A / Cmd+A) → Copie (Ctrl+C / Cmd+C)",
                self.styles['CopyInstructions']
            ))
            
            # Crear párrafo con el código con syntax highlighting
            code_para = Paragraph(
                highlighted_code,
                self.styles['SyntaxHighlightedCode']
            )
            
            # Añadir el código a la sección de códigos
            code_elements.append(code_para)
            code_elements.append(Spacer(1, 10))  # Reducido de 15 a 10
            
            # Añadir los elementos de código a la lista de códigos
            self.code_elements.append(KeepTogether(code_elements))
            self.code_elements.append(Spacer(1, 10))  # Reducido de 15 a 10
            
            # Crear elementos para la sección de resultados (más compactos)
            results_elements = []
            
            # Título del resultado
            result_title = f"Resultado: {program_name}"
            results_elements.append(Paragraph(
                result_title,
                self.styles['ProgramTitle']
            ))
            
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
                    
                    # NUEVO ENFOQUE: Usar la imagen directamente cuando sea posible
                    try:
                        # Intentar añadir la imagen directamente desde el archivo
                        # Este método evita transformaciones innecesarias que reducen calidad
                        original_img_width, original_img_height = None, None
                        
                        # Primero verificar las dimensiones
                        with PILImage.open(screenshot_path) as img_check:
                            original_img_width, original_img_height = img_check.size
                            max_width = 6.5 * inch  # Ancho máximo
                            
                            # Calcular dimensiones para PDF
                            if original_img_width > max_width:
                                ratio = max_width / original_img_width
                                img_width = max_width
                                img_height = original_img_height * ratio
                            else:
                                img_width = original_img_width
                                img_height = original_img_height
                        
                        # Añadir la imagen directamente sin procesamiento de buffer
                        results_elements.append(Paragraph(
                            "🖼️ Resultado de la Ejecución:",
                            self.styles['SectionHeader']
                        ))
                        
                        # Usar la imagen original sin procesamiento
                        img = ReportLabImage(screenshot_path, width=img_width, height=img_height)
                        results_elements.append(img)
                        results_elements.append(Spacer(1, 10))
                        
                        print(f"Imagen añadida directamente sin procesamiento. Dimensiones: {img_width}x{img_height}")
                        
                    except Exception as direct_img_error:
                        print(f"Error al añadir imagen directamente: {str(direct_img_error)}")
                        print("Intentando método alternativo con buffer en memoria...")
                        
                        # Si falla el método directo, usar el método de buffer en memoria
                        with PILImage.open(screenshot_path) as img:
                            # Conservar el modo original de la imagen
                            original_width, original_height = img.size
                            max_width = 6.5 * inch  # Ancho máximo
                            
                            # Determinamos si necesitamos redimensionar
                            if original_width > max_width:
                                ratio = max_width / original_width
                                new_width = int(original_width * ratio)
                                new_height = int(original_height * ratio)
                                # Usar LANCZOS para la mejor calidad de escalado
                                resized_img = img.resize((new_width, new_height), PILImage.LANCZOS)
                                print(f"Imagen redimensionada de {original_width}x{original_height} a {new_width}x{new_height}")
                                
                                # Usar la imagen redimensionada
                                work_img = resized_img
                                img_width = new_width
                                img_height = new_height
                            else:
                                # Usar la imagen original
                                work_img = img
                                img_width = original_width
                                img_height = original_height
                            
                            # Preparar el buffer en memoria
                            img_buffer = io.BytesIO()
                            
                            # Preservar el formato original
                            original_format = img.format or ('PNG' if screenshot_path.lower().endswith('.png') else 'JPEG')
                            
                            # Guardar con la máxima calidad
                            if original_format.upper() == 'PNG':
                                work_img.save(img_buffer, format='PNG', compress_level=0)  # Sin compresión
                                print("Guardando en formato PNG sin compresión")
                            else:
                                work_img.save(img_buffer, format='JPEG', quality=100, dpi=(300, 300), optimize=False)
                                print("Guardando en formato JPEG con calidad 100 y 300 DPI")
                            
                            img_buffer.seek(0)
                            
                            # Añadir la imagen con calidad preservada
                            results_elements.append(Paragraph(
                                "🖼️ Resultado de la Ejecución:",
                                self.styles['SectionHeader']
                            ))
                            
                            img = ReportLabImage(img_buffer, width=img_width, height=img_height)
                            results_elements.append(img)
                            results_elements.append(Spacer(1, 10))
                
                except Exception as e:
                    print(f"Error al procesar la imagen: {str(e)}")
                    traceback.print_exc()
                    results_elements.append(Paragraph(
                        f"Error al procesar la captura de pantalla: {str(e)}",
                        self.styles['Normal']
                    ))
            
            # Salida del programa en formato compacto
            if program_info.get('output'):
                # Evaluar longitud de la salida
                output_text = program_info['output']
                if len(output_text) > 1000:  # Si es muy largo, truncar
                    output_text = output_text[:1000] + "...\n[Resultado truncado por extensión]"
                
                results_elements.append(Paragraph(
                    "📊 Información de Compilación:",
                    self.styles['SectionHeader']
                ))
                
                output_para = Paragraph(
                    f"<pre>{output_text.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')}</pre>",
                    self.styles['CodeStyle']
                )
                results_elements.append(output_para)
            
            # Añadir los elementos de resultados a la lista de resultados
            self.results_elements.append(KeepTogether(results_elements[:3]))  # Título y subtítulo
            self.results_elements.extend(results_elements[3:])
            self.results_elements.append(Spacer(1, 10))  # Reducido de 15 a 10
            self.results_elements.append(Paragraph(
                "─" * 80,  # Línea horizontal como separador
                self.styles['CustomBody']
            ))
            self.results_elements.append(Spacer(1, 5))  # Reducido de 10 a 5
            
            # Generar análisis del programa para la Sección 3
            self.generate_program_analysis(program_info, style_type)
            
        except Exception as e:
            print(f"Error al añadir programa al PDF: {str(e)}")
            traceback.print_exc()
            self.code_elements.append(Paragraph(
                f"Error al procesar el programa: {str(e)}",
                self.styles['Normal']
            ))
    
    def generate_program_analysis(self, program_info, style_type=None):
        """Genera un análisis del programa para la sección 3."""
        try:
            program_name = program_info.get('name', 'Programa sin nombre')
            source_code = program_info.get('source_code', '')
            output = program_info.get('output', '')
            
            # Elementos para el análisis de este programa
            analysis_elements = []
            
            # Título del análisis
            analysis_title = f"Análisis del Programa: {program_name}"
            analysis_elements.append(Paragraph(
                analysis_title,
                self.styles['ProgramTitle']
            ))
            
            # Análisis básico del código
            code_lines = source_code.split('\n')
            total_lines = len(code_lines)
            
            # Detectar características del código
            uses_includes = '#include' in source_code
            uses_classes = 'class' in source_code
            uses_vectors = 'vector' in source_code or 'Vector' in source_code
            uses_loops = any(loop in source_code for loop in ['for', 'while', 'do'])
            uses_functions = bool(re.findall(r'\w+\s+\w+\s*\([^)]*\)\s*{', source_code))
            
            # Estilo para el análisis de código
            self.styles.add(ParagraphStyle(
                name='AnalysisText',
                parent=self.styles['CustomBody'],
                fontSize=10,
                leading=14,
                spaceBefore=4,
                spaceAfter=4,
                leftIndent=10
            ))
            
            # Crear tabla de características
            analysis_elements.append(Paragraph(
                "📋 Características del Código:",
                self.styles['SectionHeader']
            ))
            
            features_data = [
                ["Característica", "Valor"],
                ["Tipo de Programa", style_type or "General"],
                ["Total de Líneas", str(total_lines)],
                ["Uso de Includes", "Sí" if uses_includes else "No"],
                ["Uso de Clases", "Sí" if uses_classes else "No"],
                ["Uso de Vectores", "Sí" if uses_vectors else "No"],
                ["Uso de Ciclos", "Sí" if uses_loops else "No"],
                ["Uso de Funciones", "Sí" if uses_functions else "No"]
            ]
            
            # Crear tabla de características
            features_table = Table(features_data, colWidths=[2*inch, 2*inch])
            features_table.setStyle(TableStyle([
                ('BACKGROUND', (0, 0), (-1, 0), colors.HexColor("#3498DB")),
                ('TEXTCOLOR', (0, 0), (-1, 0), colors.whitesmoke),
                ('ALIGN', (0, 0), (-1, 0), 'CENTER'),
                ('FONTNAME', (0, 0), (-1, 0), 'Helvetica-Bold'),
                ('BACKGROUND', (0, 1), (-1, -1), colors.HexColor("#F5F5F5")),
                ('GRID', (0, 0), (-1, -1), 0.5, colors.grey),
                ('VALIGN', (0, 0), (-1, -1), 'MIDDLE'),
                ('ALIGN', (0, 0), (0, -1), 'LEFT'),
                ('ALIGN', (1, 0), (1, -1), 'CENTER'),
                ('PADDING', (0, 0), (-1, -1), 6)
            ]))
            
            analysis_elements.append(features_table)
            analysis_elements.append(Spacer(1, 10))
            
            # Análisis de rendimiento (basado en la complejidad del código)
            analysis_elements.append(Paragraph(
                "📊 Análisis de Rendimiento:",
                self.styles['SectionHeader']
            ))
            
            # Calcular complejidad aproximada
            complexity = 0
            
            # Factores que aumentan la complejidad
            if uses_loops: complexity += 10
            if uses_functions: complexity += 5
            if uses_classes: complexity += 10
            if uses_vectors: complexity += 5
            if total_lines > 50: complexity += 10
            if total_lines > 100: complexity += 10
            
            # Limitar la complejidad a un máximo de 100
            complexity = min(complexity, 100)
            
            # Determinar nivel de complejidad
            complexity_level = "Baja"
            if complexity > 30: complexity_level = "Media"
            if complexity > 60: complexity_level = "Alta"
            
            analysis_elements.append(Paragraph(
                f"• Complejidad estimada: {complexity}/100 (Nivel: {complexity_level})",
                self.styles['AnalysisText']
            ))
            
            # Análisis de buenas prácticas
            analysis_elements.append(Paragraph(
                "✅ Buenas Prácticas:",
                self.styles['SectionHeader']
            ))
            
            # Determinar buenas prácticas observadas
            good_practices = []
            
            if uses_functions:
                good_practices.append("Modularización mediante funciones")
            
            if "const" in source_code:
                good_practices.append("Uso de constantes para valores inmutables")
            
            if "&" in source_code and "const" in source_code:
                good_practices.append("Paso de parámetros por referencia constante (optimización)")
            
            comments_ratio = len(re.findall(r'(/\*|\*/|//)', source_code)) / max(total_lines, 1)
            if comments_ratio > 0.1:
                good_practices.append("Documentación mediante comentarios")
            
            # Si no hay buenas prácticas detectadas
            if not good_practices:
                good_practices.append("No se detectaron buenas prácticas específicas")
            
            for practice in good_practices:
                analysis_elements.append(Paragraph(
                    f"• {practice}",
                    self.styles['AnalysisText']
                ))
            
            # Oportunidades de mejora
            analysis_elements.append(Paragraph(
                "🔍 Oportunidades de Mejora:",
                self.styles['SectionHeader']
            ))
            
            # Determinar oportunidades de mejora
            improvement_opportunities = []
            
            if not uses_functions and total_lines > 30:
                improvement_opportunities.append("Considerar modularizar el código en funciones")
            
            if "using namespace std;" in source_code:
                improvement_opportunities.append("Evitar 'using namespace std;' en el ámbito global")
            
            if comments_ratio < 0.1:
                improvement_opportunities.append("Aumentar la documentación mediante comentarios")
            
            if not uses_classes and total_lines > 80:
                improvement_opportunities.append("Considerar el uso de estructuras o clases para organizar datos")
            
            # Si no hay oportunidades de mejora detectadas
            if not improvement_opportunities:
                improvement_opportunities.append("No se detectaron oportunidades de mejora específicas")
            
            for opportunity in improvement_opportunities:
                analysis_elements.append(Paragraph(
                    f"• {opportunity}",
                    self.styles['AnalysisText']
                ))
            
            # Agregar separador final
            analysis_elements.append(Spacer(1, 10))
            analysis_elements.append(Paragraph(
                "─" * 80,  # Línea horizontal como separador
                self.styles['CustomBody']
            ))
            analysis_elements.append(Spacer(1, 5))
            
            # Añadir análisis a la sección
            self.analysis_elements.extend(analysis_elements)
            
        except Exception as e:
            print(f"Error al generar análisis del programa: {str(e)}")
            traceback.print_exc()
            self.analysis_elements.append(Paragraph(
                f"Error al analizar el programa {program_info.get('name', '')}: {str(e)}",
                self.styles['Normal']
            ))
    
    def generate_summary_analysis(self):
        """Genera un resumen general de todos los programas."""
        if not self.programs:
            return []
        
        summary_elements = []
        
        # Título de resumen general
        summary_elements.append(Paragraph(
            "Resumen General de Programas",
            self.styles['ChapterTitle']
        ))
        
        # Estadísticas globales
        n_programs = len(self.programs)
        type_counts = {}
        for program in self.programs:
            prog_type = program['type']
            type_counts[prog_type] = type_counts.get(prog_type, 0) + 1
        
        # Descripción del resumen
        summary_elements.append(Paragraph(
            f"Este análisis incluye {n_programs} programa{'s' if n_programs != 1 else ''} C++ de diversos tipos y complejidades.",
            self.styles['CustomBody']
        ))
        
        # Distribución por tipos
        summary_elements.append(Paragraph(
            "📊 Distribución por Tipos:",
            self.styles['SectionHeader']
        ))
        
        for prog_type, count in type_counts.items():
            summary_elements.append(Paragraph(
                f"• {prog_type.capitalize()}: {count} programa{'s' if count != 1 else ''} ({count*100/n_programs:.1f}%)",
                self.styles['AnalysisText']
            ))
        
        # Observaciones generales
        summary_elements.append(Paragraph(
            "📋 Observaciones Generales:",
            self.styles['SectionHeader']
        ))
        
        summary_elements.append(Paragraph(
            "• Los programas procesados muestran un rango variado de técnicas de programación en C++",
            self.styles['AnalysisText']
        ))
        
        summary_elements.append(Paragraph(
            "• Se observa un buen uso de las bibliotecas estándar de C++ en la mayoría de los casos",
            self.styles['AnalysisText']
        ))
        
        summary_elements.append(Paragraph(
            "• La complejidad de los programas es adecuada para el contexto educativo",
            self.styles['AnalysisText']
        ))
        
        # Recomendaciones generales
        summary_elements.append(Paragraph(
            "💡 Recomendaciones Generales:",
            self.styles['SectionHeader']
        ))
        
        summary_elements.append(Paragraph(
            "• Incrementar el uso de comentarios para mejorar la legibilidad y mantenibilidad del código",
            self.styles['AnalysisText']
        ))
        
        summary_elements.append(Paragraph(
            "• Implementar manejo de errores más robusto mediante bloques try/catch",
            self.styles['AnalysisText']
        ))
        
        summary_elements.append(Paragraph(
            "• Considerar la adopción de estándares de codificación consistentes",
            self.styles['AnalysisText']
        ))
        
        summary_elements.append(Paragraph(
            "• Explorar características modernas de C++ (C++11 en adelante) como smart pointers y lambdas",
            self.styles['AnalysisText']
        ))
        
        summary_elements.append(Spacer(1, 15))
        
        return summary_elements
    
    def save(self):
        """Guarda el documento PDF final con la estructura reorganizada."""
        try:
            print(f"\nGenerando PDF en: {self.output_path}")
            
            # Generar la portada y el índice
            self.elements.extend(self.create_cover_page())
            
            # Actualizar el índice antes de construirlo
            self.update_index()
            self.elements.append(PageBreak())
            
            # Sección 1: Todos los códigos fuente
            self.elements.append(Paragraph(
                "SECCIÓN 1: CÓDIGOS FUENTE",
                self.styles['ChapterTitle']
            ))
            self.elements.append(Spacer(1, 5))  # Reducido de 15 a 5
            
            # Añadir todos los códigos
            self.elements.extend(self.code_elements)
            self.elements.append(PageBreak())
            
            # Sección 2: Todos los resultados de ejecución
            self.elements.append(Paragraph(
                "SECCIÓN 2: RESULTADOS DE EJECUCIÓN",
                self.styles['ChapterTitle']
            ))
            self.elements.append(Spacer(1, 5))  # Reducido de 15 a 5
            
            # Añadir todos los resultados
            self.elements.extend(self.results_elements)
            self.elements.append(PageBreak())
            
            # Sección 3: Análisis de programas
            self.elements.append(Paragraph(
                "SECCIÓN 3: ANÁLISIS TÉCNICO",
                self.styles['ChapterTitle']
            ))
            self.elements.append(Spacer(1, 5))
            
            # Añadir resumen general primero
            self.elements.extend(self.generate_summary_analysis())
            
            # Añadir análisis individuales
            self.elements.extend(self.analysis_elements)
            
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

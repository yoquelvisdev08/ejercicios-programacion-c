"""
Módulo para generar documentos PDF con los resultados de la compilación.
"""

import os
from datetime import datetime
from reportlab.lib import colors
from reportlab.lib.pagesizes import letter
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, Image as ReportLabImage, PageBreak
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.units import inch
from reportlab.lib.enums import TA_CENTER, TA_LEFT
from PIL import Image as PILImage
import traceback

from config.settings import PDF_CONFIG

class PDFGenerator:
    """Clase para generar documentos PDF con los resultados de la compilación."""
    
    def __init__(self, output_path):
        """Inicializa el generador de PDF."""
        self.output_path = output_path
        self.elements = []
        self.setup_styles()
        
        # Crear el documento
        self.doc = SimpleDocTemplate(
            output_path,
            pagesize=letter,
            rightMargin=PDF_CONFIG['margin']*inch,
            leftMargin=PDF_CONFIG['margin']*inch,
            topMargin=PDF_CONFIG['margin']*inch,
            bottomMargin=PDF_CONFIG['margin']*inch
        )
    
    def setup_styles(self):
        """Configura los estilos del documento."""
        self.styles = getSampleStyleSheet()
        
        # Estilo para el título principal
        self.styles.add(ParagraphStyle(
            name='CustomTitle',
            parent=self.styles['Title'],
            fontSize=24,
            spaceAfter=30,
            alignment=TA_CENTER
        ))
        
        # Estilo para subtítulos
        self.styles.add(ParagraphStyle(
            name='CustomHeading',
            parent=self.styles['Heading1'],
            fontSize=16,
            spaceBefore=20,
            spaceAfter=10
        ))
        
        # Estilo para código
        self.styles.add(ParagraphStyle(
            name='CodeStyle',
            parent=self.styles['Code'],
            fontSize=10,
            fontName='Courier',
            spaceBefore=10,
            spaceAfter=10,
            leftIndent=20
        ))
        
        # Estilo para texto normal
        self.styles.add(ParagraphStyle(
            name='CustomBody',
            parent=self.styles['Normal'],
            fontSize=11,
            spaceBefore=6,
            spaceAfter=6
        ))
        
        # Añadir portada
        self.add_cover_page()
    
    def add_cover_page(self):
        """Añade una portada al documento con información introductoria."""
        # Título principal
        self.elements.append(Paragraph(
            "Recopilación de Programas C++",
            self.styles['CustomTitle']
        ))
        
        # Añadir información del autor
        self.styles.add(ParagraphStyle(
            'Author',
            parent=self.styles['CustomBody'],
            fontSize=14,
            spaceBefore=10,
            spaceAfter=20,
            alignment=TA_CENTER,
            textColor=colors.HexColor('#2c5282')
        ))
        
        self.elements.append(Paragraph(
            "Desarrollado por: Yoquelvis Jorge Abreu",
            self.styles['Author']
        ))
        
        # Añadir estilo para la introducción
        self.styles.add(ParagraphStyle(
            'Introduction',
            parent=self.styles['CustomBody'],
            fontSize=12,
            spaceBefore=15,
            spaceAfter=15,
            leftIndent=30,
            rightIndent=30,
            alignment=TA_CENTER,  # Justified
            leading=18
        ))
        
        # Texto de introducción
        intro_text = """
        <strong>Acerca de esta herramienta:</strong><br/><br/>
        
        Esta aplicación es un compilador y visualizador avanzado para programas C++, diseñado para facilitar 
        el aprendizaje y la evaluación de ejercicios de programación. La herramienta automatiza el proceso 
        de compilación, ejecución y documentación de programas C++.<br/><br/>
        
        <strong>Características principales:</strong><br/>
        • Compilación automática de archivos C++ usando g++<br/>
        • Ejecución interactiva en terminal con captura de pantalla<br/>
        • Generación automática de informes en PDF con el código fuente y los resultados<br/>
        • Análisis del código para identificar estructuras y características<br/>
        • Interfaz intuitiva que permite procesar múltiples archivos secuencialmente<br/><br/>
        
        Los programas se compilan utilizando estándares modernos de C++ y se documentan incluyendo 
        tanto el código fuente como una captura de pantalla de su ejecución, permitiendo una 
        visualización completa de su funcionamiento.
        """
        
        self.elements.append(Paragraph(
            intro_text,
            self.styles['Introduction']
        ))
        
        # Fecha de generación
        self.styles.add(ParagraphStyle(
            'GenerationDate',
            parent=self.styles['CustomBody'],
            fontSize=10,
            spaceBefore=30,
            spaceAfter=0,
            alignment=TA_CENTER,
            textColor=colors.HexColor('#4a5568')
        ))
        
        self.elements.append(Paragraph(
            f"Generado el {datetime.now().strftime('%d/%m/%Y a las %H:%M:%S')}",
            self.styles['GenerationDate']
        ))
        
        self.elements.append(PageBreak())
    
    def add_program(self, program_info, style_type=None):
        """Añade un programa al PDF con su código y captura de pantalla.
        
        Args:
            program_info (dict): Información del programa a añadir
            style_type (str, optional): Tipo de estilo para el programa. Defaults to None.
        """
        try:
            # Añadir información del programa
            self.add_program_header(program_info)
            
            # Añadir código fuente
            if program_info.get('source_code'):
                self.add_source_code(program_info['source_code'])
            
            # Añadir captura de pantalla
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
                    
                    # Convertir a RGB si es necesario
                    with PILImage.open(screenshot_path) as img:
                        if img.mode not in ('RGB', 'RGBA'):
                            print(f"Convirtiendo imagen de modo {img.mode} a RGB")
                            rgb_img = img.convert('RGB')
                            rgb_path = screenshot_path.replace('.png', '_rgb.png').replace('.jpg', '_rgb.jpg')
                            rgb_img.save(rgb_path)
                            screenshot_path = rgb_path
                    
                    # Añadir la imagen al PDF usando ReportLabImage
                    img = ReportLabImage(screenshot_path, width=500, height=300, kind='proportional')
                    self.elements.append(img)
                    self.elements.append(Spacer(1, 20))
                    print("Imagen agregada correctamente al PDF")
                except Exception as e:
                    print(f"Error al procesar la imagen: {str(e)}")
                    traceback.print_exc()
                    self.elements.append(Paragraph(f"Error al procesar la captura de pantalla: {str(e)}", self.styles['Normal']))
            
            # Añadir salida del programa
            if program_info.get('output'):
                self.add_program_output(program_info['output'])
            
            # Añadir separador
            self.elements.append(PageBreak())
            
        except Exception as e:
            print(f"Error al añadir programa al PDF: {str(e)}")
            traceback.print_exc()
            self.elements.append(Paragraph(f"Error al procesar el programa: {str(e)}", self.styles['Normal']))
    
    def add_program_header(self, program_info):
        """Añade el encabezado del programa al PDF con información básica."""
        # Título del programa
        if isinstance(program_info, dict):
            # Nuevo formato basado en diccionario
            program_name = program_info.get('name', 'Programa sin nombre')
        else:
            # Formato antiguo (nombre como primer argumento)
            program_name = str(program_info)
        
        # Añadir título del programa
        self.elements.append(Paragraph(
            f"Programa: {program_name}",
            self.styles['CustomHeading']
        ))
        
        # Añadir separador
        self.elements.append(Spacer(1, 10))
    
    def add_source_code(self, source_code):
        """Añade el código fuente del programa al PDF."""
        # Título para la sección de código
        self.elements.append(Paragraph(
            "Código Fuente:",
            self.styles['CustomBody']
        ))
        
        # Añadir el código fuente con formato
        code_para = Paragraph(
            f"<pre>{source_code.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')}</pre>",
            self.styles['CodeStyle']
        )
        self.elements.append(code_para)
        
        # Añadir separador
        self.elements.append(Spacer(1, 15))
    
    def add_program_output(self, output_text):
        """Añade la salida del programa al PDF."""
        # Título para la sección de salida
        self.elements.append(Paragraph(
            "Información de Compilación y Ejecución:",
            self.styles['CustomBody']
        ))
        
        # Añadir la salida con formato
        output_para = Paragraph(
            f"<pre>{output_text.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')}</pre>",
            self.styles['CodeStyle']
        )
        self.elements.append(output_para)
        
        # Añadir separador
        self.elements.append(Spacer(1, 15))
    
    def save(self):
        """Guarda el documento PDF final."""
        try:
            print(f"\nGenerando PDF en: {self.output_path}")
            
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
                    pagesize=letter,
                    rightMargin=PDF_CONFIG['margin']*inch,
                    leftMargin=PDF_CONFIG['margin']*inch,
                    topMargin=PDF_CONFIG['margin']*inch,
                    bottomMargin=PDF_CONFIG['margin']*inch
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
                    pagesize=letter,
                    rightMargin=PDF_CONFIG['margin']*inch,
                    leftMargin=PDF_CONFIG['margin']*inch,
                    topMargin=PDF_CONFIG['margin']*inch,
                    bottomMargin=PDF_CONFIG['margin']*inch
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

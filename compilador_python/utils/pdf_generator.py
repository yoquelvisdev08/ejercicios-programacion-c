"""
Módulo para generar documentos PDF con los resultados de la compilación.
"""

import os
from datetime import datetime
from reportlab.lib import colors
from reportlab.lib.pagesizes import letter
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, Image, PageBreak
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.units import inch
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
            'CustomTitle',
            parent=self.styles['Heading1'],
            fontSize=24,
            spaceAfter=30,
            textColor=colors.HexColor('#1a365d'),
            alignment=1
        ))
        
        # Estilo para títulos de programas
        self.styles.add(ParagraphStyle(
            'ProgramTitle',
            parent=self.styles['Heading2'],
            fontSize=20,
            spaceBefore=20,
            spaceAfter=15,
            textColor=colors.HexColor('#2c5282')
        ))
        
        # Estilo para información del compilador
        self.styles.add(ParagraphStyle(
            'CompilerInfo',
            parent=self.styles['Normal'],
            fontSize=11,
            spaceBefore=10,
            spaceAfter=10,
            textColor=colors.HexColor('#4a5568'),
            backColor=colors.HexColor('#f9f9f9'),
            borderPadding=10
        ))
        
        # Estilo para bloques de código
        self.styles.add(ParagraphStyle(
            'CodeBlock',
            parent=self.styles['Code'],
            fontSize=11,
            fontName='Courier',
            spaceAfter=15,
            spaceBefore=15,
            textColor=colors.HexColor('#2c3e50'),
            backColor=colors.HexColor('#f7fafc'),
            borderPadding=10,
            borderWidth=1,
            borderColor=colors.HexColor('#dee2e6'),
            borderRadius=5
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
            parent=self.styles['Normal'],
            fontSize=14,
            spaceBefore=10,
            spaceAfter=20,
            alignment=1,
            textColor=colors.HexColor('#2c5282')
        ))
        
        self.elements.append(Paragraph(
            "Desarrollado por: Yoquelvis Jorge Abreu",
            self.styles['Author']
        ))
        
        # Añadir estilo para la introducción
        self.styles.add(ParagraphStyle(
            'Introduction',
            parent=self.styles['Normal'],
            fontSize=12,
            spaceBefore=15,
            spaceAfter=15,
            leftIndent=30,
            rightIndent=30,
            alignment=4,  # Justified
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
            parent=self.styles['Normal'],
            fontSize=10,
            spaceBefore=30,
            spaceAfter=0,
            alignment=1,
            textColor=colors.HexColor('#4a5568')
        ))
        
        self.elements.append(Paragraph(
            f"Generado el {datetime.now().strftime('%d/%m/%Y a las %H:%M:%S')}",
            self.styles['GenerationDate']
        ))
        
        self.elements.append(PageBreak())
    
    def add_program(self, name, code, compiler_info, screenshot_path=None):
        """Añade un programa al PDF con mejor formato."""
        try:
            # Título del programa
            self.elements.append(Paragraph(
                f"Programa: {name}",
                self.styles['ProgramTitle']
            ))
            
            # Información del compilador
            self.elements.append(Paragraph(
                compiler_info.replace('\n', '<br/>'),
                self.styles['CompilerInfo']
            ))
            
            # Código fuente
            self.elements.append(Paragraph(
                "Código Fuente:",
                self.styles['Heading3']
            ))
            
            # Formatear el código para mejor visualización
            formatted_code = code.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')
            formatted_code = formatted_code.replace('\n', '<br/>')
            formatted_code = formatted_code.replace('    ', '&nbsp;&nbsp;&nbsp;&nbsp;')
            
            self.elements.append(Paragraph(
                f'<pre>{formatted_code}</pre>',
                self.styles['CodeBlock']
            ))
            
            # Captura de pantalla
            if screenshot_path:
                print(f"\nProcesando captura para PDF: {screenshot_path}")
                
                # Obtener ruta de archivo JPEG correspondiente si el original es PNG
                jpg_path = screenshot_path
                if screenshot_path.lower().endswith('.png'):
                    jpg_path = screenshot_path.replace('.png', '.jpg')
                
                # Verificar primero la versión JPEG (debería existir por nuestro código mejorado)
                if os.path.exists(jpg_path):
                    use_path = jpg_path
                    print(f"Usando versión JPEG de la imagen: {jpg_path}")
                elif os.path.exists(screenshot_path):
                    use_path = screenshot_path
                    print(f"Usando imagen original: {screenshot_path}")
                else:
                    use_path = None
                    print(f"No se encontró ninguna versión de la imagen")
                
                if use_path and os.path.exists(use_path):
                    try:
                        # Verificar la imagen
                        size = os.path.getsize(use_path)
                        print(f"Tamaño de la captura: {size} bytes")
                        
                        if size == 0:
                            raise Exception("Archivo de captura vacío")
                        
                        self.elements.append(Paragraph(
                            "Resultado de la Ejecución:",
                            self.styles['Heading3']
                        ))
                        
                        # Intentar añadir la imagen al PDF directamente
                        try:
                            # Ajustar el tamaño de la imagen
                            img_width = self.doc.width * 0.9  # 90% del ancho de la página
                            img = Image(use_path)
                            aspect = img.imageHeight / float(img.imageWidth)
                            img.drawWidth = img_width
                            img.drawHeight = img_width * aspect
                            
                            self.elements.append(Spacer(1, 10))
                            self.elements.append(img)
                            self.elements.append(Spacer(1, 20))
                            
                            print("Captura añadida exitosamente al PDF")
                        except Exception as img_error:
                            print(f"Error al procesar la imagen: {img_error}")
                            traceback.print_exc()
                            
                            # Crear un párrafo alternativo en lugar de la imagen
                            self.elements.append(Paragraph(
                                "No se pudo mostrar la captura de pantalla automática. "
                                "Por favor, ejecute el programa manualmente para ver su salida exacta.",
                                self.styles['Normal']
                            ))
                            self.elements.append(Spacer(1, 10))
                        
                    except Exception as e:
                        print(f"Error al procesar la captura: {e}")
                        traceback.print_exc()
                        
                        # Agregar un mensaje alternativo
                        self.elements.append(Paragraph(
                            "Resultado de la Ejecución:",
                            self.styles['Heading3']
                        ))
                        self.elements.append(Paragraph(
                            "[Imagen no disponible]<br/><br/>"
                            "La captura de pantalla no pudo ser procesada. "
                            "El programa se ejecutó correctamente, pero no se pudo generar "
                            "una representación visual de su salida.",
                            self.styles['Normal']
                        ))
                else:
                    print(f"No se encontró el archivo de captura: {screenshot_path} ni {jpg_path}")
                    
                    # Agregar un mensaje alternativo
                    self.elements.append(Paragraph(
                        "Resultado de la Ejecución:",
                        self.styles['Heading3']
                    ))
                    self.elements.append(Paragraph(
                        "[Captura no disponible]<br/><br/>"
                        "No se encontró la captura de pantalla. "
                        "El programa se ejecutó, pero no se pudo generar "
                        "una representación visual de su salida.",
                        self.styles['Normal']
                    ))
            
            # Agregar un separador entre programas
            self.elements.append(PageBreak())
            
        except Exception as e:
            print(f"Error al añadir programa al PDF: {e}")
            traceback.print_exc()
            
            # Asegurarse de que se agregue algo al PDF incluso si hay errores
            self.elements.append(Paragraph(
                f"Programa: {name} (Ocurrió un error al procesar este programa)",
                self.styles['ProgramTitle']
            ))
            self.elements.append(Paragraph(
                "Ocurrió un error al procesar este programa para el PDF.<br/>"
                f"Error: {str(e)}",
                self.styles['CompilerInfo']
            ))
            self.elements.append(PageBreak())
    
    def save(self):
        """Guarda el PDF y verifica su integridad."""
        try:
            print(f"\n=== Guardando PDF en: {self.output_path} ===")
            
            # Verificar que hay contenido
            if not self.elements:
                raise Exception("No hay contenido para generar el PDF")
            
            # Construir el documento
            self.doc.build(self.elements)
            
            # Verificar el archivo generado
            if os.path.exists(self.output_path):
                pdf_size = os.path.getsize(self.output_path)
                print(f"PDF generado exitosamente ({pdf_size} bytes)")
                
                if pdf_size < 1000:  # Menos de 1KB
                    print("Advertencia: El PDF parece demasiado pequeño")
                
                return True
            else:
                raise Exception("No se pudo encontrar el PDF generado")
            
        except Exception as e:
            print(f"Error al guardar el PDF: {e}")
            traceback.print_exc()
            return False

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
        """Añade una portada al documento."""
        self.elements.append(Paragraph(
            "Recopilación de Programas C++",
            self.styles['CustomTitle']
        ))
        
        self.elements.append(Paragraph(
            f"Generado el {datetime.now().strftime('%d/%m/%Y a las %H:%M:%S')}",
            self.styles['CompilerInfo']
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
                
                if os.path.exists(screenshot_path):
                    try:
                        # Verificar la imagen
                        size = os.path.getsize(screenshot_path)
                        print(f"Tamaño de la captura: {size} bytes")
                        
                        if size == 0:
                            raise Exception("Archivo de captura vacío")
                        
                        self.elements.append(Paragraph(
                            "Resultado de la Ejecución:",
                            self.styles['Heading3']
                        ))
                        
                        # Ajustar el tamaño de la imagen
                        img_width = self.doc.width * 0.9  # 90% del ancho de la página
                        img = Image(screenshot_path)
                        aspect = img.imageHeight / float(img.imageWidth)
                        img.drawWidth = img_width
                        img.drawHeight = img_width * aspect
                        
                        self.elements.append(Spacer(1, 10))
                        self.elements.append(img)
                        self.elements.append(Spacer(1, 20))
                        
                        print("Captura añadida exitosamente al PDF")
                        
                    except Exception as e:
                        print(f"Error al procesar la captura: {e}")
                        traceback.print_exc()
                else:
                    print(f"No se encontró el archivo de captura: {screenshot_path}")
            
            # Agregar un separador entre programas
            self.elements.append(PageBreak())
            
        except Exception as e:
            print(f"Error al añadir programa al PDF: {e}")
            traceback.print_exc()
    
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

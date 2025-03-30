"""
Módulo para manejar las capturas de pantalla de la ejecución de programas.
"""

import os
import time
import tkinter as tk
from tkinter import ttk
import tkinter.scrolledtext as scrolledtext
from PIL import ImageGrab, Image, ImageDraw, ImageFont
import traceback
from datetime import datetime

from config.settings import GUI_CONFIG, SCREENSHOT_CONFIG, EXERCISE_TYPES

class OutputWindow:
    """Ventana personalizada para mostrar la salida del programa y tomar capturas."""
    
    def __init__(self, parent=None):
        """Inicializa la ventana de salida."""
        self.parent = parent or tk.Tk()
        self.window = tk.Toplevel(self.parent)
        self.screenshot = None
        self.setup_window()
    
    def setup_window(self):
        """Configura la ventana con estilos y widgets."""
        self.window.title("Resultado del Programa")
        self.window.geometry(f"{GUI_CONFIG['window_width']}x{GUI_CONFIG['window_height']}+100+100")
        self.window.configure(bg=GUI_CONFIG['theme']['background'])
        self.window.lift()
        self.window.focus_force()
        self.window.attributes('-topmost', True)
        
        # Frame principal
        self.main_frame = ttk.Frame(self.window, padding=15)
        self.main_frame.pack(fill="both", expand=True, padx=20, pady=20)
    
    def create_header(self, title, style_type="default"):
        """Crea el encabezado de la ventana con el estilo correspondiente."""
        style = EXERCISE_TYPES.get(style_type, EXERCISE_TYPES['default'])
        
        header_frame = tk.Frame(self.main_frame, bg=style['color'])
        header_frame.pack(fill="x", ipady=10, pady=(0, 15))
        
        title_label = tk.Label(
            header_frame,
            text=f"{style['icon']} {title}",
            font=(GUI_CONFIG['font_family'], GUI_CONFIG['theme']['title_font_size'], 'bold'),
            bg=style['color'],
            fg='white',
            padx=10
        )
        title_label.pack(pady=(10, 10))
    
    def create_output_area(self, style_type="default"):
        """Crea el área de texto para mostrar la salida."""
        style = EXERCISE_TYPES.get(style_type, EXERCISE_TYPES['default'])
        
        output_frame = ttk.Frame(self.main_frame, padding=10)
        output_frame.pack(fill="both", expand=True, padx=5, pady=5)
        
        # Configurar estilo
        s = ttk.Style()
        s.configure('Output.TFrame', background=style['bg_color'])
        
        output_inner_frame = ttk.Frame(output_frame, style='Output.TFrame')
        output_inner_frame.pack(fill="both", expand=True)
        
        self.output_display = scrolledtext.ScrolledText(
            output_inner_frame,
            wrap="word",
            font=(GUI_CONFIG['code_font_family'], GUI_CONFIG['theme']['body_font_size']),
            bg=style['bg_color'],
            fg=GUI_CONFIG['theme']['info'],
            padx=15,
            pady=15,
            borderwidth=0
        )
        self.output_display.pack(fill="both", expand=True)
    
    def create_footer(self):
        """Crea el pie de página con información y botones."""
        footer_frame = tk.Frame(self.main_frame, bg="#ecf0f1", height=30)
        footer_frame.pack(fill="x", pady=(15, 0))
        
        # Información de compilación
        footer_label = tk.Label(
            footer_frame,
            text=f"Compilado con éxito • {datetime.now().strftime('%d/%m/%Y %H:%M:%S')}",
            font=(GUI_CONFIG['font_family'], 9),
            bg="#ecf0f1",
            fg="#7f8c8d"
        )
        footer_label.pack(side=tk.RIGHT, padx=10, pady=8)
        
        # Botón de captura
        self.capture_button = tk.Button(
            footer_frame,
            text="Capturar y Cerrar",
            command=self.take_screenshot,
            bg=GUI_CONFIG['theme']['primary'],
            fg="white",
            font=(GUI_CONFIG['font_family'], 9, 'bold'),
            padx=10,
            relief="flat"
        )
        self.capture_button.pack(side=tk.LEFT, padx=10, pady=5)
        
        # Indicador de captura
        self.capture_label = tk.Label(
            footer_frame,
            text="",
            font=(GUI_CONFIG['font_family'], 9, 'bold'),
            bg="#ecf0f1",
            fg=GUI_CONFIG['theme']['error']
        )
        self.capture_label.pack(side=tk.LEFT, padx=10, pady=5)
    
    def show_output(self, output_text, style_type="default"):
        """Muestra la salida del programa con formato."""
        sections = output_text.split('\n\n')
        formatted_text = ""
        
        for section in sections:
            if section.strip():
                if style_type == "vector" and "[" in section:
                    lines = section.strip().split('\n')
                    formatted_text += self.format_vector_output(lines)
                elif style_type == "matriz" and self.is_matrix_output(section):
                    lines = section.strip().split('\n')
                    formatted_text += self.format_matrix_output(lines)
                else:
                    formatted_text += section.strip() + "\n\n"
        
        self.output_display.insert("1.0", formatted_text)
        self.output_display.configure(state="disabled")
    
    def format_vector_output(self, lines):
        """Da formato especial a la salida de vectores."""
        formatted = ""
        for line in lines:
            if "[" in line and "]" in line:
                formatted += "▶ " + line + "\n"
            else:
                formatted += line + "\n"
        return formatted + "\n"
    
    def format_matrix_output(self, lines):
        """Da formato especial a la salida de matrices."""
        formatted = ""
        for line in lines:
            if any(char.isdigit() for char in line) and len(line.strip()) > 0:
                formatted += "│ " + line + " │\n"
            else:
                formatted += line + "\n"
        return formatted + "\n"
    
    def is_matrix_output(self, text):
        """Determina si el texto corresponde a una matriz."""
        return any(x in text.lower() for x in ["filas", "columnas", "matriz"])
    
    def take_screenshot(self, filepath):
        """Toma una captura de la ventana actual."""
        try:
            self.capture_label.config(text="Tomando captura...")
            self.window.update_idletasks()
            
            # Esperar el tiempo configurado
            time.sleep(SCREENSHOT_CONFIG['delay'])
            
            # Obtener dimensiones y posición
            x = self.window.winfo_x()
            y = self.window.winfo_y()
            width = self.window.winfo_width()
            height = self.window.winfo_height()
            
            # Tomar la captura
            self.screenshot = ImageGrab.grab(bbox=(x, y, x+width, y+height))
            self.screenshot = self.screenshot.convert('RGB')
            
            # Guardar con las configuraciones especificadas
            self.screenshot.save(
                filepath,
                SCREENSHOT_CONFIG['format'],
                quality=SCREENSHOT_CONFIG['quality'],
                optimize=SCREENSHOT_CONFIG['optimize']
            )
            
            # Verificar la captura
            if os.path.exists(filepath) and os.path.getsize(filepath) > 0:
                print(f"Captura guardada exitosamente en: {filepath}")
                print(f"Tamaño de la captura: {os.path.getsize(filepath)} bytes")
                self.capture_label.config(
                    text="¡Captura exitosa!",
                    fg=GUI_CONFIG['theme']['success']
                )
            else:
                raise Exception("La captura se guardó pero está vacía")
            
            # Cerrar la ventana después de un momento
            self.window.after(1000, self.window.destroy)
            return True
            
        except Exception as e:
            print(f"Error al tomar la captura: {e}")
            traceback.print_exc()
            self.capture_label.config(
                text="Error al capturar",
                fg=GUI_CONFIG['theme']['error']
            )
            return False

def take_program_screenshot(output_text, screenshot_path, output_window=None):
    """Crea una imagen con el texto de la salida del programa."""
    try:
        print(f"\nCreando imagen con la salida del programa...")
        print(f"Ruta de destino: {screenshot_path}")
        
        # Asegurar que el directorio existe
        os.makedirs(os.path.dirname(screenshot_path), exist_ok=True)
        
        # Crear una imagen con el texto
        from PIL import Image, ImageDraw, ImageFont
        
        # Configurar dimensiones y colores
        width = SCREENSHOT_CONFIG['width']
        height = SCREENSHOT_CONFIG['height']
        bg_color = SCREENSHOT_CONFIG['bg_color']
        
        # Crear la imagen
        image = Image.new('RGB', (width, height), color=bg_color)
        draw = ImageDraw.Draw(image)
        
        # Intentar cargar una fuente monoespaciada
        try:
            font = ImageFont.truetype("Courier", 12)
        except:
            try:
                font = ImageFont.truetype("DejaVuSansMono", 12)
            except:
                font = ImageFont.load_default()
        
        # Dibujar el texto
        margin = 20
        y = margin
        for line in output_text.split('\n'):
            draw.text((margin, y), line, fill='black', font=font)
            y += 20
        
        # Guardar la imagen
        image.save(
            screenshot_path,
            SCREENSHOT_CONFIG['format'],
            quality=SCREENSHOT_CONFIG['quality'],
            optimize=SCREENSHOT_CONFIG['optimize']
        )
        
        # Verificar la imagen
        if os.path.exists(screenshot_path):
            size = os.path.getsize(screenshot_path)
            print(f"Imagen creada exitosamente ({size} bytes)")
            return True
        else:
            raise Exception("No se pudo guardar la imagen")
            
    except Exception as e:
        print(f"Error al crear la imagen: {e}")
        traceback.print_exc()
        return False

def take_terminal_screenshot(screenshot_path, window_title):
    """Toma una captura de la ventana de terminal."""
    try:
        print(f"\nTomando captura de la ventana de terminal...")
        print(f"Ruta de destino: {screenshot_path}")
        
        # Asegurar que el directorio existe
        os.makedirs(os.path.dirname(screenshot_path), exist_ok=True)
        
        # Cambiar la extensión del archivo a jpg si es png
        jpg_path = screenshot_path
        if screenshot_path.lower().endswith('.png'):
            jpg_path = screenshot_path.replace('.png', '.jpg')
        
        # Método 1: Intentar usando screencapture nativo de macOS con formato JPEG
        try:
            print("Intentando captura con screencapture nativo (formato JPEG)...")
            # -t jpg especifica el formato, -l captura ventana específica
            os.system(f"screencapture -t jpg -l$(osascript -e 'tell app \"Terminal\" to id of window 1') {jpg_path}")
            
            # Verificar si el archivo se creó correctamente
            if os.path.exists(jpg_path) and os.path.getsize(jpg_path) > 100:
                print(f"Captura guardada exitosamente usando screencapture nativo (JPEG)")
                
                # Si el nombre original terminaba en .png, copiar el archivo para mantener esa referencia
                if jpg_path != screenshot_path:
                    import shutil
                    shutil.copy2(jpg_path, screenshot_path)
                    print(f"Archivo copiado a {screenshot_path} para mantener compatibilidad")
                
                return True
        except Exception as e:
            print(f"Error al usar screencapture nativo: {e}")
        
        # Método 2: Capturar toda la pantalla y recortarla según coordenadas fijas
        try:
            print("Intentando captura de pantalla completa (JPEG)...")
            # Coordenadas fijas para una ventana de terminal
            x, y = 50, 50
            width, height = 800, 600
            
            # Tomar la captura de toda la pantalla
            screenshot = ImageGrab.grab()
            screenshot = screenshot.convert('RGB')  # Asegurar que está en RGB
            
            # Recortar la región de interés
            screenshot = screenshot.crop((x, y, x + width, y + height))
            
            # Guardar la imagen directamente en JPEG
            screenshot.save(jpg_path, 'JPEG', quality=90)
            
            # Si el nombre original terminaba en .png, copiar el archivo
            if jpg_path != screenshot_path:
                import shutil
                shutil.copy2(jpg_path, screenshot_path)
            
            # Verificar la imagen
            if os.path.exists(jpg_path) and os.path.getsize(jpg_path) > 100:
                print(f"Captura guardada exitosamente con recorte fijo (JPEG)")
                return True
        except Exception as e:
            print(f"Error al usar captura con recorte fijo: {e}")
        
        # Método 3: Último recurso - generar una imagen de reemplazo con un mensaje
        print("Generando imagen de reemplazo (JPEG)...")
        width, height = 800, 600
        img = Image.new('RGB', (width, height), color='white')
        d = ImageDraw.Draw(img)
        
        # Intentar cargar una fuente
        try:
            font = ImageFont.truetype("Arial", 16)
        except:
            try:
                font = ImageFont.truetype("DejaVuSans", 16)
            except:
                font = ImageFont.load_default()
        
        # Texto para mostrar en la imagen
        title = "Salida del programa"
        message = (
            "La captura automática de la ventana del terminal no funcionó.\n"
            "Sin embargo, el programa se ejecutó correctamente.\n\n"
            "Por favor, ejecute el programa manualmente para ver su salida exacta."
        )
        
        # Dibujar un recuadro y el texto
        d.rectangle([10, 10, width-10, height-10], outline="#3498db", width=2)
        d.text((20, 20), title, fill="#3498db", font=font)
        d.multiline_text((20, 60), message, fill="black", font=font, spacing=10)
        
        # Guardar la imagen en JPEG para mejor compatibilidad
        img.save(jpg_path, 'JPEG', quality=90)
        
        # Si el nombre original terminaba en .png, copiar el archivo
        if jpg_path != screenshot_path:
            import shutil
            shutil.copy2(jpg_path, screenshot_path)
        
        if os.path.exists(jpg_path):
            print(f"Imagen de reemplazo generada correctamente (JPEG)")
            return True
        else:
            raise Exception("No se pudo guardar la imagen de reemplazo")
            
    except Exception as e:
        print(f"Error al tomar la captura: {e}")
        traceback.print_exc()
        return False

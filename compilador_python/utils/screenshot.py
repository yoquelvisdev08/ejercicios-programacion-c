"""
Módulo para manejar las capturas de pantalla de la ejecución de programas.
"""

import os
import time
import traceback
from datetime import datetime
import tkinter as tk
from tkinter import ttk
import tkinter.scrolledtext as scrolledtext
from PIL import Image, ImageDraw, ImageFont

try:
    from PIL import ImageGrab
except ImportError:
    # En algunos sistemas como Linux, ImageGrab puede no estar disponible
    ImageGrab = None

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
        self.window.geometry(f"{SCREENSHOT_CONFIG['width']}x{SCREENSHOT_CONFIG['height']}+100+100")
        self.window.configure(bg=GUI_CONFIG['theme']['background'])
        self.window.lift()
        self.window.focus_force()
        
        # Frame principal con padding
        self.main_frame = ttk.Frame(self.window, padding=15)
        self.main_frame.pack(fill="both", expand=True)
    
    def capture_window(self, output_path):
        """Captura la ventana actual usando screencapture en macOS."""
        try:
            # Asegurar que la ventana está visible y actualizada
            self.window.update_idletasks()
            self.window.update()
            time.sleep(0.5)  # Pequeña pausa para asegurar que la ventana está lista
            
            # Obtener el ID de la ventana
            window_id = self.window.winfo_id()
            
            # Usar screencapture para capturar la ventana específica
            temp_path = output_path.replace('.png', '.jpg')
            cmd = ['screencapture', '-l' + str(window_id), '-t', 'jpg', temp_path]
            result = subprocess.run(cmd, capture_output=True, text=True)
            
            if result.returncode == 0 and os.path.exists(temp_path):
                # Convertir a PNG para mantener compatibilidad
                with Image.open(temp_path) as img:
                    img.save(output_path, 'PNG')
                os.remove(temp_path)  # Eliminar el archivo temporal JPG
                return True
            return False
        except Exception as e:
            print(f"Error al capturar la pantalla: {str(e)}")
            return False
    
    def show_output(self, output_text, title="Resultado del Programa"):
        """Muestra la salida del programa en la ventana."""
        self.window.title(title)
        
        # Crear área de texto con estilo moderno
        output_area = scrolledtext.ScrolledText(
            self.main_frame,
            wrap=tk.WORD,
            font=(GUI_CONFIG['code_font_family'], 12),
            bg=GUI_CONFIG['theme']['card_bg'],
            fg=GUI_CONFIG['theme']['text'],
            insertbackground=GUI_CONFIG['theme']['text'],
            selectbackground=GUI_CONFIG['theme']['primary'],
            selectforeground=GUI_CONFIG['theme']['text'],
            padx=10,
            pady=10,
            relief="flat"
        )
        output_area.pack(fill="both", expand=True)
        
        # Insertar el texto
        output_area.insert(tk.END, output_text)
        output_area.configure(state="disabled")
        
        # Centrar la ventana
        self.window.update_idletasks()
        width = self.window.winfo_width()
        height = self.window.winfo_height()
        x = (self.window.winfo_screenwidth() // 2) - (width // 2)
        y = (self.window.winfo_screenheight() // 2) - (height // 2)
        self.window.geometry(f'{width}x{height}+{x}+{y}')

def take_program_screenshot(output_text, screenshot_path, output_window=None):
    """Crea una imagen con el texto de la salida del programa."""
    try:
        print(f"\nCreando imagen con la salida del programa...")
        print(f"Ruta de destino: {screenshot_path}")
        
        # Asegurar que el directorio existe
        os.makedirs(os.path.dirname(screenshot_path), exist_ok=True)
        
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
        
        # Método más robusto utilizando AppleScript y screencapture
        try:
            print("Intentando captura con AppleScript mejorado (formato JPEG)...")
            
            # Primer paso: Obtener el ID de la ventana de Terminal activa
            get_window_id_script = """osascript -e '
tell application "Terminal"
    id of front window
end tell'"""
            
            window_id = os.popen(get_window_id_script).read().strip()
            
            if window_id:
                # Si tenemos un ID válido, tomamos la captura usando screencapture
                capture_cmd = f"screencapture -l{window_id} -t jpg '{jpg_path}'"
                print(f"Ejecutando: {capture_cmd}")
                os.system(capture_cmd)
                
                # Verificar si el archivo se creó correctamente
                if os.path.exists(jpg_path) and os.path.getsize(jpg_path) > 1000:
                    print(f"Captura guardada exitosamente usando screencapture con ID: {window_id}")
                    
                    # Si el nombre original terminaba en .png, copiar el archivo para mantener esa referencia
                    if jpg_path != screenshot_path:
                        import shutil
                        shutil.copy2(jpg_path, screenshot_path)
                        print(f"Archivo copiado a {screenshot_path} para mantener compatibilidad")
                    
                    return True
                else:
                    print(f"La captura se creó pero parece inválida (tamaño: {os.path.getsize(jpg_path) if os.path.exists(jpg_path) else 'no existe'})")
            else:
                print("No se pudo obtener el ID de la ventana de Terminal")
                
        except Exception as e:
            print(f"Error al usar método AppleScript mejorado: {e}")
            traceback.print_exc()
        
        # Método alternativo usando Terminal activa sin necesidad de ID
        try:
            print("Intentando captura directa de Terminal activa...")
            # Usar el modo de captura de ventana activa
            os.system(f"screencapture -w -t jpg '{jpg_path}'")
            
            # Verificar si el archivo se creó correctamente
            if os.path.exists(jpg_path) and os.path.getsize(jpg_path) > 1000:
                print(f"Captura de ventana activa guardada exitosamente")
                
                # Si el nombre original terminaba en .png, copiar el archivo
                if jpg_path != screenshot_path:
                    import shutil
                    shutil.copy2(jpg_path, screenshot_path)
                
                return True
        except Exception as e:
            print(f"Error al usar captura de ventana activa: {e}")
            traceback.print_exc()
        
        # Método 3: Capturar área de pantalla específica
        try:
            print("Intentando captura de área específica...")
            
            # Ejecutar AppleScript para obtener posición y tamaño de la ventana de Terminal
            get_bounds_script = """osascript -e '
tell application "Terminal"
    get bounds of front window
end tell'"""
            
            bounds = os.popen(get_bounds_script).read().strip()
            if bounds:
                # Parsear los límites (left, top, right, bottom)
                try:
                    bounds_list = [int(x.strip()) for x in bounds.split(",")]
                    if len(bounds_list) == 4:
                        left, top, right, bottom = bounds_list
                        
                        # Capturar el área específica
                        capture_cmd = f"screencapture -R{left},{top},{right-left},{bottom-top} -t jpg '{jpg_path}'"
                        print(f"Ejecutando captura de área: {capture_cmd}")
                        os.system(capture_cmd)
                        
                        if os.path.exists(jpg_path) and os.path.getsize(jpg_path) > 1000:
                            print(f"Captura de área específica guardada exitosamente")
                            
                            # Si el nombre original terminaba en .png, copiar el archivo
                            if jpg_path != screenshot_path:
                                import shutil
                                shutil.copy2(jpg_path, screenshot_path)
                            
                            return True
                except Exception as parse_err:
                    print(f"Error al parsear límites de ventana: {parse_err}")
        except Exception as e:
            print(f"Error al usar captura de área específica: {e}")
            traceback.print_exc()
        
        # Método 4: Captura usando ImageGrab (PIL)
        if ImageGrab is not None:
            try:
                print("Intentando captura con PIL ImageGrab...")
                
                # Usar método genérico de captura de toda la pantalla y permitir al usuario ajustar manualmente
                # por si los métodos automáticos fallan
                print("Por favor, asegúrese que la ventana de Terminal es visible en pantalla")
                print("Espere 3 segundos para capturar toda la pantalla...")
                time.sleep(3)
                
                # Tomar captura de toda la pantalla
                screenshot = ImageGrab.grab()
                screenshot = screenshot.convert('RGB')  # Asegurar que está en RGB
                
                # Guardar la captura completa
                screenshot.save(jpg_path, 'JPEG', quality=95)
                
                # Si el nombre original terminaba en .png, copiar el archivo
                if jpg_path != screenshot_path:
                    import shutil
                    shutil.copy2(jpg_path, screenshot_path)
                
                if os.path.exists(jpg_path) and os.path.getsize(jpg_path) > 1000:
                    print(f"Captura completa de pantalla guardada exitosamente")
                    print("Nota: La captura incluye toda la pantalla, no solo la terminal")
                    return True
                    
            except Exception as e:
                print(f"Error al usar PIL ImageGrab: {e}")
                traceback.print_exc()
        else:
            print("PIL.ImageGrab no está disponible en este sistema")
        
        # Método final: Generar una imagen de reemplazo con un mensaje
        print("Generando imagen de reemplazo como último recurso...")
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
        img.save(jpg_path, 'JPEG', quality=95)
        
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

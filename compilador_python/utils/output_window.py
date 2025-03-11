"""
Módulo para manejar la ventana de salida de los programas.
"""

import tkinter as tk
from tkinter import ttk
import tkinter.scrolledtext as scrolledtext
from datetime import datetime

from config.settings import GUI_CONFIG, EXERCISE_TYPES

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
            text="📸 Capturar y Cerrar",
            font=(GUI_CONFIG['font_family'], 9),
            bg="#2ecc71",
            fg="white",
            relief="flat",
            command=self.window.destroy
        )
        self.capture_button.pack(side=tk.LEFT, padx=10, pady=5) 
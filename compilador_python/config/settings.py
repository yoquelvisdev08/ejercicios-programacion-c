"""
Configuraciones globales para el compilador C++.
"""

import os

# Rutas base
BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TEMP_DIR = os.path.join(BASE_DIR, "temp_compilation")
OUTPUT_DIR = os.path.join(BASE_DIR, "output")

# Configuración del compilador
COMPILER_CONFIG = {
    "compiler": "g++",
    "flags": ["-Wall", "-std=c++11"],
    "timeout": 10  # segundos
}

# Configuración de la interfaz gráfica
GUI_CONFIG = {
    "window_width": 1200,
    "window_height": 800,
    "icon_path": os.path.join(BASE_DIR, "resources", "icon.png"),
    "font_family": "SF Pro Display",  # Fuente moderna
    "code_font_family": "JetBrains Mono",  # Mejor fuente para código
    "bootstrap_theme": "darkly",  # Tema oscuro moderno
    "theme": {
        "primary": "#007AFF",    # Azul iOS
        "success": "#34C759",    # Verde iOS
        "warning": "#FF9500",    # Naranja iOS
        "error": "#FF3B30",      # Rojo iOS
        "info": "#5856D6",       # Violeta iOS
        "background": "#1C1C1E", # Fondo oscuro
        "surface": "#2C2C2E",    # Superficie de tarjetas
        "text": "#FFFFFF",       # Texto principal
        "text_secondary": "#8E8E93", # Texto secundario
        "border": "#3A3A3C",     # Bordes
        "hover": "#3A3A3C",      # Color hover
        "active": "#48484A",     # Color active
        "card_bg": "#2C2C2E",    # Fondo de tarjetas
        "input_bg": "#3A3A3C",   # Fondo de inputs
    }
}

# Configuración de capturas de pantalla
SCREENSHOT_CONFIG = {
    "delay": 0.5,         # segundos de espera antes de capturar
    "quality": 95,        # calidad de la imagen (1-100)
    "format": "PNG",      # formato de imagen
    "optimize": True,     # optimizar imagen
    "width": 800,        # ancho por defecto
    "height": 600,       # alto por defecto
    "bg_color": GUI_CONFIG["theme"]["background"]  # usar color de fondo del tema
}

# Configuración del PDF
PDF_CONFIG = {
    "margin": 0.5,         # pulgadas (reducido de 0.75)
    "title_font_size": 16, # reducido de 18
    "body_font_size": 10,  # reducido de 12
    "code_font_size": 9    # reducido de 11
}

# Tipos de ejercicios y sus estilos
EXERCISE_TYPES = {
    "vector": {
        "icon": "📊",
        "color": GUI_CONFIG["theme"]["primary"],
        "bg_color": "#0A84FF20"  # Primary con transparencia
    },
    "matriz": {
        "icon": "🔢",
        "color": GUI_CONFIG["theme"]["success"],
        "bg_color": "#32D74B20"  # Success con transparencia
    },
    "cadena": {
        "icon": "📝",
        "color": GUI_CONFIG["theme"]["warning"],
        "bg_color": "#FF9F0A20"  # Warning con transparencia
    },
    "estructura": {
        "icon": "🏗️",
        "color": GUI_CONFIG["theme"]["info"],
        "bg_color": "#5E5CE120"  # Info con transparencia
    },
    "default": {
        "icon": "💻",
        "color": GUI_CONFIG["theme"]["text"],
        "bg_color": GUI_CONFIG["theme"]["card_bg"]
    }
}

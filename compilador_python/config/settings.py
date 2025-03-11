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
    "window_width": 900,
    "window_height": 700,
    "font_family": "Helvetica",
    "code_font_family": "Consolas",
    "theme": {
        "primary": "#3498db",    # Azul
        "success": "#2ecc71",    # Verde
        "warning": "#f1c40f",    # Amarillo
        "error": "#e74c3c",      # Rojo
        "info": "#34495e",       # Gris oscuro
        "background": "#f5f5f5", # Gris claro
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
    "bg_color": "white"  # color de fondo
}

# Configuración del PDF
PDF_CONFIG = {
    "margin": 0.5,        # pulgadas
    "title_font_size": 16,
    "body_font_size": 12,
    "code_font_size": 10
}

# Tipos de ejercicios y sus estilos
EXERCISE_TYPES = {
    "vector": {
        "icon": "🔢",
        "color": "#3498db",
        "bg_color": "#e8f4f8"
    },
    "matriz": {
        "icon": "📊",
        "color": "#2ecc71",
        "bg_color": "#e8f8e8"
    },
    "cadena": {
        "icon": "📝",
        "color": "#e74c3c",
        "bg_color": "#f8e8e8"
    },
    "estructura": {
        "icon": "📋",
        "color": "#9b59b6",
        "bg_color": "#f0e8f8"
    },
    "default": {
        "icon": "💻",
        "color": "#34495e",
        "bg_color": "#f0f0f0"
    }
}

#!/usr/bin/env python3
"""
Script para crear un icono simple para el compilador.
"""

from PIL import Image, ImageDraw, ImageFont
import os

def create_icon():
    """Crea un icono simple para el compilador."""
    # Crear una imagen cuadrada
    img_size = 512
    img = Image.new('RGBA', (img_size, img_size), (0, 0, 0, 0))
    draw = ImageDraw.Draw(img)
    
    # Definir colores
    background_color = "#007AFF"  # Azul iOS
    text_color = "#FFFFFF"        # Blanco
    
    # Dibujar un círculo como fondo
    circle_margin = 10
    circle_radius = (img_size - 2 * circle_margin) // 2
    circle_center = (img_size // 2, img_size // 2)
    
    # Dibujar círculo de fondo
    draw.ellipse(
        (
            circle_center[0] - circle_radius,
            circle_center[1] - circle_radius,
            circle_center[0] + circle_radius,
            circle_center[1] + circle_radius
        ),
        fill=background_color
    )
    
    # Dibujar texto "C++" en el centro
    try:
        # Intentar usar una fuente del sistema
        font_size = img_size // 4
        font = ImageFont.truetype("Arial Bold", font_size)
    except IOError:
        # Si falla, usar la fuente por defecto
        font = ImageFont.load_default()
        font_size = img_size // 8
    
    text = "C++"
    text_bbox = draw.textbbox((0, 0), text, font=font)
    text_width = text_bbox[2] - text_bbox[0]
    text_height = text_bbox[3] - text_bbox[1]
    
    text_position = (
        circle_center[0] - text_width // 2,
        circle_center[1] - text_height // 2
    )
    
    # Dibujar el texto
    draw.text(text_position, text, font=font, fill=text_color)
    
    # Guardar la imagen
    output_path = os.path.join("resources", "icon.png")
    img.save(output_path)
    print(f"Icono creado en: {output_path}")
    
    return output_path

if __name__ == "__main__":
    create_icon() 
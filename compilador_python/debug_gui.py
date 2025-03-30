#!/usr/bin/env python3
"""
Script para ejecutar y depurar la interfaz gráfica directamente.
"""

import sys
import traceback
import time
import os

def check_import(module_name, description=""):
    try:
        if "." in module_name:
            base_module, sub_module = module_name.split(".", 1)
            base = __import__(base_module)
            # Intentar acceder al submódulo
            parts = sub_module.split(".")
            for part in parts:
                base = getattr(base, part)
            print(f"✓ Módulo {module_name} importado correctamente")
            return True
        else:
            __import__(module_name)
            print(f"✓ Módulo {module_name} importado correctamente")
            return True
    except ImportError as e:
        print(f"✗ Error al importar {module_name}: {e}")
        return False
    except Exception as e:
        print(f"✗ Error al verificar {module_name}: {e}")
        return False

try:
    print("\n=== Depuración de la Interfaz Gráfica ===")
    print(f"Directorio actual: {os.getcwd()}")
    print(f"Directorio de Python: {sys.executable}")
    print("Verificando módulos necesarios...")
    
    check_import("tkinter", "Interfaz gráfica básica")
    check_import("PIL.Image", "Procesamiento de imágenes")
    check_import("reportlab", "Generación de PDF")
    check_import("nltk", "Procesamiento de lenguaje natural")
    
    # Verificar ttkbootstrap
    try:
        import ttkbootstrap
        from ttkbootstrap.constants import *
        print(f"✓ ttkbootstrap versión {ttkbootstrap.__version__} importado correctamente")
    except ImportError:
        print("✗ ttkbootstrap no está disponible - se usará la interfaz estándar")
    except Exception as e:
        print(f"✗ Error al verificar ttkbootstrap: {e}")
    
    # Intentar iniciar la interfaz gráfica
    print("\nIniciando la interfaz gráfica...")
    from gui.main_window import main
    main()
    print("Interfaz gráfica cerrada normalmente")
    
except Exception as e:
    print(f"\nError al iniciar la interfaz gráfica: {e}")
    print("\nTraceback completo:")
    traceback.print_exc()
    sys.exit(1) 
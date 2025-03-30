"""
Punto de entrada principal para el compilador C++ avanzado.
"""

import os
import sys
import argparse
import platform
import traceback

def check_dependencies():
    """Verifica que todas las dependencias necesarias estén instaladas."""
    missing_deps = []
    
    # Verificar bibliotecas básicas
    required_packages = [
        "PIL", "reportlab", "nltk", "tkinter"
    ]
    
    for package in required_packages:
        try:
            if package == "PIL":
                __import__("PIL.Image")
            elif package == "tkinter":
                __import__("tkinter")
            else:
                __import__(package)
        except ImportError:
            missing_deps.append(package)
    
    # Verificar componentes específicos que necesitamos
    try:
        from PIL import ImageGrab
    except ImportError:
        missing_deps.append("PIL.ImageGrab")
    
    # Verificar que se pueden usar capturas de pantalla (en macOS)
    if platform.system() == "Darwin":  # macOS
        try:
            from PIL import ImageGrab
            # Intentar una captura de pantalla simple
            try:
                ImageGrab.grab(bbox=(0, 0, 10, 10))
            except Exception as e:
                print(f"Advertencia: No se pueden capturar imágenes de pantalla: {e}")
                print("Es posible que necesite otorgar permisos a Terminal o Python en Seguridad y Privacidad.")
        except:
            pass
    
    if missing_deps:
        print("Faltan las siguientes dependencias:")
        for dep in missing_deps:
            print(f"  - {dep}")
        print("\nIntente ejecutar: pip install -r requirements.txt")
        return False
    
    return True

def setup_environment():
    """Configura el entorno de ejecución."""
    # Asegurar que estamos en el directorio correcto
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    
    # Añadir el directorio actual al path
    if os.path.dirname(os.path.abspath(__file__)) not in sys.path:
        sys.path.append(os.path.dirname(os.path.abspath(__file__)))
    
    # Crear directorios necesarios
    for dir_path in ["temp_compilation", "output"]:
        os.makedirs(dir_path, exist_ok=True)
    
    # Indicar que la carpeta temp_compilation ha sido limpiada al inicio
    open(os.path.join("temp_compilation", ".cleaned"), "w").close()

def parse_arguments():
    """Procesa los argumentos de línea de comandos."""
    parser = argparse.ArgumentParser(
        description="Compilador C++ avanzado con interfaz gráfica"
    )
    
    parser.add_argument(
        '--no-gui',
        action='store_true',
        help='Ejecutar en modo consola (sin interfaz gráfica)'
    )
    
    parser.add_argument(
        '--skip-checks',
        action='store_true',
        help='Omitir verificación de dependencias'
    )
    
    parser.add_argument(
        '--new-venv',
        action='store_true',
        help='Recrear el entorno virtual (uso interno del script)'
    )
    
    parser.add_argument(
        '--clean-temp',
        action='store_true',
        help='Limpiar archivos temporales y salir'
    )
    
    parser.add_argument(
        '--keep-current',
        action='store_true',
        help='Mantener archivos de la ejecución actual cuando se usa --clean-temp'
    )
    
    parser.add_argument(
        'files',
        nargs='*',
        help='Archivos .cpp a procesar'
    )
    
    return parser.parse_args()

def run_gui_mode():
    """Ejecuta el programa en modo gráfico."""
    try:
        from gui.main_window import main
        main()
    except Exception as e:
        print(f"Error al iniciar la interfaz gráfica: {e}")
        traceback.print_exc()
        print("\nIntentando ejecutar en modo consola...")
        return False
    return True

def run_console_mode(files):
    """Ejecuta el programa en modo consola."""
    from core.compiler import CppCompiler
    
    if not files:
        print("Error: No se especificaron archivos para procesar")
        return False
    
    # Verificar que g++ esté instalado
    if os.system("g++ --version > /dev/null 2>&1") != 0:
        print("Error: No se encuentra el compilador g++. Por favor, instálelo antes de continuar.")
        if platform.system() == "Darwin":  # macOS
            print("En macOS, puede instalarlo con: xcode-select --install")
        elif platform.system() == "Linux":
            print("En Linux, puede instalarlo con: sudo apt-get install g++")
        return False
    
    compiler = CppCompiler()
    success = True
    
    for file in files:
        if not os.path.exists(file):
            print(f"Error: No se encuentra el archivo {file}")
            success = False
            continue
        
        if not file.lower().endswith('.cpp'):
            print(f"Error: {file} no es un archivo C++ válido")
            success = False
            continue
        
        print(f"\nProcesando: {file}")
        result = compiler.process_file(file)
        
        if result["success"]:
            print(f"✓ {os.path.basename(file)} procesado correctamente")
        else:
            print(f"✗ Error al procesar {os.path.basename(file)}")
            if "error" in result:
                print(f"  Error: {result['error']}")
            success = False
    
    if compiler.save_pdf():
        print("\nPDF generado correctamente")
    else:
        print("\nError al generar el PDF")
        success = False
    
    compiler.cleanup()
    return success

def main():
    """Función principal."""
    try:
        # Configurar entorno
        setup_environment()
        
        # Mostrar información del sistema
        print(f"\n=== Compilador C++ Avanzado ===")
        print(f"Sistema: {platform.system()} {platform.release()}")
        print(f"Python: {platform.python_version()}")
        print(f"Arquitectura: {platform.machine()}")
        print(f"{'='*30}\n")
        
        # Procesar argumentos
        args = parse_arguments()
        
        # Verificar si se solicita limpiar temporales
        if args.clean_temp:
            from core.compiler import CppCompiler
            print("Limpiando archivos temporales...")
            compiler = CppCompiler()
            compiler.cleanup(keep_current=args.keep_current)
            print("Limpieza completada.")
            sys.exit(0)
        
        # Verificar dependencias
        if not args.skip_checks:
            if not check_dependencies():
                print("Advertencia: Falta una o más dependencias. El programa podría no funcionar correctamente.")
                print("Para arreglar esto, ejecute: ./run_compiler.sh --new-venv")
                response = input("¿Desea continuar de todos modos? (s/n): ").strip().lower()
                if response != 's' and response != 'si':
                    print("Operación cancelada.")
                    sys.exit(1)
        
        # Ejecutar en el modo apropiado
        if args.no_gui or args.files:
            success = run_console_mode(args.files)
            sys.exit(0 if success else 1)
        else:
            # Intentar modo GUI primero, si falla, intentar modo consola
            if not run_gui_mode():
                print("La interfaz gráfica no pudo iniciarse. Usando modo consola.")
                print("Si este error persiste, intente reinstalar las dependencias con: ./run_compiler.sh --new-venv")
                files = []
                while not files:
                    filepath = input("Introduzca la ruta a un archivo .cpp (o 'q' para salir): ").strip()
                    if filepath.lower() == 'q':
                        print("Operación cancelada por el usuario.")
                        sys.exit(0)
                    if os.path.exists(filepath) and filepath.lower().endswith('.cpp'):
                        files.append(filepath)
                    else:
                        print(f"Error: {filepath} no es un archivo C++ válido o no existe.")
                
                success = run_console_mode(files)
                sys.exit(0 if success else 1)
            
    except KeyboardInterrupt:
        print("\nOperación cancelada por el usuario")
        sys.exit(1)
    except Exception as e:
        print(f"\nError inesperado: {e}")
        print("Si este problema persiste, intente reinstalar las dependencias con: ./run_compiler.sh --new-venv")
        traceback.print_exc()
        sys.exit(1)

if __name__ == '__main__':
    main()

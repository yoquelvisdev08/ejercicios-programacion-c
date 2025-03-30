"""
Punto de entrada principal para el compilador C++ avanzado.
"""

import os
import sys
import argparse

def setup_environment():
    """Configura el entorno de ejecución."""
    # Asegurar que estamos en el directorio correcto
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    
    # Añadir el directorio actual al path
    if os.path.dirname(os.path.abspath(__file__)) not in sys.path:
        sys.path.append(os.path.dirname(os.path.abspath(__file__)))

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
        'files',
        nargs='*',
        help='Archivos .cpp a procesar'
    )
    
    return parser.parse_args()

def run_gui_mode():
    """Ejecuta el programa en modo gráfico."""
    from gui.main_window import main
    main()

def run_console_mode(files):
    """Ejecuta el programa en modo consola."""
    from core.compiler import CppCompiler
    
    if not files:
        print("Error: No se especificaron archivos para procesar")
        return
    
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
        
        # Procesar argumentos
        args = parse_arguments()
        
        # Ejecutar en el modo apropiado
        if args.no_gui or args.files:
            success = run_console_mode(args.files)
            sys.exit(0 if success else 1)
        else:
            run_gui_mode()
            
    except KeyboardInterrupt:
        print("\nOperación cancelada por el usuario")
        sys.exit(1)
    except Exception as e:
        print(f"\nError inesperado: {e}")
        sys.exit(1)

if __name__ == '__main__':
    main()

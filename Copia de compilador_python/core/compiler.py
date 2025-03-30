"""
Módulo principal para la compilación y ejecución de programas C++.
"""

import os
import subprocess
import re
import time
import traceback
from datetime import datetime

from config.settings import COMPILER_CONFIG, TEMP_DIR, OUTPUT_DIR
from utils.screenshot import take_program_screenshot, take_terminal_screenshot
from utils.pdf_generator import PDFGenerator
from utils.output_window import OutputWindow

class CppCompiler:
    """Clase principal para manejar la compilación y ejecución de programas C++."""
    
    def __init__(self, gui=None):
        """Inicializa el compilador."""
        self.compiler = COMPILER_CONFIG['compiler']
        self.flags = COMPILER_CONFIG['flags']
        self.timeout = COMPILER_CONFIG['timeout']
        self.gui = gui
        self.pdf = PDFGenerator(os.path.join(OUTPUT_DIR, "programas_cpp.pdf"))
        
        # Crear directorios necesarios
        os.makedirs(TEMP_DIR, exist_ok=True)
        os.makedirs(OUTPUT_DIR, exist_ok=True)
    
    def analyze_cpp_file(self, filepath):
        """Analiza un archivo C++ para determinar sus características."""
        try:
            with open(filepath, 'r', encoding='utf-8') as file:
                content = file.read()
            
            analysis = {
                "content": content,
                "requires_input": False,
                "input_types": [],
                "includes": [],
                "main_function": False,
                "classes": [],
                "functions": []
            }
            
            # Detectar includes
            analysis["includes"] = re.findall(r'#include\s*[<"]([^>"]+)[>"]', content)
            
            # Detectar función main
            analysis["main_function"] = bool(re.search(r'int\s+main\s*\([^)]*\)', content))
            
            # Detectar clases
            analysis["classes"] = re.findall(r'class\s+(\w+)', content)
            
            # Detectar funciones
            analysis["functions"] = re.findall(r'(?:void|int|float|double|char|bool|string)\s+(\w+)\s*\([^)]*\)', content)
            
            # Detectar tipos de entrada
            if 'cin' in content or 'getline' in content:
                analysis["requires_input"] = True
                
                # Detectar tipos de variables usadas con cin
                cin_vars = re.findall(r'cin\s*>>\s*(\w+)', content)
                for var in cin_vars:
                    # Buscar la declaración de la variable
                    var_decl = re.findall(rf'(?:int|float|double|char|string)\s+{var}\s*;', content)
                    if var_decl:
                        analysis["input_types"].append(var_decl[0].split()[0])
            
            return analysis
            
        except Exception as e:
            print(f"Error al analizar archivo: {e}")
            traceback.print_exc()
            return {"error": str(e)}
    
    def compile_file(self, filepath):
        """Compila un archivo C++."""
        try:
            basename = os.path.basename(filepath)
            name_without_ext = os.path.splitext(basename)[0]
            
            # Asegurar que el directorio temporal existe
            os.makedirs(TEMP_DIR, exist_ok=True)
            
            executable = os.path.join(TEMP_DIR, name_without_ext)
            
            if os.name == 'nt':  # Windows
                executable += '.exe'
            
            # Construir el comando de compilación
            compile_cmd = [self.compiler] + self.flags + [filepath, '-o', executable]
            
            print(f"\n=== Compilando {basename} ===")
            print(f"Comando: {' '.join(compile_cmd)}")
            
            # Ejecutar la compilación
            process = subprocess.run(
                compile_cmd,
                capture_output=True,
                text=True
            )
            
            if process.returncode == 0:
                print("Compilación exitosa")
                return {
                    "success": True,
                    "executable": executable,
                    "stdout": process.stdout,
                    "stderr": process.stderr
                }
            else:
                print("Error de compilación:")
                print(process.stderr)
                return {
                    "success": False,
                    "stdout": process.stdout,
                    "stderr": process.stderr
                }
                
        except Exception as e:
            print(f"Error durante la compilación: {e}")
            traceback.print_exc()
            return {
                "success": False,
                "error": str(e)
            }
    
    def execute_program(self, executable, test_input=None):
        """Ejecuta un programa compilado y captura su salida."""
        try:
            basename = os.path.basename(executable)
            name_without_ext = os.path.splitext(basename)[0]
            screenshot_path = os.path.join(TEMP_DIR, f"screenshot_{name_without_ext}.png")
            
            print(f"\n{'='*50}")
            print(f"Ejecutando: {basename}")
            print(f"{'='*50}\n")
            
            # Crear un script temporal para ejecutar el programa
            script_path = os.path.join(TEMP_DIR, f"run_{name_without_ext}.sh")
            with open(script_path, 'w') as f:
                f.write(f"""#!/bin/bash
clear
echo "{'='*50}"
echo "Ejecutando: {basename}"
echo "{'='*50}"
echo ""
{executable}
echo ""
echo "{'='*50}"
echo "Ejecución completada"
echo "Presione Enter cuando haya terminado para continuar..."
read
""")
            
            # Hacer el script ejecutable
            os.chmod(script_path, 0o755)
            
            # Configurar dimensiones específicas para la ventana (más estables)
            dimensions = "50, 45, 1200, 800"
            
            # Comando AppleScript para abrir una ventana de Terminal con tamaño específico
            # y ejecutar el script
            terminal_cmd = f"""osascript -e '
tell application "Terminal"
    do script "{script_path}"
    set bounds of front window to {{{dimensions}}}
    set number of rows of front window to 40
    set number of columns of front window to 120
    activate
end tell'"""
            
            print("Abriendo terminal y ejecutando programa...")
            os.system(terminal_cmd)
            
            # Esperar a que el usuario interactúe con el programa
            print("Esperando a que el usuario complete la ejecución...")
            time.sleep(2)  # Dar tiempo para que la ventana se abra completamente
            
            # Script para verificar si el Terminal sigue ocupado
            check_busy_script = """osascript -e '
tell application "Terminal"
    set isBusy to false
    repeat with w in windows
        repeat with t in tabs of w
            if busy of t then
                set isBusy to true
                exit repeat
            end if
        end repeat
        if isBusy then exit repeat
    end repeat
    return isBusy
end tell'"""
            
            # Esperar hasta que el Terminal ya no esté ocupado (programa terminado)
            max_wait = 30  # Tiempo máximo de espera en segundos
            wait_time = 0
            while wait_time < max_wait:
                result = os.popen(check_busy_script).read().strip()
                if result == "false":
                    break
                time.sleep(1)
                wait_time += 1
            
            # Dar tiempo para que la ventana se estabilice
            time.sleep(1)
            
            # Tomar la captura de la ventana de Terminal
            screenshot_taken = take_terminal_screenshot(
                screenshot_path,
                "Terminal"
            )
            
            # Comando para cerrar la ventana después de la captura
            close_cmd = """osascript -e '
tell application "Terminal"
    close front window
end tell'"""
            os.system(close_cmd)
            
            # Capturar la salida del programa (esto es para el PDF)
            try:
                with open(os.path.join(TEMP_DIR, f"{name_without_ext}_output.txt"), 'r') as f:
                    stdout = f.read()
                stderr = ""
            except:
                stdout = "La salida del programa se muestra en la captura de pantalla"
                stderr = ""
            
            return {
                "success": True,
                "stdout": stdout,
                "stderr": stderr,
                "screenshot": screenshot_path if screenshot_taken else None
            }
            
        except Exception as e:
            print(f"Error durante la ejecución: {e}")
            traceback.print_exc()
            return {
                "success": False,
                "error": str(e),
                "screenshot": None
            }
    
    def process_file(self, filepath):
        """Procesa un archivo C++: analiza, compila, ejecuta y documenta."""
        try:
            basename = os.path.basename(filepath)
            name_without_ext = os.path.splitext(basename)[0]
            
            print(f"\n{'='*50}")
            print(f"Procesando: {basename}")
            print(f"{'='*50}\n")
            
            # Analizar el archivo
            analysis = self.analyze_cpp_file(filepath)
            if "error" in analysis:
                raise Exception(f"Error al analizar el archivo: {analysis['error']}")
            
            # Compilar
            compile_result = self.compile_file(filepath)
            if not compile_result["success"]:
                # Documentar el error de compilación
                compiler_info = f"""Compilador: {self.compiler}
Flags: {' '.join(self.flags)}
Fecha: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}
Estado: Error en compilación
Error:
{compile_result['stderr']}"""
                
                self.pdf.add_program(
                    name_without_ext,
                    analysis["content"],
                    compiler_info
                )
                return compile_result
            
            print("\nPrograma compilado exitosamente.")
            print("Iniciando ejecución... Por favor:")
            print("1. Interactúe con el programa si es necesario")
            print("2. Revise la salida")
            print("3. Presione Enter cuando haya terminado para tomar la captura")
            print("4. Espere a que se procese el siguiente archivo\n")
            
            # Ejecutar
            execution_result = self.execute_program(
                compile_result["executable"]
            )
            
            # Verificar si hay captura
            screenshot = None
            if execution_result.get("screenshot") and os.path.exists(execution_result["screenshot"]):
                screenshot = execution_result["screenshot"]
                print(f"Captura encontrada: {screenshot}")
            
            # Documentar el resultado
            compiler_info = f"""Compilador: {self.compiler}
Flags: {' '.join(self.flags)}
Fecha: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}
Estado: {'Ejecución exitosa' if execution_result['success'] else 'Error en ejecución'}
Salida:
{execution_result.get('stdout', '')}"""
            
            # Añadir error si existe
            if execution_result.get("stderr"):
                compiler_info += f"""
Error:
{execution_result.get("stderr", "")}"""
            
            self.pdf.add_program(
                name_without_ext,
                analysis["content"],
                compiler_info,
                screenshot
            )
            
            print(f"\nProcesamiento de {basename} completado.")
            print("Puede continuar con el siguiente archivo...")
            
            return {
                "success": execution_result["success"],
                "compile_result": compile_result,
                "execution_result": execution_result
            }
            
        except Exception as e:
            print(f"Error al procesar archivo: {e}")
            traceback.print_exc()
            return {
                "success": False,
                "error": str(e)
            }
    
    def cleanup(self):
        """Limpia los archivos temporales."""
        try:
            print("\n=== Limpiando archivos temporales ===")
            
            if os.path.exists(TEMP_DIR):
                for filename in os.listdir(TEMP_DIR):
                    filepath = os.path.join(TEMP_DIR, filename)
                    try:
                        if os.path.isfile(filepath):
                            os.remove(filepath)
                            print(f"Eliminado: {filename}")
                    except Exception as e:
                        print(f"Error al eliminar {filename}: {e}")
                
                os.rmdir(TEMP_DIR)
                print("Directorio temporal eliminado")
            
        except Exception as e:
            print(f"Error durante la limpieza: {e}")
            traceback.print_exc()
    
    def save_pdf(self):
        """Guarda el PDF con los resultados."""
        return self.pdf.save()

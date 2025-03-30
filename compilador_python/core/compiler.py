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
from core.analyzer import CppAnalyzer

class CppCompiler:
    """Clase principal para manejar la compilación y ejecución de programas C++."""
    
    def __init__(self, gui=None):
        """Inicializa el compilador."""
        self.compiler = COMPILER_CONFIG['compiler']
        self.flags = COMPILER_CONFIG['flags']
        self.timeout = COMPILER_CONFIG['timeout']
        self.gui = gui
        self.pdf = PDFGenerator(os.path.join(OUTPUT_DIR, "programas_cpp.pdf"))
        self.analyzer = CppAnalyzer()
        self.processed_files = []  # Lista para mantener registro de archivos procesados
        
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
"{executable}" # Se agregan comillas para manejar rutas con espacios
echo ""
echo "{'='*50}"
echo "Ejecución completada"
echo "Presione Enter cuando haya terminado para continuar..."
read
""")
            
            # Hacer el script ejecutable
            os.chmod(script_path, 0o755)
            
            # Guardar la salida para el PDF
            output_file = os.path.join(TEMP_DIR, f"{name_without_ext}_output.txt")
            
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
            terminal_process = os.system(terminal_cmd)
            
            if terminal_process != 0:
                print(f"Advertencia: El comando de terminal devolvió código {terminal_process}")
                print("Intentando método alternativo...")
                
                # Método alternativo para ejecutar el programa directamente
                try:
                    direct_cmd = f"""osascript -e '
tell application "Terminal"
    do script "bash {script_path}"
    activate
end tell'"""
                    os.system(direct_cmd)
                except Exception as term_ex:
                    print(f"Error al abrir Terminal: {term_ex}")
                    raise Exception(f"No se pudo iniciar el terminal: {term_ex}")
            
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
            max_wait = self.timeout  # Usar el timeout configurado
            wait_time = 0
            while wait_time < max_wait:
                try:
                    result = os.popen(check_busy_script).read().strip()
                    if result.lower() == "false":
                        print("Ejecución del programa completada")
                        break
                except Exception as check_ex:
                    print(f"Error al verificar estado de terminal: {check_ex}")
                    # Continuamos el bucle en caso de error
                
                time.sleep(1)
                wait_time += 1
                
                # Informar progreso cada 5 segundos
                if wait_time % 5 == 0:
                    print(f"Esperando... ({wait_time}/{max_wait}s)")
            
            # Avisar si se alcanzó el tiempo máximo
            if wait_time >= max_wait:
                print(f"Se alcanzó el tiempo máximo de espera ({max_wait}s). Procediendo con la captura...")
            
            # Dar tiempo para que la ventana se estabilice
            time.sleep(1)
            
            # Intentar tomar la captura varias veces si es necesario
            screenshot_taken = False
            max_attempts = 3
            for attempt in range(max_attempts):
                print(f"Intento de captura #{attempt+1}...")
                screenshot_taken = take_terminal_screenshot(screenshot_path, "Terminal")
                if screenshot_taken:
                    print("Captura de pantalla exitosa")
                    break
                else:
                    print(f"Intento {attempt+1} fallido. {'Reintentando...' if attempt < max_attempts-1 else 'No más intentos.'}")
                    time.sleep(1)  # Esperar antes de reintentar
            
            # Comando para cerrar la ventana después de la captura
            close_cmd = """osascript -e '
tell application "Terminal"
    close front window
end tell'"""
            try:
                os.system(close_cmd)
            except Exception as close_ex:
                print(f"Advertencia: Error al cerrar la ventana de Terminal: {close_ex}")
            
            # Capturar la salida del programa (esto es para el PDF)
            stdout = ""
            stderr = ""
            try:
                # Intentar leer la salida capturada si existe
                if os.path.exists(output_file):
                    with open(output_file, 'r') as f:
                        stdout = f.read()
                else:
                    # Si no hay archivo de salida, generar un mensaje
                    stdout = "La salida del programa se muestra en la captura de pantalla"
            except Exception as read_ex:
                print(f"Error al leer la salida del programa: {read_ex}")
                stdout = "No se pudo leer la salida del programa. Ver captura de pantalla."
            
            return {
                "success": True,
                "stdout": stdout,
                "stderr": stderr,
                "screenshot": screenshot_path if screenshot_taken else None,
                "execution_time": wait_time
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
            
            # Agregar a la lista de archivos procesados
            if filepath not in self.processed_files:
                self.processed_files.append(filepath)
            
            print(f"\n{'='*50}")
            print(f"Procesando: {basename}")
            print(f"{'='*50}\n")
            
            # Analizar el archivo usando nuestro analizador avanzado
            analysis = self.analyzer.analyze_file(filepath)
            if "error" in analysis:
                raise Exception(f"Error al analizar el archivo: {analysis['error']}")
            
            print(f"Tipo de programa detectado: {analysis['type'].upper()}")
            print(f"Complejidad estimada: {analysis['complexity']}/100")
            if analysis["requires_input"]:
                print(f"Requiere entrada del usuario: Sí")
                if analysis["input_types"]:
                    print(f"Tipos de entrada: {', '.join(analysis['input_types'])}")
            else:
                print(f"Requiere entrada del usuario: No")
            
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
                
                # Obtener el contenido del archivo para el PDF
                with open(filepath, 'r', encoding='utf-8') as f:
                    file_content = f.read()
                    
                self.pdf.add_program({
                    'name': name_without_ext,
                    'source_code': file_content,
                    'output': compiler_info
                })
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
Tipo: {analysis['type'].upper()}
Complejidad: {analysis['complexity']}/100
Salida:
{execution_result.get('stdout', '')}"""
            
            # Añadir error si existe
            if execution_result.get("stderr"):
                compiler_info += f"""
Error:
{execution_result.get("stderr", "")}"""
            
            # Obtener el contenido del archivo para el PDF
            with open(filepath, 'r', encoding='utf-8') as f:
                file_content = f.read()
            
            # Usar el tipo detectado por el analizador
            self.pdf.add_program({
                'name': name_without_ext,
                'source_code': file_content,
                'output': compiler_info,
                'screenshot': screenshot
            }, analysis["type"])
            
            print(f"\nProcesamiento de {basename} completado.")
            print("Puede continuar con el siguiente archivo...")
            
            return {
                "success": execution_result["success"],
                "compile_result": compile_result,
                "execution_result": execution_result,
                "analysis": analysis
            }
            
        except Exception as e:
            print(f"Error al procesar archivo: {e}")
            traceback.print_exc()
            return {
                "success": False,
                "error": str(e)
            }
    
    def is_current_session_file(self, filepath):
        """Determina si un archivo pertenece a la sesión actual.
        
        Args:
            filepath (str): Ruta del archivo a verificar
            
        Returns:
            bool: True si el archivo pertenece a la sesión actual
        """
        if not self.processed_files:
            return False
            
        try:
            basename = os.path.basename(filepath)
            name_without_ext = os.path.splitext(basename)[0]
            
            # Verificar si el archivo está relacionado con algún archivo procesado
            for processed_file in self.processed_files:
                processed_basename = os.path.splitext(os.path.basename(processed_file))[0]
                
                # Patrones de archivos generados para cada programa
                patterns = [
                    f"screenshot_{processed_basename}",
                    f"run_{processed_basename}.sh",
                    processed_basename,
                    f"{processed_basename}_output.txt"
                ]
                
                # Si el nombre del archivo coincide con algún patrón, es un archivo de la sesión actual
                if any(pattern in name_without_ext for pattern in patterns):
                    return True
            
            return False
            
        except Exception as e:
            if self.gui:
                self.gui.log(f"Error al verificar archivo de sesión: {str(e)}", "warning")
            return False
            
    def cleanup(self, keep_current=True):
        """Limpia los archivos temporales.
        
        Args:
            keep_current (bool): Si es True, mantiene los archivos de la sesión actual
        """
        try:
            if not os.path.exists(TEMP_DIR):
                return
            
            # Obtener la lista de archivos a eliminar
            files_to_delete = []
            for filename in os.listdir(TEMP_DIR):
                filepath = os.path.join(TEMP_DIR, filename)
                
                # Siempre eliminar archivos .cleaned
                if filename.endswith('.cleaned'):
                    files_to_delete.append(filepath)
                    continue
                
                # Si keep_current es True y hay archivos procesados, preservar archivos de la sesión actual
                if keep_current and self.processed_files and self.is_current_session_file(filepath):
                    continue
                
                # Agregar el archivo a la lista de eliminación
                files_to_delete.append(filepath)
            
            # Eliminar los archivos
            for filepath in files_to_delete:
                try:
                    if os.path.exists(filepath):
                        os.remove(filepath)
                        if self.gui:
                            self.gui.log(f"Eliminado: {os.path.basename(filepath)}")
                except Exception as e:
                    if self.gui:
                        self.gui.log(f"No se pudo eliminar {os.path.basename(filepath)}: {str(e)}", "warning")
            
            # Crear un nuevo archivo .cleaned para marcar la limpieza
            cleanup_marker = os.path.join(TEMP_DIR, f".cleaned {len(os.listdir(TEMP_DIR))}")
            with open(cleanup_marker, 'w') as f:
                pass
            
        except Exception as e:
            if self.gui:
                self.gui.log(f"Error durante la limpieza: {str(e)}", "error")
            raise
    
    def save_pdf(self):
        """Guarda el PDF con todos los programas procesados."""
        try:
            print("Generando PDF de programas procesados...")
            result = self.pdf.save_pdf()
            
            # Verificar si el archivo existe aunque el método haya devuelto False
            if os.path.exists(self.pdf.output_path) and os.path.getsize(self.pdf.output_path) > 0:
                print(f"PDF generado correctamente en: {self.pdf.output_path}")
                print(f"Tamaño: {os.path.getsize(self.pdf.output_path) / 1024:.2f} KB")
                return True
                
            if result:
                print("PDF generado correctamente.")
                return True
            else:
                print("Error al generar el PDF.")
                return False
        except Exception as e:
            print(f"Error al guardar el PDF: {e}")
            traceback.print_exc()
            
            # Verificar si a pesar del error el PDF se generó
            if os.path.exists(self.pdf.output_path) and os.path.getsize(self.pdf.output_path) > 0:
                print(f"A pesar del error, el PDF fue generado en: {self.pdf.output_path}")
                return True
                
            return False

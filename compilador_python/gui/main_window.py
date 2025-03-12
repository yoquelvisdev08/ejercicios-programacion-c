"""
Ventana principal de la interfaz gráfica del compilador.
"""

import os
import tkinter as tk
from tkinter import ttk, messagebox
import tkinter.filedialog as filedialog
from tkinter import scrolledtext
from datetime import datetime
import threading
import queue
import traceback

try:
    import tkinterdnd2
    DRAG_DROP_SUPPORT = True
except ImportError:
    DRAG_DROP_SUPPORT = False
    print("Advertencia: No se pudo importar tkinterdnd2. El arrastrar y soltar no estará disponible.")

from config.settings import GUI_CONFIG, COMPILER_CONFIG
from core.compiler import CppCompiler

class CompilerGUI:
    """Ventana principal del compilador C++."""
    
    def __init__(self):
        """Inicializar la ventana principal."""
        # Crear la ventana principal
        if DRAG_DROP_SUPPORT:
            self.root = tkinterdnd2.TkinterDnD.Tk()
        else:
            self.root = tk.Tk()
        
        self.setup_window()
        self.create_widgets()
        self.setup_compiler()
        
        # Cola para capturas de pantalla
        self.screenshot_queue = queue.Queue()
    
    def setup_window(self):
        """Configura la ventana principal."""
        self.root.title("Compilador C++ Avanzado")
        self.root.geometry("1000x700")
        self.root.minsize(800, 600)
        
        # Configurar tema
        self.root.configure(bg='#1a202c')
        style = ttk.Style()
        style.configure("Main.TFrame", background='#1a202c')
        style.configure("Card.TFrame", background='#2d3748')
        
        # Estilos para etiquetas
        style.configure("Header.TLabel",
                       font=('Helvetica', 20, 'bold'),
                       foreground='#63b3ed',
                       background='#1a202c')
        
        style.configure("Subheader.TLabel",
                       font=('Helvetica', 11),
                       foreground='#a0aec0',
                       background='#1a202c')
        
        # Estilo para botones
        style.configure("Compile.TButton",
                       font=('Helvetica', 11, 'bold'),
                       padding=10)
        
        # Estilo para entradas de texto
        style.configure("Config.TEntry",
                       fieldbackground='#2d3748',
                       foreground='#e2e8f0')
        
        # Estilo para pestañas
        style.configure("TNotebook", background='#1a202c')
        style.configure("TNotebook.Tab", 
                      font=('Helvetica', 11),
                      padding=[10, 5],
                      background='#2d3748',
                      foreground='#e2e8f0')
        style.map("TNotebook.Tab",
                background=[("selected", '#4a5568')],
                foreground=[("selected", '#ffffff')])
    
    def create_widgets(self):
        """Crea los widgets de la interfaz."""
        # Frame principal
        main_frame = ttk.Frame(self.root, style="Main.TFrame")
        main_frame.pack(fill="both", expand=True, padx=20, pady=20)
        
        # Título
        header_frame = ttk.Frame(main_frame, style="Main.TFrame")
        header_frame.pack(fill="x", pady=(0, 20))
        
        ttk.Label(header_frame,
                 text="✨ Compilador C++ Avanzado",
                 style="Header.TLabel").pack(anchor="w")
        
        ttk.Label(header_frame,
                 text="Compile, pruebe y documente sus programas C++ de forma sencilla",
                 style="Subheader.TLabel").pack(anchor="w")
        
        # Crear notebook (pestañas)
        self.notebook = ttk.Notebook(main_frame)
        self.notebook.pack(fill="both", expand=True)
        
        # Crear pestaña de compilación individual
        self.single_tab = ttk.Frame(self.notebook, style="Main.TFrame")
        self.notebook.add(self.single_tab, text="📄 Compilación Individual")
        
        # Crear pestaña de compilación por lotes
        self.batch_tab = ttk.Frame(self.notebook, style="Main.TFrame")
        self.notebook.add(self.batch_tab, text="📚 Compilación por Lotes")
        
        # Configurar pestaña de compilación individual
        self.setup_single_compilation_tab()
        
        # Configurar pestaña de compilación por lotes
        self.setup_batch_compilation_tab()
        
        # Barra de estado
        self.status_var = tk.StringVar(value="Listo")
        status_bar = ttk.Label(
            self.root,
            textvariable=self.status_var,
            relief=tk.SUNKEN,
            padding=5
        )
        status_bar.pack(fill=tk.X, side=tk.BOTTOM)
    
    def setup_single_compilation_tab(self):
        """Configura la pestaña de compilación individual."""
        # Panel izquierdo
        left_panel = ttk.Frame(self.single_tab, style="Card.TFrame")
        left_panel.pack(side="left", fill="both", expand=True, padx=(0, 10))
        
        # Configuración del compilador
        config_frame = ttk.LabelFrame(left_panel, text="⚙️ Configuración", padding=10)
        config_frame.pack(fill="x", pady=(0, 10))
        
        # Variables de configuración
        self.compiler_var = tk.StringVar(value=COMPILER_CONFIG["compiler"])
        self.flags_var = tk.StringVar(value=" ".join(COMPILER_CONFIG["flags"]))
        self.timeout_var = tk.StringVar(value=str(COMPILER_CONFIG["timeout"]))
        
        # Grid de configuración
        ttk.Label(config_frame, text="🔧 Compilador:").grid(row=0, column=0, sticky="w", padx=5, pady=2)
        ttk.Entry(config_frame, textvariable=self.compiler_var, style="Config.TEntry").grid(row=0, column=1, sticky="ew", padx=5, pady=2)
        
        ttk.Label(config_frame, text="🚩 Flags:").grid(row=1, column=0, sticky="w", padx=5, pady=2)
        ttk.Entry(config_frame, textvariable=self.flags_var, style="Config.TEntry").grid(row=1, column=1, sticky="ew", padx=5, pady=2)
        
        ttk.Label(config_frame, text="⏱️ Timeout:").grid(row=2, column=0, sticky="w", padx=5, pady=2)
        ttk.Entry(config_frame, textvariable=self.timeout_var, style="Config.TEntry").grid(row=2, column=1, sticky="ew", padx=5, pady=2)
        
        config_frame.columnconfigure(1, weight=1)
        
        # Área de archivos
        files_frame = ttk.LabelFrame(left_panel, text="📄 Archivos", padding=10)
        files_frame.pack(fill="both", expand=True)
        
        # Área de arrastrar y soltar
        drop_text = "🔄 Arrastre archivos .cpp aquí" if DRAG_DROP_SUPPORT else "📎 Use el botón 'Añadir Archivos'"
        self.drop_target = tk.Text(files_frame,
                                 height=5,
                                 font=('Helvetica', 10),
                                 bg='#2d3748',
                                 fg='#e2e8f0',
                                 relief="flat")
        self.drop_target.insert("1.0", drop_text)
        self.drop_target.configure(state="disabled")
        self.drop_target.pack(fill="both", expand=True, pady=(0, 10))
        
        if DRAG_DROP_SUPPORT:
            self.drop_target.drop_target_register('DND_Files')
            self.drop_target.dnd_bind('<<Drop>>', self.on_drop)
        
        # Lista de archivos
        self.files_list = tk.Listbox(files_frame,
                                   height=10,
                                   font=('Helvetica', 10),
                                   bg='#2d3748',
                                   fg='#e2e8f0',
                                   selectmode=tk.MULTIPLE,
                                   relief="flat")
        self.files_list.pack(fill="both", expand=True)
        
        # Botones de archivos
        buttons_frame = ttk.Frame(files_frame)
        buttons_frame.pack(fill="x", pady=(10, 0))
        
        ttk.Button(buttons_frame,
                  text="📥 Añadir Archivos",
                  command=self.add_files).pack(side="left", padx=2)
        
        ttk.Button(buttons_frame,
                  text="🗑️ Eliminar",
                  command=self.remove_selected).pack(side="left", padx=2)
        
        ttk.Button(buttons_frame,
                  text="🧹 Limpiar Todo",
                  command=self.clear_files).pack(side="left", padx=2)
        
        # Frame para los botones de compilación
        compile_buttons_frame = ttk.Frame(left_panel)
        compile_buttons_frame.pack(fill="x", pady=10)
        
        # Botón solo compilar
        compile_only_button = ttk.Button(compile_buttons_frame,
                                text="🔨 Solo Compilar",
                                command=self.compile_files_only,
                                style="Compile.TButton")
        compile_only_button.pack(fill="x", pady=(0, 5))
        
        # Botón de compilación con PDF
        compile_pdf_button = ttk.Button(compile_buttons_frame,
                                  text="🚀 Compilar y Generar PDF",
                                  command=self.compile_files,
                                  style="Compile.TButton")
        compile_pdf_button.pack(fill="x")
        
        # Panel derecho (log)
        right_panel = ttk.Frame(self.single_tab, style="Card.TFrame")
        right_panel.pack(side="right", fill="both", expand=True)
        
        # Área de log
        log_frame = ttk.LabelFrame(right_panel, text="📊 Registro de Operaciones", padding=10)
        log_frame.pack(fill="both", expand=True)
        
        self.log_text = scrolledtext.ScrolledText(
            log_frame,
            wrap=tk.WORD,
            font=('Consolas', 10),
            bg='#1a202c',
            fg='#e2e8f0'
        )
        self.log_text.pack(fill="both", expand=True)
        
        # Barra de progreso
        self.progress_var = tk.DoubleVar()
        self.progress_bar = ttk.Progressbar(
            log_frame,
            variable=self.progress_var,
            maximum=100,
            mode='determinate'
        )
        self.progress_bar.pack(fill="x", pady=(10, 0))
    
    def setup_batch_compilation_tab(self):
        """Configura la pestaña de compilación por lotes."""
        # Panel izquierdo
        left_panel = ttk.Frame(self.batch_tab, style="Card.TFrame")
        left_panel.pack(side="left", fill="both", expand=True, padx=(0, 10))
        
        # Configuración de carpeta
        folder_frame = ttk.LabelFrame(left_panel, text="📁 Carpeta de Proyectos", padding=10)
        folder_frame.pack(fill="x", pady=(0, 10))
        
        # Variable para la carpeta
        self.folder_var = tk.StringVar()
        
        # Widget de selección de carpeta
        folder_entry = ttk.Entry(folder_frame, textvariable=self.folder_var, style="Config.TEntry")
        folder_entry.pack(side="left", fill="x", expand=True, padx=(0, 5))
        
        ttk.Button(folder_frame,
                  text="📂 Explorar",
                  command=self.select_folder).pack(side="right")
        
        # Configuración del patrón de búsqueda
        pattern_frame = ttk.LabelFrame(left_panel, text="🔍 Patrón de Búsqueda", padding=10)
        pattern_frame.pack(fill="x", pady=(0, 10))
        
        # Variable para el patrón de búsqueda
        self.pattern_var = tk.StringVar(value="*.cpp")
        
        ttk.Label(pattern_frame, text="Buscar archivos:").pack(anchor="w")
        ttk.Entry(pattern_frame, textvariable=self.pattern_var, style="Config.TEntry").pack(fill="x", pady=5)
        
        ttk.Button(pattern_frame,
                 text="🔍 Buscar Archivos",
                 command=self.search_files).pack(fill="x")
        
        # Área de archivos encontrados
        files_frame = ttk.LabelFrame(left_panel, text="📄 Archivos Encontrados", padding=10)
        files_frame.pack(fill="both", expand=True)
        
        # Lista de archivos
        self.batch_files_list = tk.Listbox(files_frame,
                                         height=10,
                                         font=('Helvetica', 10),
                                         bg='#2d3748',
                                         fg='#e2e8f0',
                                         selectmode=tk.MULTIPLE,
                                         relief="flat")
        self.batch_files_list.pack(fill="both", expand=True)
        
        # Frame de información
        info_frame = ttk.Frame(files_frame)
        info_frame.pack(fill="x", pady=5)
        
        # Etiqueta para mostrar el número de archivos
        self.files_count_var = tk.StringVar(value="0 archivos encontrados")
        ttk.Label(info_frame, textvariable=self.files_count_var).pack(side="left")
        
        # Botones de selección
        ttk.Button(info_frame,
                  text="✅ Seleccionar Todos",
                  command=self.select_all_files).pack(side="right", padx=2)
        
        ttk.Button(info_frame,
                  text="❌ Deseleccionar Todos",
                  command=self.deselect_all_files).pack(side="right", padx=2)
        
        # Botón de compilación por lotes
        compile_button = ttk.Button(left_panel,
                                   text="🚀 Compilar Lote",
                                   command=self.compile_batch,
                                   style="Compile.TButton")
        compile_button.pack(fill="x", pady=10)
        
        # Panel derecho (log)
        right_panel = ttk.Frame(self.batch_tab, style="Card.TFrame")
        right_panel.pack(side="right", fill="both", expand=True)
        
        # Área de log
        log_frame = ttk.LabelFrame(right_panel, text="📊 Registro de Operaciones por Lotes", padding=10)
        log_frame.pack(fill="both", expand=True)
        
        self.batch_log_text = scrolledtext.ScrolledText(
            log_frame,
            wrap=tk.WORD,
            font=('Consolas', 10),
            bg='#1a202c',
            fg='#e2e8f0'
        )
        self.batch_log_text.pack(fill="both", expand=True)
        
        # Barra de progreso
        self.batch_progress_var = tk.DoubleVar()
        self.batch_progress_bar = ttk.Progressbar(
            log_frame,
            variable=self.batch_progress_var,
            maximum=100,
            mode='determinate'
        )
        self.batch_progress_bar.pack(fill="x", pady=(10, 0))
    
    def setup_compiler(self):
        """Configura el compilador."""
        self.compiler = CppCompiler(gui=self)
        self.selected_files = []
        self.batch_selected_files = []
    
    def select_folder(self):
        """Abre un diálogo para seleccionar una carpeta."""
        folder = filedialog.askdirectory(title="Seleccionar carpeta con archivos C++")
        if folder:
            self.folder_var.set(folder)
            self.batch_log(f"Carpeta seleccionada: {folder}")
    
    def search_files(self):
        """Busca archivos en la carpeta seleccionada según el patrón."""
        folder = self.folder_var.get()
        pattern = self.pattern_var.get()
        
        if not folder:
            messagebox.showwarning("Advertencia", "Por favor, seleccione una carpeta primero.")
            return
        
        import glob
        import os
        
        # Buscar archivos según el patrón
        self.batch_log(f"Buscando archivos {pattern} en {folder}...")
        files = glob.glob(os.path.join(folder, pattern), recursive=True)
        
        # Actualizar la lista
        self.batch_files_list.delete(0, tk.END)
        self.batch_selected_files = []
        
        for file in files:
            if os.path.isfile(file):
                self.batch_files_list.insert(tk.END, file)
                self.batch_selected_files.append(file)
        
        # Actualizar el contador de archivos
        count = len(self.batch_selected_files)
        self.files_count_var.set(f"{count} archivo{'s' if count != 1 else ''} encontrado{'s' if count != 1 else ''}")
        
        self.batch_log(f"Se encontraron {count} archivos.")
    
    def select_all_files(self):
        """Selecciona todos los archivos en la lista de compilación por lotes."""
        self.batch_files_list.select_set(0, tk.END)
    
    def deselect_all_files(self):
        """Deselecciona todos los archivos en la lista de compilación por lotes."""
        self.batch_files_list.selection_clear(0, tk.END)
    
    def batch_log(self, message):
        """Añade un mensaje al área de log de compilación por lotes."""
        timestamp = datetime.now().strftime("[%H:%M:%S]")
        self.batch_log_text.insert(tk.END, f"{timestamp} {message}\n")
        self.batch_log_text.see(tk.END)
    
    def compile_batch(self):
        """Compila todos los archivos seleccionados en modo lote."""
        selected_indices = self.batch_files_list.curselection()
        if not selected_indices:
            messagebox.showwarning("Advertencia", "Por favor, seleccione al menos un archivo para compilar.")
            return
        
        # Obtener los archivos seleccionados
        files_to_compile = [self.batch_selected_files[i] for i in selected_indices]
        
        # Deshabilitar la interfaz durante la compilación
        self.disable_interface()
        
        # Iniciar la compilación en un hilo separado
        thread = threading.Thread(target=self.process_batch_files, args=(files_to_compile,))
        thread.daemon = True
        thread.start()
    
    def process_batch_files(self, files):
        """Procesa un lote de archivos C++ en un hilo separado."""
        try:
            total_files = len(files)
            self.status_var.set(f"Compilando {total_files} archivos...")
            self.batch_log(f"Iniciando compilación por lotes de {total_files} archivos...")
            
            success_count = 0
            error_count = 0
            
            for i, file in enumerate(files):
                # Actualizar progreso
                progress = (i / total_files) * 100
                self.batch_progress_var.set(progress)
                self.status_var.set(f"Compilando {i+1}/{total_files}: {os.path.basename(file)}")
                
                # Procesar el archivo
                self.batch_log(f"Procesando ({i+1}/{total_files}): {file}")
                
                # Compilar archivo sin generar PDF
                compile_result = self.compiler.compile_file(file)
                
                if compile_result["success"]:
                    self.batch_log(f"✅ Archivo compilado correctamente: {os.path.basename(file)}")
                    success_count += 1
                else:
                    self.batch_log(f"❌ Error al compilar: {os.path.basename(file)}")
                    if "stderr" in compile_result:
                        error_text = compile_result["stderr"]
                        # Limitar la cantidad de texto de error para evitar sobrecarga
                        if len(error_text) > 500:
                            error_text = error_text[:500] + "... (mensaje truncado)"
                        self.batch_log(f"  Error: {error_text}")
                    error_count += 1
            
            # Compilación completada
            self.batch_progress_var.set(100)
            self.batch_log(f"Compilación por lotes finalizada. Éxitos: {success_count}, Errores: {error_count}")
            
            # Mostrar mensaje final según el resultado
            if error_count == 0:
                messagebox.showinfo("Éxito", f"La compilación por lotes ha finalizado correctamente.\nSe compilaron {success_count} archivos sin errores.")
            else:
                messagebox.showwarning("Compilación completada con errores", 
                                    f"La compilación finalizó con {error_count} errores.\n"
                                    f"Se compilaron correctamente {success_count} de {total_files} archivos.")
            
        except Exception as e:
            self.batch_log(f"❌ Error durante la compilación por lotes: {str(e)}")
            traceback.print_exc()
            
        finally:
            # Restaurar la interfaz
            self.restore_interface()
            self.status_var.set("Listo")
    
    def on_drop(self, event):
        """Maneja el evento de soltar archivos."""
        files = self.root.tk.splitlist(event.data)
        self.add_files_to_list(files)
    
    def add_files(self):
        """Abre un diálogo para seleccionar archivos."""
        files = filedialog.askopenfilenames(
            title="Seleccionar archivos C++",
            filetypes=[("Archivos C++", "*.cpp"), ("Todos los archivos", "*.*")]
        )
        self.add_files_to_list(files)
    
    def add_files_to_list(self, files):
        """Añade archivos a la lista."""
        for file in files:
            if file.lower().endswith('.cpp'):
                if file not in self.selected_files:
                    self.selected_files.append(file)
                    self.files_list.insert(tk.END, os.path.basename(file))
                    self.log(f"Archivo añadido: {os.path.basename(file)}")
    
    def remove_selected(self):
        """Elimina los archivos seleccionados."""
        selected = self.files_list.curselection()
        for index in reversed(selected):
            self.files_list.delete(index)
            self.selected_files.pop(index)
    
    def clear_files(self):
        """Limpia la lista de archivos."""
        self.files_list.delete(0, tk.END)
        self.selected_files.clear()
        self.log("Lista de archivos limpiada")
    
    def log(self, message):
        """Añade un mensaje al área de log."""
        timestamp = datetime.now().strftime("[%H:%M:%S]")
        self.log_text.insert(tk.END, f"{timestamp} {message}\n")
        self.log_text.see(tk.END)
    
    def compile_files(self):
        """Compila los archivos seleccionados."""
        if not self.selected_files:
            messagebox.showwarning("Advertencia", "No hay archivos para compilar.")
            return
        
        # Actualizar la configuración del compilador
        self.update_compiler_config()
        
        # Deshabilitar la interfaz durante la compilación
        self.disable_interface()
        
        # Iniciar la compilación en un hilo separado
        thread = threading.Thread(target=self.process_files)
        thread.daemon = True
        thread.start()
    
    def update_compiler_config(self):
        """Actualiza la configuración del compilador según los valores de la interfaz."""
        self.compiler.compiler = self.compiler_var.get()
        self.compiler.flags = self.flags_var.get().split()
        try:
            self.compiler.timeout = int(self.timeout_var.get())
        except ValueError:
            self.log("Advertencia: Valor de timeout inválido, usando valor predeterminado")
            self.compiler.timeout = COMPILER_CONFIG["timeout"]
    
    def process_files(self):
        """Procesa los archivos seleccionados en un hilo separado."""
        try:
            total_files = len(self.selected_files)
            self.status_var.set(f"Compilando {total_files} archivos...")
            self.log(f"Iniciando compilación de {total_files} archivos...")
            
            for i, file in enumerate(self.selected_files):
                # Actualizar progreso
                progress = (i / total_files) * 100
                self.progress_var.set(progress)
                self.status_var.set(f"Compilando {i+1}/{total_files}: {os.path.basename(file)}")
                
                # Procesar el archivo
                self.log(f"Procesando ({i+1}/{total_files}): {file}")
                result = self.compiler.process_file(file)
                
                if result["success"]:
                    self.log(f"✓ Archivo procesado correctamente: {os.path.basename(file)}")
                else:
                    self.log(f"✗ Error al procesar: {os.path.basename(file)}")
                    if "error" in result:
                        self.log(f"  Error: {result['error']}")
            
            # Compilación completada
            self.progress_var.set(100)
            self.log("Generando PDF...")
            
            if self.compiler.save_pdf():
                self.log("✓ PDF generado correctamente")
                messagebox.showinfo("Éxito", "La compilación ha finalizado correctamente y se ha generado el PDF.")
            else:
                self.log("✗ Error al generar el PDF")
                messagebox.showerror("Error", "Ha ocurrido un error al generar el PDF.")
            
            self.compiler.cleanup()
            
        except Exception as e:
            self.log(f"✗ Error durante la compilación: {str(e)}")
            traceback.print_exc()
            
        finally:
            # Restaurar la interfaz
            self.restore_interface()
            self.status_var.set("Listo")
    
    def disable_interface(self):
        """Deshabilita la interfaz durante la compilación."""
        # En lugar de intentar desactivar el Notebook, 
        # simplemente desactivamos los botones y controles importantes
        for widget in self.root.winfo_children():
            if isinstance(widget, ttk.Button):
                widget.configure(state="disabled")
        
        # Función recursiva para obtener todos los widgets descendientes
        def get_all_children(widget):
            children = widget.winfo_children()
            result = list(children)
            for child in children:
                result.extend(get_all_children(child))
            return result
        
        # Desactivar botones específicos en las pestañas
        for tab in [self.single_tab, self.batch_tab]:
            for widget in get_all_children(tab):
                if isinstance(widget, (ttk.Button, ttk.Entry, tk.Listbox)):
                    try:
                        widget.configure(state="disabled")
                    except Exception as e:
                        print(f"No se pudo desactivar: {widget}, error: {e}")

    def restore_interface(self):
        """Restaura la interfaz después de la compilación."""
        # Restaurar los botones y controles importantes
        for widget in self.root.winfo_children():
            if isinstance(widget, ttk.Button):
                widget.configure(state="normal")
        
        # Función recursiva para obtener todos los widgets descendientes
        def get_all_children(widget):
            children = widget.winfo_children()
            result = list(children)
            for child in children:
                result.extend(get_all_children(child))
            return result
        
        # Restaurar botones específicos en las pestañas
        for tab in [self.single_tab, self.batch_tab]:
            for widget in get_all_children(tab):
                if isinstance(widget, ttk.Button):
                    widget.configure(state="normal")
                elif isinstance(widget, ttk.Entry):
                    widget.configure(state="normal")
                elif isinstance(widget, tk.Listbox):
                    try:
                        widget.configure(state="normal")
                    except Exception as e:
                        print(f"No se pudo restaurar: {widget}, error: {e}")
    
    def compile_files_only(self):
        """Compila los archivos seleccionados sin generar PDF."""
        if not self.selected_files:
            messagebox.showwarning("Advertencia", "No hay archivos para compilar.")
            return
        
        # Actualizar la configuración del compilador
        self.update_compiler_config()
        
        # Deshabilitar la interfaz durante la compilación
        self.disable_interface()
        
        # Iniciar la compilación en un hilo separado
        thread = threading.Thread(target=self.process_files_only)
        thread.daemon = True
        thread.start()
    
    def process_files_only(self):
        """Procesa los archivos seleccionados solo para compilación."""
        try:
            total_files = len(self.selected_files)
            self.status_var.set(f"Compilando {total_files} archivos...")
            self.log(f"Iniciando compilación de {total_files} archivos...")
            
            success_count = 0
            error_count = 0
            
            for i, file in enumerate(self.selected_files):
                # Actualizar progreso
                progress = (i / total_files) * 100
                self.progress_var.set(progress)
                self.status_var.set(f"Compilando {i+1}/{total_files}: {os.path.basename(file)}")
                
                # Compilar archivo
                self.log(f"Compilando ({i+1}/{total_files}): {file}")
                compile_result = self.compiler.compile_file(file)
                
                if compile_result["success"]:
                    self.log(f"✅ Archivo compilado correctamente: {os.path.basename(file)}")
                    success_count += 1
                else:
                    self.log(f"❌ Error al compilar: {os.path.basename(file)}")
                    if "stderr" in compile_result:
                        error_text = compile_result["stderr"]
                        # Limitar la cantidad de texto de error para evitar sobrecarga
                        if len(error_text) > 500:
                            error_text = error_text[:500] + "... (mensaje truncado)"
                        self.log(f"  Error: {error_text}")
                    error_count += 1
            
            # Compilación completada
            self.progress_var.set(100)
            
            # Mostrar mensaje de finalización
            self.log(f"Compilación finalizada. Éxitos: {success_count}, Errores: {error_count}")
            
            # Mostrar mensaje final según el resultado
            if error_count == 0:
                messagebox.showinfo("Éxito", f"La compilación ha finalizado correctamente.\nSe compilaron {success_count} archivos sin errores.")
            else:
                messagebox.showwarning("Compilación completada con errores", 
                                   f"La compilación finalizó con {error_count} errores.\n"
                                   f"Se compilaron correctamente {success_count} de {total_files} archivos.")
            
        except Exception as e:
            self.log(f"❌ Error durante la compilación: {str(e)}")
            traceback.print_exc()
            
        finally:
            # Restaurar la interfaz
            self.restore_interface()
            self.status_var.set("Listo")
    
    def run(self):
        """Ejecuta la interfaz gráfica."""
        self.root.mainloop()

def main():
    """Función principal."""
    gui = CompilerGUI()
    gui.run()

if __name__ == "__main__":
    main()

"""
Ventana principal de la interfaz gráfica del compilador.
"""

import os
import sys
import time
import traceback
import threading
import queue
import tkinter as tk
from tkinter import ttk, filedialog, messagebox
import tkinter.scrolledtext as scrolledtext
from datetime import datetime
import platform

from config.settings import GUI_CONFIG, COMPILER_CONFIG, TEMP_DIR, OUTPUT_DIR
from core.compiler import CppCompiler

# Intentar importar ttkbootstrap si está disponible
try:
    import ttkbootstrap as ttk
    from ttkbootstrap.constants import *
    USING_TTKBOOTSTRAP = True
    print("Usando ttkbootstrap para una interfaz moderna")
except ImportError:
    USING_TTKBOOTSTRAP = False
    print("ttkbootstrap no disponible, usando interfaz estándar")
    
# Verificar si estamos en Apple Silicon
IS_APPLE_SILICON = platform.system() == "Darwin" and platform.machine() == "arm64"

# Intentar importar tkinterdnd2 si no estamos en Apple Silicon
# (es incompatible con ARM64 en macOS)
if not IS_APPLE_SILICON:
    try:
        from tkinterdnd2 import TkinterDnD, DND_FILES
        USING_DRAG_DROP = True
    except ImportError:
        USING_DRAG_DROP = False
        print("tkinterdnd2 no disponible, arrastrar y soltar desactivado")
else:
    USING_DRAG_DROP = False
    print("Ejecutando en Apple Silicon - Drag and drop desactivado para compatibilidad")

def create_button(parent, text, command, style=None, side=None, padx=None, fill=None, pady=None, **kwargs):
    """Crea un botón utilizando ttkbootstrap o ttk según disponibilidad."""
    if USING_TTKBOOTSTRAP:
        btn = ttk.Button(parent, text=text, bootstyle=style, command=command, **kwargs)
    else:
        btn = ttk.Button(parent, text=text, command=command, **kwargs)
    
    if side is not None:
        if fill is not None:
            btn.pack(side=side, padx=padx, fill=fill, pady=pady)
        else:
            btn.pack(side=side, padx=padx, pady=pady)
    
    return btn

class CompilerGUI:
    """Ventana principal del compilador C++."""
    
    def __init__(self):
        """Inicializar la ventana principal."""
        # Crear la ventana principal
        if USING_TTKBOOTSTRAP:
            if USING_DRAG_DROP:
                self.root = TkinterDnD.Tk()
                self.style = ttk.Style(theme=GUI_CONFIG["bootstrap_theme"])
            else:
                self.root = ttk.Window(themename=GUI_CONFIG["bootstrap_theme"])
        else:
            if USING_DRAG_DROP:
                self.root = TkinterDnD.Tk()
            else:
                self.root = tk.Tk()
        
        self.setup_window()
        self.setup_styles()
        self.create_widgets()
        self.setup_compiler()
        
        # Cola para capturas de pantalla
        self.screenshot_queue = queue.Queue()
        
        # Nuevo atributo para controlar el estado de la GUI
        self.gui_closed = False
    
    def setup_window(self):
        """Configura la ventana principal."""
        # Establecer título y tamaño
        self.root.title("Compilador C++ Avanzado")
        
        # Usar valores predeterminados si no están definidos en GUI_CONFIG
        window_width = GUI_CONFIG.get('window_width', 1200)
        window_height = GUI_CONFIG.get('window_height', 800)
        self.root.geometry(f"{window_width}x{window_height}")
        
        # Agregar icono si está disponible
        if 'icon_path' in GUI_CONFIG and os.path.exists(GUI_CONFIG['icon_path']):
            try:
                icon = tk.PhotoImage(file=GUI_CONFIG['icon_path'])
                self.root.iconphoto(True, icon)
            except Exception as e:
                print(f"No se pudo cargar el icono: {e}")
        
        # Registrar el manejador para el cierre de la ventana
        self.root.protocol("WM_DELETE_WINDOW", self.on_close)
        
        # Configurar tema oscuro
        if not USING_TTKBOOTSTRAP:
            # Verificar que 'theme' y 'background' existen
            if 'theme' in GUI_CONFIG and 'background' in GUI_CONFIG['theme']:
                self.root.configure(bg=GUI_CONFIG['theme']['background'])
            else:
                # Usar un color predeterminado
                self.root.configure(bg='#2c3e50')
    
    def on_close(self):
        """Manejador para el cierre de la ventana."""
        self.gui_closed = True
        self.root.destroy()
    
    def setup_styles(self):
        """Configura los estilos personalizados."""
        if not USING_TTKBOOTSTRAP:
            style = ttk.Style()
            
            # Configurar colores base
            style.configure(".", 
                          background=GUI_CONFIG['theme']['background'],
                          foreground=GUI_CONFIG['theme']['text'],
                          font=(GUI_CONFIG['font_family'], 10))
            
            # Frames
            style.configure("Main.TFrame", 
                          background=GUI_CONFIG['theme']['background'])
            style.configure("Card.TFrame", 
                          background=GUI_CONFIG['theme']['card_bg'])
            
            # Etiquetas
            style.configure("Header.TLabel",
                          font=(GUI_CONFIG['font_family'], 20, 'bold'),
                          foreground=GUI_CONFIG['theme']['text'],
                          background=GUI_CONFIG['theme']['background'])
            
            style.configure("Subheader.TLabel",
                          font=(GUI_CONFIG['font_family'], 11),
                          foreground=GUI_CONFIG['theme']['text_secondary'],
                          background=GUI_CONFIG['theme']['background'])
            
            # Botones
            style.configure("Compile.TButton",
                          font=(GUI_CONFIG['font_family'], 11, 'bold'),
                          padding=10,
                          background=GUI_CONFIG['theme']['primary'])
            
            # Entradas
            style.configure("Config.TEntry",
                          fieldbackground=GUI_CONFIG['theme']['input_bg'],
                          foreground=GUI_CONFIG['theme']['text'])
            
            # Pestañas
            style.configure("TNotebook", 
                          background=GUI_CONFIG['theme']['background'])
            style.configure("TNotebook.Tab",
                          font=(GUI_CONFIG['font_family'], 11),
                          padding=[10, 5],
                          background=GUI_CONFIG['theme']['card_bg'],
                          foreground=GUI_CONFIG['theme']['text'])
            style.map("TNotebook.Tab",
                     background=[("selected", GUI_CONFIG['theme']['active'])],
                     foreground=[("selected", GUI_CONFIG['theme']['primary'])])
    
    def create_widgets(self):
        """Crea los widgets de la interfaz."""
        # Frame principal
        if USING_TTKBOOTSTRAP:
            main_frame = ttk.Frame(self.root, bootstyle="dark")
        else:
            main_frame = ttk.Frame(self.root, style="Main.TFrame")
        main_frame.pack(fill="both", expand=True, padx=20, pady=20)
        
        # Título
        header_frame = ttk.Frame(main_frame, style="Main.TFrame")
        header_frame.pack(fill="x", pady=(0, 20))
        
        if USING_TTKBOOTSTRAP:
            ttk.Label(
                header_frame,
                text="Compilador C++ Avanzado",
                font=(GUI_CONFIG['font_family'], 24, 'bold'),
                bootstyle="inverse-dark"
            ).pack(anchor="w")
            
            ttk.Label(
                header_frame,
                text="Compile, pruebe y documente sus programas C++ fácilmente",
                font=(GUI_CONFIG['font_family'], 12),
                bootstyle="secondary"
            ).pack(anchor="w")
        else:
            ttk.Label(header_frame,
                    text="✨ Compilador C++ Avanzado",
                    style="Header.TLabel").pack(anchor="w")
            
            ttk.Label(header_frame,
                    text="Compile, pruebe y documente sus programas C++ de forma sencilla",
                    style="Subheader.TLabel").pack(anchor="w")
        
        # Crear frame para botones de herramientas
        tools_frame = ttk.Frame(header_frame)
        tools_frame.pack(anchor="e", pady=(5, 0))
        
        # Botón para limpiar archivos temporales
        if USING_TTKBOOTSTRAP:
            self.clean_button = create_button(
                tools_frame,
                text="Limpiar Temporales",
                style="outline-warning",
                command=self.clean_temp_files,
                side="right", 
                padx=5
            )
        else:
            self.clean_button = ttk.Button(
                tools_frame,
                text="🧹 Limpiar Temporales",
                command=self.clean_temp_files
            )
            self.clean_button.pack(side="right", padx=5)
        
        # Crear notebook (pestañas)
        if USING_TTKBOOTSTRAP:
            self.notebook = ttk.Notebook(main_frame, bootstyle="primary")
        else:
            self.notebook = ttk.Notebook(main_frame)
        self.notebook.pack(fill="both", expand=True)
        
        # Crear pestaña de compilación individual
        self.single_tab = ttk.Frame(self.notebook)
        self.notebook.add(self.single_tab, text="Compilación Individual")
        
        # Crear pestaña de compilación por lotes
        self.batch_tab = ttk.Frame(self.notebook)
        self.notebook.add(self.batch_tab, text="Compilación por Lotes")
        
        # Configurar pestaña de compilación individual
        self.setup_single_compilation_tab()
        
        # Configurar pestaña de compilación por lotes
        self.setup_batch_compilation_tab()
        
        # Barra de estado
        self.status_var = tk.StringVar(value="Listo")
        if USING_TTKBOOTSTRAP:
            status_bar = ttk.Label(
                self.root,
                textvariable=self.status_var,
                bootstyle="secondary",
                relief="sunken",
                padding=5
            )
        else:
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
        if USING_TTKBOOTSTRAP:
            left_panel = ttk.Frame(self.single_tab, bootstyle="dark")
        else:
            left_panel = ttk.Frame(self.single_tab, style="Card.TFrame")
        left_panel.pack(side="left", fill="both", expand=True, padx=(0, 10))
        
        # Configuración del compilador
        if USING_TTKBOOTSTRAP:
            config_frame = ttk.Labelframe(left_panel, text="Configuración", padding=10, bootstyle="dark")
        else:
            config_frame = ttk.LabelFrame(left_panel, text="⚙️ Configuración", padding=10)
        config_frame.pack(fill="x", pady=(0, 10))
        
        # Variables de configuración
        self.compiler_var = tk.StringVar(value=COMPILER_CONFIG["compiler"])
        self.flags_var = tk.StringVar(value=" ".join(COMPILER_CONFIG["flags"]))
        self.timeout_var = tk.StringVar(value=str(COMPILER_CONFIG["timeout"]))
        self.autoclean_var = tk.BooleanVar(value=True)  # Variable para limpieza automática
        
        # Grid de configuración
        if USING_TTKBOOTSTRAP:
            ttk.Label(config_frame, text="Compilador:", bootstyle="primary").grid(row=0, column=0, sticky="w", padx=5, pady=2)
            ttk.Entry(config_frame, textvariable=self.compiler_var, bootstyle="primary").grid(row=0, column=1, sticky="ew", padx=5, pady=2)
            
            ttk.Label(config_frame, text="Flags:", bootstyle="primary").grid(row=1, column=0, sticky="w", padx=5, pady=2)
            ttk.Entry(config_frame, textvariable=self.flags_var, bootstyle="primary").grid(row=1, column=1, sticky="ew", padx=5, pady=2)
            
            ttk.Label(config_frame, text="Timeout:", bootstyle="primary").grid(row=2, column=0, sticky="w", padx=5, pady=2)
            ttk.Entry(config_frame, textvariable=self.timeout_var, bootstyle="primary").grid(row=2, column=1, sticky="ew", padx=5, pady=2)
            
            # Opción para limpiar archivos temporales
            ttk.Checkbutton(
                config_frame, 
                text="Limpiar archivos temporales", 
                variable=self.autoclean_var,
                bootstyle="primary-round-toggle"
            ).grid(row=3, column=0, columnspan=2, sticky="w", padx=5, pady=5)
        else:
            ttk.Label(config_frame, text="🔧 Compilador:").grid(row=0, column=0, sticky="w", padx=5, pady=2)
            ttk.Entry(config_frame, textvariable=self.compiler_var, style="Config.TEntry").grid(row=0, column=1, sticky="ew", padx=5, pady=2)
            
            ttk.Label(config_frame, text="🚩 Flags:").grid(row=1, column=0, sticky="w", padx=5, pady=2)
            ttk.Entry(config_frame, textvariable=self.flags_var, style="Config.TEntry").grid(row=1, column=1, sticky="ew", padx=5, pady=2)
            
            ttk.Label(config_frame, text="⏱️ Timeout:").grid(row=2, column=0, sticky="w", padx=5, pady=2)
            ttk.Entry(config_frame, textvariable=self.timeout_var, style="Config.TEntry").grid(row=2, column=1, sticky="ew", padx=5, pady=2)
            
            # Opción para limpiar archivos temporales
            ttk.Checkbutton(
                config_frame, 
                text="🧹 Limpiar archivos temporales", 
                variable=self.autoclean_var,
                style="TCheckbutton"
            ).grid(row=3, column=0, columnspan=2, sticky="w", padx=5, pady=5)
        
        config_frame.columnconfigure(1, weight=1)
        
        # Área de archivos
        if USING_TTKBOOTSTRAP:
            files_frame = ttk.Labelframe(left_panel, text="Archivos", padding=10, bootstyle="primary")
        else:
            files_frame = ttk.LabelFrame(left_panel, text="📄 Archivos", padding=10)
        files_frame.pack(fill="both", expand=True)
        
        # Área de arrastrar y soltar
        drop_text = "Arrastre archivos .cpp aquí" if USING_DRAG_DROP else "Use el botón 'Añadir Archivos'"
        
        if USING_TTKBOOTSTRAP:
            self.drop_target = tk.Text(files_frame,
                                    height=5,
                                    font=('Roboto', 10),
                                    bg='#f8f9fa',
                                    fg='#495057')
        else:
            self.drop_target = tk.Text(files_frame,
                                    height=5,
                                    font=('Helvetica', 10),
                                    bg='#f8f9fa',
                                    fg='#495057',
                                    relief="flat")
        self.drop_target.insert("1.0", drop_text)
        self.drop_target.configure(state="disabled")
        self.drop_target.pack(fill="both", expand=True, pady=(0, 10))
        
        if USING_DRAG_DROP:
            self.drop_target.drop_target_register('DND_Files')
            self.drop_target.dnd_bind('<<Drop>>', self.on_drop)
        
        # Lista de archivos
        if USING_TTKBOOTSTRAP:
            self.files_list = ttk.Treeview(files_frame, 
                                        columns=("path",),
                                        show="headings",
                                        height=8,
                                        bootstyle="primary")
            self.files_list.heading("path", text="Ruta del archivo")
            self.files_list.column("path", width=300)
        else:
            self.files_list = tk.Listbox(files_frame,
                                    height=10,
                                    font=('Helvetica', 10),
                                    bg='#f8f9fa',
                                    fg='#495057',
                                    selectmode=tk.MULTIPLE,
                                    relief="flat")
        self.files_list.pack(fill="both", expand=True)
        
        # Botones de archivos
        buttons_frame = ttk.Frame(files_frame)
        buttons_frame.pack(fill="x", pady=(10, 0))
        
        if USING_TTKBOOTSTRAP:
            ttk.Button(buttons_frame,
                    text="Añadir Archivos",
                    bootstyle="outline-primary",
                    command=self.add_files).pack(side="left", padx=2)
            
            ttk.Button(buttons_frame,
                    text="Eliminar",
                    bootstyle="outline-danger",
                    command=self.remove_selected).pack(side="left", padx=2)
            
            ttk.Button(buttons_frame,
                    text="Limpiar Todo",
                    bootstyle="outline-warning",
                    command=self.clear_files).pack(side="left", padx=2)
        else:
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
        if USING_TTKBOOTSTRAP:
            compile_only_button = ttk.Button(compile_buttons_frame,
                                        text="Solo Compilar",
                                        bootstyle="success-outline",
                                        command=self.compile_files_only)
        else:
            compile_only_button = ttk.Button(compile_buttons_frame,
                                    text="🔨 Solo Compilar",
                                    command=self.compile_files_only,
                                    style="Compile.TButton")
        compile_only_button.pack(fill="x", pady=(0, 5))
        
        # Botón de compilación con PDF
        if USING_TTKBOOTSTRAP:
            compile_pdf_button = ttk.Button(compile_buttons_frame,
                                        text="Compilar y Generar PDF",
                                        bootstyle="success",
                                        command=self.compile_files)
        else:
            compile_pdf_button = ttk.Button(compile_buttons_frame,
                                    text="🚀 Compilar y Generar PDF",
                                    command=self.compile_files,
                                    style="Compile.TButton")
        compile_pdf_button.pack(fill="x")
        
        # Panel derecho (log)
        if USING_TTKBOOTSTRAP:
            right_panel = ttk.Frame(self.single_tab, bootstyle="light")
        else:
            right_panel = ttk.Frame(self.single_tab, style="Card.TFrame")
        right_panel.pack(side="right", fill="both", expand=True)
        
        # Área de log
        if USING_TTKBOOTSTRAP:
            log_frame = ttk.Labelframe(right_panel, text="Registro de Operaciones", padding=10, bootstyle="primary")
        else:
            log_frame = ttk.LabelFrame(right_panel, text="📊 Registro de Operaciones", padding=10)
        log_frame.pack(fill="both", expand=True)
        
        if USING_TTKBOOTSTRAP:
            try:
                self.log_text = ScrolledText(
                    log_frame,
                    font=(GUI_CONFIG['code_font_family'], 9),
                    autohide=True,
                    bootstyle="dark"
                )
            except:
                # Fallback si hay error con la importación
                self.log_text = scrolledtext.ScrolledText(
                    log_frame,
                    wrap=tk.WORD,
                    font=(GUI_CONFIG['code_font_family'], 10),
                    bg=GUI_CONFIG['theme']['card_bg'],
                    fg=GUI_CONFIG['theme']['text']
                )
        self.log_text.pack(fill="both", expand=True)
        
        # Barra de progreso
        self.progress_var = tk.DoubleVar()
        if USING_TTKBOOTSTRAP:
            self.progress_bar = ttk.Progressbar(
                log_frame,
                variable=self.progress_var,
                maximum=100,
                bootstyle="success-striped"
            )
        else:
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
        if USING_TTKBOOTSTRAP:
            left_panel = ttk.Frame(self.batch_tab, bootstyle="light")
        else:
            left_panel = ttk.Frame(self.batch_tab, style="Card.TFrame")
        left_panel.pack(side="left", fill="both", expand=True, padx=(0, 10))
        
        # Configuración de búsqueda
        if USING_TTKBOOTSTRAP:
            search_frame = ttk.Labelframe(left_panel, text="Búsqueda de Archivos", padding=10, bootstyle="primary")
        else:
            search_frame = ttk.LabelFrame(left_panel, text="🔍 Búsqueda de Archivos", padding=10)
        search_frame.pack(fill="x", pady=(0, 10))
        
        # Variables de configuración
        self.folder_var = tk.StringVar()
        self.pattern_var = tk.StringVar(value="*.cpp")
        self.recursive_var = tk.BooleanVar(value=True)
        self.batch_autoclean_var = tk.BooleanVar(value=True)  # Variable para limpieza automática
        
        # Grid de configuración
        if USING_TTKBOOTSTRAP:
            ttk.Label(search_frame, text="Carpeta:", bootstyle="primary").grid(row=0, column=0, sticky="w", padx=5, pady=2)
        else:
            ttk.Label(search_frame, text="📁 Carpeta:").grid(row=0, column=0, sticky="w", padx=5, pady=2)
        
        folder_frame = ttk.Frame(search_frame)
        folder_frame.grid(row=0, column=1, sticky="ew", padx=5, pady=2)
        
        if USING_TTKBOOTSTRAP:
            ttk.Entry(folder_frame, textvariable=self.folder_var, bootstyle="primary").pack(side="left", fill="x", expand=True)
            ttk.Button(folder_frame, text="Explorar", bootstyle="outline-primary", command=self.select_folder).pack(side="right", padx=(5, 0))
        else:
            ttk.Entry(folder_frame, textvariable=self.folder_var, style="Config.TEntry").pack(side="left", fill="x", expand=True)
            ttk.Button(folder_frame, text="📂", command=self.select_folder, width=3).pack(side="right", padx=(5, 0))
        
        if USING_TTKBOOTSTRAP:
            ttk.Label(search_frame, text="Patrón:", bootstyle="primary").grid(row=1, column=0, sticky="w", padx=5, pady=2)
            ttk.Entry(search_frame, textvariable=self.pattern_var, bootstyle="primary").grid(row=1, column=1, sticky="ew", padx=5, pady=2)
            
            ttk.Checkbutton(
                search_frame, 
                text="Búsqueda recursiva", 
                variable=self.recursive_var,
                bootstyle="primary-round-toggle"
            ).grid(row=2, column=0, columnspan=2, sticky="w", padx=5, pady=2)
            
            # Opción para limpiar archivos temporales
            ttk.Checkbutton(
                search_frame, 
                text="Limpiar archivos temporales", 
                variable=self.batch_autoclean_var,
                bootstyle="primary-round-toggle"
            ).grid(row=3, column=0, columnspan=2, sticky="w", padx=5, pady=5)
            
            # Botón de búsqueda
            ttk.Button(search_frame, 
                     text="Buscar Archivos", 
                     bootstyle="primary",
                     command=self.search_files).grid(row=4, column=0, columnspan=2, sticky="ew", padx=5, pady=5)
        else:
            ttk.Label(search_frame, text="🔎 Patrón:").grid(row=1, column=0, sticky="w", padx=5, pady=2)
            ttk.Entry(search_frame, textvariable=self.pattern_var, style="Config.TEntry").grid(row=1, column=1, sticky="ew", padx=5, pady=2)
            
            ttk.Checkbutton(
                search_frame, 
                text="🔄 Búsqueda recursiva", 
                variable=self.recursive_var
            ).grid(row=2, column=0, columnspan=2, sticky="w", padx=5, pady=2)
            
            # Opción para limpiar archivos temporales
            ttk.Checkbutton(
                search_frame, 
                text="🧹 Limpiar archivos temporales", 
                variable=self.batch_autoclean_var
            ).grid(row=3, column=0, columnspan=2, sticky="w", padx=5, pady=5)
            
            # Botón de búsqueda
            ttk.Button(search_frame, 
                     text="🔍 Buscar Archivos", 
                     command=self.search_files).grid(row=4, column=0, columnspan=2, sticky="ew", padx=5, pady=5)
        
        search_frame.columnconfigure(1, weight=1)
        
        # Área de archivos encontrados
        if USING_TTKBOOTSTRAP:
            files_frame = ttk.Labelframe(left_panel, text="Archivos Encontrados", padding=10, bootstyle="primary")
        else:
            files_frame = ttk.LabelFrame(left_panel, text="📄 Archivos Encontrados", padding=10)
        files_frame.pack(fill="both", expand=True)
        
        # Lista de archivos
        if USING_TTKBOOTSTRAP:
            self.batch_files_list = ttk.Treeview(files_frame, 
                                            columns=("path",),
                                            show="headings",
                                            height=10,
                                            bootstyle="primary",
                                            selectmode="extended")
            self.batch_files_list.heading("path", text="Ruta del archivo")
            self.batch_files_list.column("path", width=300)
        else:
            self.batch_files_list = tk.Listbox(files_frame,
                                         height=10,
                                         font=('Helvetica', 10),
                                         bg='#f8f9fa',
                                         fg='#495057',
                                         selectmode=tk.MULTIPLE,
                                         relief="flat")
        self.batch_files_list.pack(fill="both", expand=True)
        
        # Frame de información
        info_frame = ttk.Frame(files_frame)
        info_frame.pack(fill="x", pady=5)
        
        # Etiqueta para mostrar el número de archivos
        self.files_count_var = tk.StringVar(value="0 archivos encontrados")
        if USING_TTKBOOTSTRAP:
            ttk.Label(info_frame, textvariable=self.files_count_var, bootstyle="secondary").pack(side="left")
        else:
            ttk.Label(info_frame, textvariable=self.files_count_var).pack(side="left")
        
        # Botones de selección
        if USING_TTKBOOTSTRAP:
            ttk.Button(info_frame,
                     text="Seleccionar Todos",
                     bootstyle="outline-success",
                     command=self.select_all_files).pack(side="right", padx=2)
            
            ttk.Button(info_frame,
                     text="Deseleccionar Todos",
                     bootstyle="outline-danger",
                     command=self.deselect_all_files).pack(side="right", padx=2)
        else:
            ttk.Button(info_frame,
                     text="✅ Seleccionar Todos",
                     command=self.select_all_files).pack(side="right", padx=2)
            
            ttk.Button(info_frame,
                     text="❌ Deseleccionar Todos",
                     command=self.deselect_all_files).pack(side="right", padx=2)
        
        # Botón de compilación por lotes
        if USING_TTKBOOTSTRAP:
            compile_button = ttk.Button(left_panel,
                                       text="Compilar Lote",
                                       bootstyle="success",
                                       command=self.compile_batch)
        else:
            compile_button = ttk.Button(left_panel,
                                       text="🚀 Compilar Lote",
                                       command=self.compile_batch,
                                       style="Compile.TButton")
        compile_button.pack(fill="x", pady=10)
        
        # Panel derecho (log)
        if USING_TTKBOOTSTRAP:
            right_panel = ttk.Frame(self.batch_tab, bootstyle="light")
        else:
            right_panel = ttk.Frame(self.batch_tab, style="Card.TFrame")
        right_panel.pack(side="right", fill="both", expand=True)
        
        # Área de log
        if USING_TTKBOOTSTRAP:
            log_frame = ttk.Labelframe(right_panel, text="Registro de Operaciones por Lotes", padding=10, bootstyle="primary")
        else:
            log_frame = ttk.LabelFrame(right_panel, text="📊 Registro de Operaciones por Lotes", padding=10)
        log_frame.pack(fill="both", expand=True)
        
        if USING_TTKBOOTSTRAP:
            try:
                self.batch_log_text = ScrolledText(
                    log_frame,
                    font=(GUI_CONFIG['code_font_family'], 9),
                    autohide=True,
                    bootstyle="dark"
                )
            except:
                # Fallback si hay error con la importación
                self.batch_log_text = scrolledtext.ScrolledText(
                    log_frame,
                    wrap=tk.WORD,
                    font=(GUI_CONFIG['code_font_family'], 10),
                    bg=GUI_CONFIG['theme']['card_bg'],
                    fg=GUI_CONFIG['theme']['text']
                )
        else:
            self.batch_log_text = scrolledtext.ScrolledText(
                log_frame,
                wrap=tk.WORD,
                font=(GUI_CONFIG['code_font_family'], 10),
                bg=GUI_CONFIG['theme']['card_bg'],
                fg=GUI_CONFIG['theme']['text']
            )
        self.batch_log_text.pack(fill="both", expand=True)
        
        # Barra de progreso
        self.batch_progress_var = tk.DoubleVar()
        if USING_TTKBOOTSTRAP:
            self.batch_progress_bar = ttk.Progressbar(
                log_frame,
                variable=self.batch_progress_var,
                maximum=100,
                bootstyle="success-striped"
            )
        else:
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
        
        if self.recursive_var.get():
            if not pattern.startswith("**/"):
                pattern = os.path.join("**", pattern)
            files = glob.glob(os.path.join(folder, pattern), recursive=True)
        else:
            files = glob.glob(os.path.join(folder, pattern), recursive=False)
        
        # Actualizar la lista
        if USING_TTKBOOTSTRAP:
            for item in self.batch_files_list.get_children():
                self.batch_files_list.delete(item)
        else:
            self.batch_files_list.delete(0, tk.END)
        
        self.batch_selected_files = []
        
        for file in files:
            if os.path.isfile(file):
                if USING_TTKBOOTSTRAP:
                    self.batch_files_list.insert("", "end", values=(file,))
                else:
                    self.batch_files_list.insert(tk.END, file)
                self.batch_selected_files.append(file)
        
        # Actualizar el contador de archivos
        count = len(self.batch_selected_files)
        self.files_count_var.set(f"{count} archivo{'s' if count != 1 else ''} encontrado{'s' if count != 1 else ''}")
        
        self.batch_log(f"Se encontraron {count} archivos.")
    
    def select_all_files(self):
        """Selecciona todos los archivos en la lista de compilación por lotes."""
        if USING_TTKBOOTSTRAP:
            for item in self.batch_files_list.get_children():
                self.batch_files_list.selection_add(item)
        else:
            self.batch_files_list.select_set(0, tk.END)
    
    def deselect_all_files(self):
        """Deselecciona todos los archivos en la lista de compilación por lotes."""
        if USING_TTKBOOTSTRAP:
            for item in self.batch_files_list.get_children():
                self.batch_files_list.selection_remove(item)
        else:
            self.batch_files_list.selection_clear(0, tk.END)
    
    def batch_log(self, message, level="info"):
        """Añade un mensaje al área de log de compilación por lotes con formato.
        
        Args:
            message: El mensaje a mostrar
            level: El nivel del mensaje ("info", "success", "warning", "error")
        """
        timestamp = datetime.now().strftime("[%H:%M:%S]")
        
        if USING_TTKBOOTSTRAP:
            # Definir colores y prefijos según el nivel
            if level == "success":
                prefix = "✅ "
                tag = "success"
            elif level == "warning":
                prefix = "⚠️ "
                tag = "warning"
            elif level == "error":
                prefix = "❌ "
                tag = "error"
            else:  # info
                prefix = "ℹ️ "
                tag = "info"
                
            # Insertar texto con color
            self.batch_log_text.insert(tk.END, f"{timestamp} ", "timestamp")
            self.batch_log_text.insert(tk.END, f"{prefix}{message}\n", tag)
            
            # Configurar tags si no están definidos
            if not hasattr(self, "batch_log_tags_configured"):
                self.batch_log_text.tag_configure("timestamp", foreground="#6c757d")
                self.batch_log_text.tag_configure("info", foreground="#0275d8")
                self.batch_log_text.tag_configure("success", foreground="#5cb85c")
                self.batch_log_text.tag_configure("warning", foreground="#f0ad4e")
                self.batch_log_text.tag_configure("error", foreground="#d9534f")
                self.batch_log_tags_configured = True
        else:
            # Versión simple para ttk estándar
            self.batch_log_text.insert(tk.END, f"{timestamp} {message}\n")
        
        self.batch_log_text.see(tk.END)
    
    def compile_batch(self):
        """Compila todos los archivos seleccionados en modo lote."""
        files = self.get_selected_batch_files()
        if not files:
            messagebox.showwarning("Advertencia", "No hay archivos seleccionados para compilar.")
            return
        
        # Configurar la interfaz durante la compilación
        self.disable_interface()
        self.batch_progress_var.set(0)
        
        # Iniciar el hilo de compilación
        threading.Thread(target=self.process_batch_files, args=(files,), daemon=True).start()
    
    def process_batch_files(self, files):
        """Procesa los archivos seleccionados en un hilo separado."""
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
                    self.batch_log(f"Archivo compilado correctamente: {os.path.basename(file)}", "success")
                    success_count += 1
                else:
                    self.batch_log(f"Error al compilar: {os.path.basename(file)}", "error")
                    if "stderr" in compile_result:
                        error_text = compile_result["stderr"]
                        # Limitar la cantidad de texto de error para evitar sobrecarga
                        if len(error_text) > 500:
                            error_text = error_text[:500] + "... (mensaje truncado)"
                        self.batch_log(f"Error: {error_text}", "error")
                    error_count += 1
            
            # Compilación completada
            self.batch_progress_var.set(100)
            self.batch_log(f"Compilación por lotes finalizada. Éxitos: {success_count}, Errores: {error_count}", 
                        "success" if error_count == 0 else "warning")
            
            # Limpiar archivos temporales si está habilitada
            if self.batch_autoclean_var.get():
                self.batch_log("Limpiando archivos temporales antiguos...", "info")
                self.compiler.cleanup(keep_current=True)
            
            # Mostrar mensaje final según el resultado
            if error_count == 0:
                messagebox.showinfo("Éxito", f"La compilación por lotes ha finalizado correctamente.\nSe compilaron {success_count} archivos sin errores.")
            else:
                messagebox.showwarning("Compilación completada con errores", 
                                    f"La compilación finalizó con {error_count} errores.\n"
                                    f"Se compilaron correctamente {success_count} de {total_files} archivos.")
            
        except Exception as e:
            self.batch_log(f"Error durante la compilación por lotes: {str(e)}", "error")
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
                    if USING_TTKBOOTSTRAP:
                        item_id = self.files_list.insert("", "end", values=(file,))
                    else:
                        self.files_list.insert(tk.END, os.path.basename(file))
                    self.log(f"Archivo añadido: {os.path.basename(file)}")
    
    def remove_selected(self):
        """Elimina los archivos seleccionados."""
        if USING_TTKBOOTSTRAP:
            selected = self.files_list.selection()
            for item_id in selected:
                file_path = self.files_list.item(item_id)['values'][0]
                self.selected_files.remove(file_path)
                self.files_list.delete(item_id)
        else:
            selected = self.files_list.curselection()
            for index in reversed(selected):
                self.files_list.delete(index)
                self.selected_files.pop(index)
    
    def clear_files(self):
        """Limpia la lista de archivos."""
        if USING_TTKBOOTSTRAP:
            for item in self.files_list.get_children():
                self.files_list.delete(item)
        else:
            self.files_list.delete(0, tk.END)
        self.selected_files.clear()
        self.log("Lista de archivos limpiada")
    
    def log(self, message, level="info"):
        """Añade un mensaje al área de log con formato y colores según el nivel.
        
        Args:
            message: El mensaje a mostrar
            level: El nivel del mensaje ("info", "success", "warning", "error")
        """
        timestamp = datetime.now().strftime("[%H:%M:%S]")
        
        if USING_TTKBOOTSTRAP:
            # Definir colores y prefijos según el nivel
            if level == "success":
                prefix = "✅ "
                tag = "success"
            elif level == "warning":
                prefix = "⚠️ "
                tag = "warning"
            elif level == "error":
                prefix = "❌ "
                tag = "error"
            else:  # info
                prefix = "ℹ️ "
                tag = "info"
                
            # Insertar texto con color
            self.log_text.insert(tk.END, f"{timestamp} ", "timestamp")
            self.log_text.insert(tk.END, f"{prefix}{message}\n", tag)
            
            # Configurar tags si no están definidos
            if not hasattr(self, "log_tags_configured"):
                self.log_text.tag_configure("timestamp", foreground="#6c757d")
                self.log_text.tag_configure("info", foreground="#0275d8")
                self.log_text.tag_configure("success", foreground="#5cb85c")
                self.log_text.tag_configure("warning", foreground="#f0ad4e")
                self.log_text.tag_configure("error", foreground="#d9534f")
                self.log_tags_configured = True
        else:
            # Versión simple para ttk estándar
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
                    self.log(f"Archivo procesado correctamente: {os.path.basename(file)}", "success")
                else:
                    self.log(f"Error al procesar: {os.path.basename(file)}", "error")
                    if "error" in result:
                        self.log(f"Error: {result['error']}", "error")
            
            # Compilación completada
            self.progress_var.set(100)
            self.log("Generando PDF...", "info")
            
            pdf_result = self.compiler.save_pdf()
            if pdf_result:
                self.log("PDF generado correctamente", "success")
            else:
                # Verificar si el PDF existe aunque el método haya reportado error
                pdf_path = os.path.join(OUTPUT_DIR, "programas_cpp.pdf")
                if os.path.exists(pdf_path) and os.path.getsize(pdf_path) > 0:
                    self.log(f"PDF generado en {pdf_path} a pesar del error reportado", "success")
                else:
                    self.log("Error al generar el PDF", "error")
            
            # Limpiar archivos temporales si está activada la opción
            if self.autoclean_var.get():
                self.log("Limpiando archivos temporales antiguos...", "info")
                try:
                    self.compiler.cleanup(keep_current=True)
                    self.log("Limpieza completada", "success")
                except Exception as cleanup_error:
                    self.log(f"Error durante la limpieza: {str(cleanup_error)}", "error")
            
            # Actualizar estado
            self.status_var.set("Listo")
            self.processing = False
            self.restore_interface()
            
        except Exception as e:
            error_msg = str(e)
            if not self.gui_closed:  # Evitar errores si la GUI ya ha sido cerrada
                self.log(f"Error durante la compilación: {error_msg}", "error")
                messagebox.showerror("Error", f"Ha ocurrido un error durante la compilación:\n{error_msg}")
                self.status_var.set("Error")
                self.processing = False
                self.restore_interface()  # Usar restore_interface en lugar de enable_controls
    
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
                    self.log(f"Archivo compilado correctamente: {os.path.basename(file)}", "success")
                    success_count += 1
                else:
                    self.log(f"Error al compilar: {os.path.basename(file)}", "error")
                    if "stderr" in compile_result:
                        error_text = compile_result["stderr"]
                        # Limitar la cantidad de texto de error para evitar sobrecarga
                        if len(error_text) > 500:
                            error_text = error_text[:500] + "... (mensaje truncado)"
                        self.log(f"Error: {error_text}", "error")
                    error_count += 1
            
            # Compilación completada
            self.progress_var.set(100)
            
            # Mostrar mensaje de finalización
            self.log(f"Compilación finalizada. Éxitos: {success_count}, Errores: {error_count}", 
                    "success" if error_count == 0 else "warning")
            
            # Mostrar mensaje final según el resultado
            if error_count == 0:
                messagebox.showinfo("Éxito", f"La compilación ha finalizado correctamente.\nSe compilaron {success_count} archivos sin errores.")
            else:
                messagebox.showwarning("Compilación completada con errores", 
                                    f"La compilación finalizó con {error_count} errores.\n"
                                    f"Se compilaron correctamente {success_count} de {total_files} archivos.")
            
        except Exception as e:
            self.log(f"Error durante la compilación: {str(e)}", "error")
            traceback.print_exc()
            
        finally:
            # Restaurar la interfaz
            self.restore_interface()
            self.status_var.set("Listo")
    
    def clean_temp_files(self):
        """Limpia todos los archivos temporales."""
        if USING_TTKBOOTSTRAP:
            if messagebox.askyesno("Confirmar", "¿Desea eliminar todos los archivos temporales?\n\nEsto incluye capturas de pantalla y archivos compilados.", icon="question"):
                try:
                    self.log("Limpiando todos los archivos temporales...")
                    self.compiler.cleanup(keep_current=False)
                    messagebox.showinfo("Limpieza Completada", "Se han eliminado todos los archivos temporales.")
                except Exception as e:
                    self.log(f"Error durante la limpieza: {str(e)}")
                    messagebox.showerror("Error", f"No se pudieron eliminar todos los archivos temporales: {str(e)}")
        else:
            if messagebox.askyesno("Confirmar", "¿Desea eliminar todos los archivos temporales?\nEsto incluye capturas de pantalla y archivos compilados."):
                try:
                    self.log("Limpiando todos los archivos temporales...")
                    self.compiler.cleanup(keep_current=False)
                    messagebox.showinfo("Limpieza Completada", "Se han eliminado todos los archivos temporales.")
                except Exception as e:
                    self.log(f"Error durante la limpieza: {str(e)}")
                    messagebox.showerror("Error", f"No se pudieron eliminar todos los archivos temporales: {str(e)}")
    
    def get_selected_batch_files(self):
        """Obtiene la lista de archivos seleccionados para compilación por lotes."""
        files = []
        if USING_TTKBOOTSTRAP:
            selected_items = self.batch_files_list.selection()
            if selected_items:
                for item_id in selected_items:
                    file_path = self.batch_files_list.item(item_id)['values'][0]
                    files.append(file_path)
            else:
                # Si no hay selección, usar todos los archivos encontrados
                files = self.batch_selected_files
        else:
            selected = self.batch_files_list.curselection()
            if selected:
                for index in selected:
                    files.append(self.batch_selected_files[index])
            else:
                # Si no hay selección, usar todos los archivos encontrados
                files = self.batch_selected_files
                
        return files
    
    def run(self):
        """Ejecuta la interfaz gráfica."""
        self.root.mainloop()

def main():
    """Función principal."""
    gui = CompilerGUI()
    gui.run()

if __name__ == "__main__":
    main()

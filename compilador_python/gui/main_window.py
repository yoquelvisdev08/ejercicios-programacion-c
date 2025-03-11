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
        
        # Panel izquierdo
        left_panel = ttk.Frame(main_frame, style="Card.TFrame")
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
        
        # Botón de compilación
        compile_button = ttk.Button(left_panel,
                                  text="🚀 Compilar y Generar PDF",
                                  command=self.compile_files,
                                  style="Compile.TButton")
        compile_button.pack(fill="x", pady=10)
        
        # Panel derecho (log)
        right_panel = ttk.Frame(main_frame, style="Card.TFrame")
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
        
        # Barra de estado
        self.status_var = tk.StringVar(value="Listo")
        status_bar = ttk.Label(
            self.root,
            textvariable=self.status_var,
            relief=tk.SUNKEN,
            padding=5
        )
        status_bar.pack(fill=tk.X, side=tk.BOTTOM)
    
    def setup_compiler(self):
        """Configura el compilador."""
        self.compiler = CppCompiler(gui=self)
        self.selected_files = []
    
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
        timestamp = datetime.now().strftime("%H:%M:%S")
        self.log_text.insert(tk.END, f"[{timestamp}] {message}\n")
        self.log_text.see(tk.END)
        self.root.update_idletasks()
    
    def compile_files(self):
        """Compila los archivos seleccionados."""
        if not self.selected_files:
            messagebox.showwarning(
                "Sin archivos",
                "No hay archivos para procesar."
            )
            return
        
        # Deshabilitar interfaz durante el procesamiento
        self.root.config(cursor="wait")
        self.status_var.set("Procesando archivos...")
        
        # Procesar archivos en un hilo separado
        threading.Thread(target=self.process_files, daemon=True).start()
    
    def process_files(self):
        """Procesa los archivos en un hilo separado."""
        try:
            total_files = len(self.selected_files)
            processed = 0
            
            # Asegurarse de que el directorio temporal está limpio
            self.compiler.cleanup()
            
            for file in self.selected_files:
                # Actualizar progreso
                progress = (processed / total_files) * 100
                self.root.after(0, lambda: self.progress_var.set(progress))
                self.root.after(0, lambda: self.status_var.set(f"Procesando {os.path.basename(file)}..."))
                
                self.log(f"\nProcesando: {os.path.basename(file)}")
                result = self.compiler.process_file(file)
                
                if result["success"]:
                    self.log(f"✓ {os.path.basename(file)} procesado correctamente")
                else:
                    self.log(f"✗ Error al procesar {os.path.basename(file)}")
                    if "error" in result:
                        self.log(f"  Error: {result['error']}")
                
                processed += 1
            
            # Guardar PDF
            if self.compiler.save_pdf():
                self.log("\n✓ PDF generado correctamente")
            else:
                self.log("\n✗ Error al generar el PDF")
            
            # Limpiar archivos temporales
            self.compiler.cleanup()
            
            # Actualizar progreso final
            self.root.after(0, lambda: self.progress_var.set(100))
            self.root.after(0, lambda: self.status_var.set("Procesamiento completado"))
            
            # Mostrar mensaje de éxito
            self.root.after(0, lambda: messagebox.showinfo(
                "Proceso Completado",
                f"Se han procesado {total_files} archivos.\nEl PDF ha sido generado correctamente."
            ))
            
        except Exception as e:
            self.log(f"\n✗ Error: {str(e)}")
            traceback.print_exc()
            self.root.after(0, lambda: messagebox.showerror(
                "Error",
                f"Error durante el procesamiento: {str(e)}"
            ))
        finally:
            # Restaurar interfaz
            self.root.after(0, self.restore_interface)
    
    def restore_interface(self):
        """Restaura la interfaz después del procesamiento."""
        self.root.config(cursor="")
        self.status_var.set("Listo")
    
    def run(self):
        """Inicia la aplicación."""
        self.root.mainloop()

def main():
    """Función principal."""
    app = CompilerGUI()
    app.run()

if __name__ == '__main__':
    main()

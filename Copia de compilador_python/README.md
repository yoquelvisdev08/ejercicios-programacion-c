# Compilador C++ Avanzado

Un compilador C++ avanzado con interfaz gráfica que permite compilar, ejecutar y documentar programas C++.

## Características

- 🖥️ Interfaz gráfica moderna y fácil de usar
- 📄 Soporte para arrastrar y soltar archivos
- 📚 Compilación por lotes de múltiples archivos C++
- 📁 Búsqueda recursiva de archivos en directorios
- 📸 Capturas de pantalla automáticas de la ejecución
- 📝 Generación de documentación en PDF
- 🎨 Estilos personalizados según el tipo de ejercicio
- 🔍 Análisis inteligente del código
- 🚀 Soporte para entrada/salida interactiva

## Requisitos

- Python 3.7 o superior
- g++ (compilador C++)
- Bibliotecas de sistema:
  - Tk (para la interfaz gráfica)
  - SSL (para descargar recursos)

### En macOS

```bash
# Instalar Xcode Command Line Tools (incluye g++)
xcode-select --install

# Instalar Python 3 (si no está instalado)
brew install python3
```

### En Linux (Ubuntu/Debian)

```bash
# Instalar g++ y dependencias
sudo apt-get update
sudo apt-get install g++ python3 python3-venv python3-tk
```

## Instalación

1. Clonar el repositorio:
```bash
git clone <url-del-repositorio>
cd compilador_python
```

2. Ejecutar el script de instalación:
```bash
chmod +x run_compiler.sh
./run_compiler.sh
```

El script creará automáticamente un entorno virtual e instalará todas las dependencias necesarias.

## Uso

### Modo Gráfico

1. Ejecutar el programa:
```bash
./run_compiler.sh
```

2. En la interfaz gráfica:
   - **Compilación Individual**:
     - Arrastrar archivos .cpp a la ventana o hacer clic para seleccionarlos
     - Hacer clic en "Compilar y Generar PDF"
     - Los resultados se mostrarán en pantalla y se guardarán en un PDF
   
   - **Compilación por Lotes**:
     - Seleccionar una carpeta que contenga archivos C++
     - Establecer el patrón de búsqueda (por defecto "*.cpp")
     - Hacer clic en "Buscar Archivos" para encontrar todos los archivos coincidentes
     - Seleccionar los archivos que se desean compilar
     - Hacer clic en "Compilar Lote y Generar PDF"

### Modo Consola

```bash
# Procesar archivos específicos
./run_compiler.sh archivo1.cpp archivo2.cpp

# Modo consola explícito
./run_compiler.sh --no-gui archivo.cpp
```

### Opciones

- `--keep-venv`: Mantener el entorno virtual existente
- `--no-gui`: Ejecutar en modo consola
- Los archivos .cpp se pueden especificar como argumentos

## Estructura del Proyecto

```
compilador_python/
├── config/
│   ├── __init__.py
│   └── settings.py        # Configuraciones globales
├── core/
│   ├── __init__.py
│   ├── compiler.py        # Lógica de compilación
│   └── executor.py        # Lógica de ejecución
├── gui/
│   ├── __init__.py
│   ├── main_window.py     # Ventana principal
│   └── output_window.py   # Ventana de salida/captura
├── utils/
│   ├── __init__.py
│   ├── file_handler.py    # Manejo de archivos
│   ├── pdf_generator.py   # Generación de PDF
│   └── screenshot.py      # Captura de pantalla
├── tests/
│   ├── __init__.py
│   └── test_compiler.py   # Tests unitarios
├── run_compiler.sh        # Script de ejecución
├── requirements.txt       # Dependencias
└── main.py               # Punto de entrada
```

## Configuración

Las configuraciones se pueden ajustar en `config/settings.py`:

- Rutas de directorios
- Opciones del compilador
- Estilos de la interfaz
- Configuración de capturas
- Formato del PDF

## Modos de Compilación

### Compilación Individual

El modo de compilación individual permite:
- Seleccionar archivos específicos para compilar
- Ver detalles del proceso de compilación para cada archivo
- Generar documentación detallada de cada archivo

### Compilación por Lotes

El modo de compilación por lotes permite:
- Seleccionar una carpeta que contiene múltiples archivos C++
- Buscar archivos en subdirectorios con patrones personalizados
- Compilar múltiples archivos en una sola operación
- Generar un informe consolidado en PDF

## Solución de Problemas

### La interfaz gráfica no se inicia

Verificar que Tk está instalado:
```bash
python3 -c "import tkinter"
```

### Error de compilación

Verificar que g++ está instalado:
```bash
g++ --version
```

### Capturas de pantalla no funcionan

1. Verificar permisos de acceso a la pantalla
2. Asegurar que hay suficiente espacio en disco
3. Verificar que el directorio temporal es escribible

### Problemas con el modo de lotes

1. Asegurarse de que la carpeta existe y tiene permisos de lectura
2. Verificar que el patrón de búsqueda está correctamente formateado
3. Para búsquedas recursivas, añadir "**/*.cpp" como patrón

## Contribuir

1. Fork del repositorio
2. Crear una rama para tu característica
3. Commit de tus cambios
4. Push a la rama
5. Crear un Pull Request

## Licencia

Este proyecto está licenciado bajo la Licencia MIT - ver el archivo LICENSE para más detalles.

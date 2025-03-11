# Compilador C++ Avanzado con Entorno Virtual

Esta herramienta proporciona una interfaz gráfica avanzada para compilar, probar y documentar programas en C++. Incluye análisis automático de código, pruebas inteligentes y generación de informes completos, todo ejecutándose en un entorno virtual aislado.

## Características Principales

- **Interfaz gráfica** con soporte para seleccionar archivos fácilmente
- **Análisis inteligente de código** para generar datos de prueba adecuados
- **Compilación en carpetas individuales** para cada programa
- **Ejecución y prueba automática** con capturas de pantalla
- **Documentación completa** en formato Markdown para cada programa
- **Ejecución en entorno virtual** para manejar dependencias de forma aislada
- **Funcionalidad de arrastrar y soltar** (opcional, si tkinterdnd2 está instalado)

## Requisitos previos

- Python 3.6 o superior
- Un compilador C++ (por defecto g++)

## Instalación y uso

### Método fácil (scripts ejecutables)

Simplemente ejecute el script correspondiente a su sistema operativo:

- **Windows**: Haga doble clic en `run_compiler.bat`
- **macOS/Linux**: Ejecute `./run_compiler.sh` (asegúrese de que tiene permisos de ejecución con `chmod +x run_compiler.sh`)

Estos scripts configurarán automáticamente el entorno virtual e instalarán todas las dependencias necesarias.

### Instalación manual

Si prefiere una instalación manual:

1. **Cree un entorno virtual**:
   ```bash
   python -m venv .venv
   ```

2. **Active el entorno virtual**:
   - Windows:
     ```
     .venv\Scripts\activate
     ```
   - macOS/Linux:
     ```
     source .venv/bin/activate
     ```

3. **Instale las dependencias**:
   ```bash
   pip install Pillow
   
   # Opcional: para la funcionalidad de arrastrar y soltar
   pip install tkinterdnd2
   ```

4. **Ejecute el compilador**:
   ```bash
   python compile_cpp_advanced.py
   ```

### Uso del programa

Una vez iniciado, puede:

1. Usar el botón "Añadir archivos" para seleccionar archivos .cpp
2. Arrastrar archivos `.cpp` directamente a la zona designada (si tkinterdnd2 está instalado)
3. Configurar compilador, flags y directorio de salida
4. Hacer clic en "Compilar y probar" para iniciar el proceso

## Sobre la funcionalidad de arrastrar y soltar

El programa intenta usar la biblioteca tkinterdnd2 para proporcionar la funcionalidad de arrastrar y soltar archivos. Si esta biblioteca no está disponible:

- La funcionalidad de arrastrar y soltar estará desactivada
- Aparecerá un mensaje indicando cómo habilitar esta característica
- Podrá seguir usando el programa normalmente a través del botón "Añadir Archivos"

Los scripts de inicio intentarán instalar automáticamente esta biblioteca, pero pueden fallar en algunos sistemas.

## Modo línea de comandos

También puede usar el programa desde la línea de comandos:

```bash
# En Windows (con entorno virtual)
run_compiler.bat -d practica2

# En macOS/Linux (con entorno virtual)
./run_compiler.sh -d practica2

# Opciones disponibles
python compile_cpp_advanced.py --help
```

Opciones disponibles:
- `-f, --files`: Lista de archivos .cpp a procesar
- `-d, --directory`: Directorio donde buscar archivos .cpp
- `-c, --compiler`: Compilador a utilizar (por defecto: g++)
- `-g, --flags`: Flags de compilación (por defecto: -Wall -std=c++11)
- `-o, --output`: Directorio de salida (por defecto: compiladas_avanzado)

## Estructura de carpetas generada

Para cada programa procesado, se crea una estructura como esta:

```
compiladas_avanzado/
└── nombre_programa/
    ├── nombre_programa           # Ejecutable compilado
    ├── nombre_programa.cpp       # Copia del código fuente
    ├── informe.md                # Documentación completa
    ├── input.txt                 # Datos de entrada usados
    ├── screenshot.png            # Captura de pantalla
    ├── stdout.txt                # Salida estándar del programa
    └── stderr.txt                # Errores producidos (si hay)
```

## Cómo funciona el análisis inteligente

El programa analiza el código fuente para detectar:
- Tipos de datos utilizados (vectores, matrices, cadenas)
- Patrones de entrada comunes (nombres, edades, notas)
- Cantidad de entradas requeridas (cin, getline)

Basándose en este análisis, genera automáticamente datos de prueba adecuados para ejecutar el programa.

## Solución de problemas

### Error: 'Text' object has no attribute 'drop_target_register'

Este error ocurre cuando la biblioteca tkinterdnd2 no está disponible. El programa seguirá funcionando, pero sin la capacidad de arrastrar y soltar archivos. Para solucionar este problema:

1. Instale tkinterdnd2 manualmente:
   ```bash
   # Con el entorno virtual activado
   pip install tkinterdnd2
   ```

2. Si la instalación falla, no se preocupe. Puede seguir utilizando el programa mediante el botón "Añadir Archivos".

### Otros problemas con el entorno virtual

Si encuentra otros errores con el entorno virtual:

1. Elimine la carpeta `.venv`
2. Ejecute nuevamente el script correspondiente a su sistema operativo
3. Si el problema persiste, instale manualmente las dependencias:
   ```bash
   pip install Pillow
   ```

## Autor

Yoquelvis Abreu
Marzo 2024 
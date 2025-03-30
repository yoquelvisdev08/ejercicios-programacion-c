#!/bin/bash
# Script para ejecutar el compilador C++ avanzado usando el entorno virtual

# Colores para mensajes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Función para imprimir mensajes con formato
print_message() {
    local color=$1
    local message=$2
    echo -e "${color}${message}${NC}"
}

# Función para imprimir mensajes de error y salir
error_exit() {
    print_message "$RED" "Error: $1"
    exit 1
}

# Obtener el directorio del script
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR" || error_exit "No se pudo cambiar al directorio del script"

# Verificar si g++ está instalado
if ! command -v g++ &> /dev/null; then
    print_message "$RED" "Error: g++ no está instalado. Por favor, instale las herramientas de desarrollo C++."
    if [[ "$OSTYPE" == "darwin"* ]]; then
        print_message "$YELLOW" "En macOS, puede instalarlo con: xcode-select --install"
    elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
        print_message "$YELLOW" "En Linux, puede instalarlo con: sudo apt-get install g++"
    fi
    exit 1
fi

# Verificar si Python 3 está instalado
if ! command -v python3 &> /dev/null; then
    error_exit "Python 3 no está instalado"
fi

# Verificar la versión de Python
PYTHON_VERSION=$(python3 -c 'import sys; print(".".join(map(str, sys.version_info[:2])))')
MAJOR_VERSION=$(echo $PYTHON_VERSION | cut -d. -f1)
MINOR_VERSION=$(echo $PYTHON_VERSION | cut -d. -f2)

if [ "$MAJOR_VERSION" -lt 3 ] || ([ "$MAJOR_VERSION" -eq 3 ] && [ "$MINOR_VERSION" -lt 7 ]); then
    error_exit "Se requiere Python 3.7 o superior (versión actual: $PYTHON_VERSION)"
fi

# Verificar si se desea mantener el entorno virtual existente
if [ "$1" == "--keep-venv" ]; then
    KEEP_VENV=true
    shift # Eliminar el argumento para que no se pase a main.py
else
    KEEP_VENV=false
fi

# Crear o reutilizar el entorno virtual
if [ -d ".venv" ] && [ "$KEEP_VENV" == "true" ]; then
    print_message "$BLUE" "Reutilizando entorno virtual existente..."
else
    # Eliminar el entorno virtual si existe
    if [ -d ".venv" ]; then
        print_message "$YELLOW" "Eliminando entorno virtual existente..."
        rm -rf .venv
    fi
    
    # Crear nuevo entorno virtual
    print_message "$BLUE" "Creando nuevo entorno virtual..."
    python3 -m venv .venv || error_exit "No se pudo crear el entorno virtual"
fi

# Activar el entorno virtual
if [ -f ".venv/bin/activate" ]; then
    print_message "$BLUE" "Activando entorno virtual..."
    source .venv/bin/activate || error_exit "No se pudo activar el entorno virtual"
    
    # Solo instalar dependencias si el entorno es nuevo
    if [ "$KEEP_VENV" == "false" ]; then
        print_message "$BLUE" "Instalando pip..."
        curl -s https://bootstrap.pypa.io/get-pip.py -o get-pip.py
        python3 get-pip.py --quiet
        rm get-pip.py
        
        print_message "$BLUE" "Actualizando pip..."
        pip install --upgrade pip --quiet
        
        print_message "$BLUE" "Instalando dependencias..."
        pip install --upgrade certifi --quiet
        pip install Pillow --quiet
        pip install fpdf2==2.7.8 --quiet
        pip install reportlab==4.1.0 --quiet
        pip install nltk==3.8.1 --quiet
        
        # Intentar instalar tkinterdnd2 con manejo de errores
        print_message "$BLUE" "Instalando tkinterdnd2..."
        if pip install tkinterdnd2==0.3.0 --quiet; then
            print_message "$GREEN" "tkinterdnd2 instalado correctamente"
        else
            print_message "$YELLOW" "No se pudo instalar tkinterdnd2. El arrastrar y soltar no estará disponible."
        fi
        
        print_message "$BLUE" "Descargando recursos de NLTK..."
        python3 -c '
import nltk
import ssl
try:
    _create_unverified_https_context = ssl._create_unverified_context
except AttributeError:
    pass
else:
    ssl._create_default_https_context = _create_unverified_https_context
nltk.download("punkt", quiet=True)
nltk.download("averaged_perceptron_tagger", quiet=True)
'
    fi
    
    # Ejecutar el script con los argumentos proporcionados
    print_message "$GREEN" "Ejecutando el compilador..."
    python3 main.py "$@"
    EXIT_CODE=$?
    
    # Desactivar el entorno virtual
    deactivate
    
    if [ $EXIT_CODE -eq 0 ]; then
        print_message "$GREEN" "Proceso completado exitosamente."
    else
        print_message "$RED" "El proceso terminó con errores."
        exit $EXIT_CODE
    fi
else
    error_exit "No se encontró el archivo de activación del entorno virtual"
fi

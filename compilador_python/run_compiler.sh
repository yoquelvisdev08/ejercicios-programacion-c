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
    echo -e "${2}${1}${NC}"
}

# Función para imprimir mensajes de error
print_error() {
    print_message "❌ Error: $1" "${RED}"
}

# Función para imprimir mensajes de éxito
print_success() {
    print_message "✓ $1" "${GREEN}"
}

# Función para imprimir mensajes informativos
print_info() {
    print_message "ℹ️  $1" "${BLUE}"
}

# Función para imprimir advertencias
print_warning() {
    print_message "⚠️  $1" "${YELLOW}"
}

# Obtener el directorio del script
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR" || error_exit "No se pudo cambiar al directorio del script"

# Limpiar carpeta de archivos temporales
print_info "Limpiando carpeta de archivos temporales..."
mkdir -p temp_compilation
rm -rf temp_compilation/*
print_success "Carpeta de archivos temporales limpiada correctamente"

# Detectar el sistema operativo
print_info "Detectando sistema operativo..."
OS="$(uname)"
OS_VERSION="$(uname -r)"
print_success "Sistema operativo detectado: $OS ($OS_VERSION)"

# Verificar si g++ está instalado
if ! command -v g++ &> /dev/null; then
    print_error "g++ no está instalado. Por favor, instale las herramientas de desarrollo C++."
    if [[ "$OS" == "Darwin" ]]; then
        print_warning "En macOS, puede instalarlo con: xcode-select --install"
    elif [[ "$OS" == "Linux" ]]; then
        print_warning "En Linux, puede instalarlo con: sudo apt-get install g++"
    fi
    exit 1
fi

# Verificar versión de g++
G_VERSION=$(g++ --version | head -n 1)
print_success "Compilador C++ detectado: $G_VERSION"

# Verificar si Python 3 está instalado
if ! command -v python3 &> /dev/null; then
    print_error "Python 3 no está instalado"
    exit 1
fi

# Verificar la versión de Python
PYTHON_VERSION=$(python3 -V | cut -d' ' -f2 | cut -d'.' -f1)
print_success "Versión de Python: $PYTHON_VERSION"

# Verificar acceso a la pantalla (importante para macOS)
if [[ "$OS" == "Darwin" ]]; then
    print_info "Verificando permisos de captura de pantalla..."
    
    # Verificar si tenemos permisos para tomar capturas
    if ! tccutil status Screen\ Recording 2>/dev/null | grep -q "DENIED"; then
        print_success "Permisos de captura de pantalla: OK"
    else
        print_warning "Se requieren permisos de captura de pantalla."
        print_info "Por favor, otorgue permisos en Preferencias del Sistema > Seguridad y Privacidad > Privacidad > Grabación de pantalla"
        open "x-apple.systempreferences:com.apple.preference.security?Privacy_ScreenCapture"
        read -p "Presione Enter después de otorgar los permisos..."
    fi
fi

# Procesar argumentos para opciones relacionadas con el entorno virtual
CREATE_NEW_VENV=false
CLEAN_TEMP=false
KEEP_CURRENT=false
VENV_DIR=".venv"

# Verificar opciones
for arg in "$@"; do
    if [[ "$arg" == "--new-venv" ]]; then
        CREATE_NEW_VENV=true
        # Eliminar el argumento para que no se pase a main.py
        args=("$@")
        args=("${args[@]/"$arg"/}")
        set -- "${args[@]}"
        break
    elif [[ "$arg" == "--keep-venv" ]]; then
        # Para compatibilidad con versiones anteriores, --keep-venv sigue funcionando
        # pero ahora es redundante ya que es el comportamiento por defecto
        print_warning "Nota: --keep-venv es ahora el comportamiento por defecto"
        # Eliminar el argumento para que no se pase a main.py
        args=("$@")
        args=("${args[@]/"$arg"/}")
        set -- "${args[@]}"
        break
    elif [[ "$arg" == "--clean-temp" ]]; then
        CLEAN_TEMP=true
    elif [[ "$arg" == "--keep-current" ]]; then
        KEEP_CURRENT=true
    fi
done

# Crear o reutilizar el entorno virtual
if [ ! -d "$VENV_DIR" ]; then
    print_info "No existe entorno virtual, creando uno nuevo..."
    python3 -m venv "$VENV_DIR"
    NEED_INSTALL_DEPS=true
elif [ "$CREATE_NEW_VENV" == "true" ]; then
    print_info "Recreando entorno virtual según lo solicitado..."
    rm -rf "$VENV_DIR"
    python3 -m venv "$VENV_DIR"
    NEED_INSTALL_DEPS=true
else
    print_info "Reutilizando entorno virtual existente..."
    NEED_INSTALL_DEPS=false
fi

# Activar el entorno virtual
if [ -f "$VENV_DIR/bin/activate" ]; then
    print_info "Activando entorno virtual..."
    source "$VENV_DIR/bin/activate"
    
    # Solo instalar dependencias si el entorno es nuevo o se solicitó recrear
    if [ "$NEED_INSTALL_DEPS" == "true" ]; then
        print_info "Actualizando pip..."
        python3 -m pip install --upgrade pip
        
        print_info "Instalando dependencias..."
        
        # Instalar dependencias con manejo de errores
        install_package() {
            local package=$1
            local version=$2
            
            if [ -z "$version" ]; then
                print_info "Instalando $package..."
                if pip install "$package" --quiet; then
                    print_success "$package instalado correctamente"
                else
                    print_warning "⚠️ Error al instalar $package. Intentando continuar..."
                fi
            else
                print_info "Instalando $package==$version..."
                if pip install "$package==$version" --quiet; then
                    print_success "$package==$version instalado correctamente"
                else
                    print_warning "⚠️ Error al instalar $package==$version. Intentando sin versión específica..."
                    if pip install "$package" --quiet; then
                        print_success "$package instalado correctamente (sin versión específica)"
                    else
                        print_warning "⚠️ Error al instalar $package. Intentando continuar..."
                    fi
                fi
            fi
        }
        
        # Instalar paquetes esenciales
        pip install --upgrade certifi --quiet
        install_package "Pillow" "10.2.0"
        install_package "fpdf2" "2.7.8"
        install_package "reportlab" "4.1.0"
        install_package "nltk" "3.8.1"
        
        # Instalar ttkbootstrap correctamente
        print_info "Instalando ttkbootstrap..."
        pip install ttkbootstrap==1.10.1
        if [ $? -eq 0 ]; then
            print_success "ttkbootstrap instalado correctamente"
        else
            print_warning "⚠️ No se pudo instalar ttkbootstrap. La interfaz no tendrá el tema moderno."
        fi
        
        # Intentar instalar tkinterdnd2 con manejo de errores
        print_info "Instalando tkinterdnd2..."
        pip install tkinterdnd2==0.3.0
        if [ $? -eq 0 ]; then
            print_success "tkinterdnd2 instalado correctamente"
        else
            print_warning "⚠️ No se pudo instalar tkinterdnd2 versión 0.3.0. Intentando con otras versiones..."
            # Intentar con versión específica para Python 3.10+
            if pip install "git+https://github.com/Eliav2/tkinterdnd2@de3f6bb" --quiet; then
                print_success "tkinterdnd2 instalado desde GitHub correctamente"
            else
                # Intentar con la instalación genérica
                if pip install tkinterdnd2 --quiet; then
                    print_success "tkinterdnd2 instalado correctamente (versión genérica)"
                else
                    print_warning "⚠️ No se pudo instalar tkinterdnd2. El arrastrar y soltar no estará disponible."
                fi
            fi
        fi
        
        print_info "Descargando recursos de NLTK..."
        python3 -c '
import nltk
import ssl
try:
    _create_unverified_https_context = ssl._create_unverified_context
except AttributeError:
    pass
else:
    ssl._create_default_https_context = _create_unverified_https_context
try:
    nltk.download("punkt", quiet=True)
    nltk.download("averaged_perceptron_tagger", quiet=True)
    print("Recursos de NLTK descargados correctamente")
except Exception as e:
    print(f"Error al descargar recursos de NLTK: {e}")
    print("El programa continuará, pero algunas funciones pueden no estar disponibles")
'
    else
        print_success "Usando dependencias ya instaladas"
    fi
    
    # Crear directorios necesarios
    print_info "Asegurando que existen directorios de trabajo..."
    mkdir -p temp_compilation output
    
    # Si estamos en modo --new-venv, solo mostrar información y salir
    if [ "$CREATE_NEW_VENV" == "true" ]; then
        echo
        echo "=== Compilador C++ Avanzado ==="
        echo "Sistema: $OS $OS_VERSION"
        echo "Python: $(python3 -V | cut -d' ' -f2)"
        echo "Arquitectura: $(uname -m)"
        echo "=============================="
        echo
        print_success "Entorno virtual creado y dependencias instaladas correctamente"
        exit 0
    fi
    
    # Detectar modo de ejecución
    NOGUI=false
    for arg in "$@"; do
        if [ "$arg" == "--no-gui" ]; then
            NOGUI=true
            break
        fi
    done
    
    # Informar modo de ejecución
    if [ "$NOGUI" == "true" ]; then
        print_success "Ejecutando en modo consola..."
    else
        print_success "Ejecutando en modo gráfico..."
    fi
    
    # Ejecutar el script con los argumentos proporcionados
    print_success "Iniciando compilador C++..."

    # Si se solicitó limpiar temporales, pasamos los argumentos apropiados
    if [ "$CLEAN_TEMP" == "true" ]; then
        CLEAN_ARGS="--clean-temp"
        if [ "$KEEP_CURRENT" == "true" ]; then
            CLEAN_ARGS="$CLEAN_ARGS --keep-current"
        fi
        python3 main.py $CLEAN_ARGS
    else
        python3 main.py "$@"
    fi

    EXIT_CODE=$?
    
    # Desactivar el entorno virtual
    deactivate
    
    if [ $EXIT_CODE -eq 0 ]; then
        print_success "Proceso completado exitosamente."
    else
        print_error "El proceso terminó con errores (código: $EXIT_CODE)."
        exit $EXIT_CODE
    fi
else
    print_error "No se encontró el archivo de activación del entorno virtual"
    exit 1
fi

print_info "Nota: Para recrear el entorno virtual y reinstalar dependencias, use la opción --new-venv"

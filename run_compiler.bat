@echo off
REM Script para ejecutar el compilador C++ avanzado usando el entorno virtual en Windows

REM Cambiar al directorio del script
cd /d "%~dp0"

REM Verificar si el entorno virtual existe
if not exist .venv (
    echo Entorno virtual no encontrado. Creando...
    python -m venv .venv
    
    REM Verificar si se creó correctamente
    if exist .venv\Scripts\activate.bat (
        call .venv\Scripts\activate.bat
        echo Instalando dependencias...
        pip install Pillow
        
        REM Intentar instalar tkinterdnd2 con manejo de errores
        echo Intentando instalar tkinterdnd2 (opcional para arrastrar y soltar)...
        pip install tkinterdnd2 2>nul || echo Nota: tkinterdnd2 no se pudo instalar. La funcionalidad de arrastrar y soltar estara desactivada.
    ) else (
        echo Error: No se pudo crear el entorno virtual.
        exit /b 1
    )
) else (
    REM Activar entorno virtual existente
    call .venv\Scripts\activate.bat
)

REM Ejecutar el compilador con los argumentos proporcionados
python compile_cpp_advanced.py %*

REM Desactivar entorno virtual al finalizar
call deactivate

echo Proceso completado. 
# Compilador de archivos C++ por lotes

Este repositorio contiene ejercicios de programación en C++ y un script en Python para compilar todos los archivos por lotes.

## Requisitos

Para usar el script de compilación necesitas:

- Python 3.6 o superior
- Compilador de C++ (g++ por defecto)
- Biblioteca colorama para Python

Para instalar colorama:

```bash
pip install colorama
```

## Estructura del repositorio

- `practica2/`: Directorio que contiene todos los ejercicios en C++
- `compile_cpp.py`: Script para compilar automáticamente todos los archivos .cpp
- `compiladas/`: Directorio donde se guardarán los ejecutables (se crea automáticamente)

## Cómo usar el script de compilación

### Uso básico

Para compilar todos los archivos .cpp en la carpeta `practica2` y guardar los ejecutables en `compiladas`:

```bash
python compile_cpp.py
```

### Opciones disponibles

El script tiene varias opciones para personalizar la compilación:

```bash
python compile_cpp.py --help
```

| Opción | Descripción |
|--------|-------------|
| `-d`, `--directory` | Directorio donde buscar los archivos .cpp (por defecto: practica2) |
| `-o`, `--output` | Directorio donde guardar los ejecutables (por defecto: compiladas) |
| `-c`, `--compiler` | Compilador a usar (por defecto: g++) |
| `-f`, `--flags` | Flags de compilación (por defecto: -Wall -std=c++11) |
| `-p`, `--pattern` | Patrón para buscar archivos (por defecto: *.cpp) |

### Ejemplos

Compilar archivos de un directorio específico:
```bash
python compile_cpp.py -d otracarpeta
```

Usar un compilador diferente:
```bash
python compile_cpp.py -c clang++
```

Establecer flags de compilación personalizados:
```bash
python compile_cpp.py -f "-Wall -std=c++17 -O2"
```

## Ejercicios incluidos

En la carpeta `practica2` encontrarás ejercicios organizados por bloques:

- **Bloque 5**: Ejercicios de arreglos y vectores
- **Bloque 6**: Ejercicios de matrices y tablas
- **Bloque 7**: Ejercicios de cadenas de caracteres
- **Bloque 8**: Ejercicios de estructuras

## Autor

Yoquelvis Abreu
Marzo 2024 
/*
 * 📝 COPIA DE CADENAS DE CARACTERES 📝
 * ==================================
 *
 * Bloque 7: Ejercicio 2
 * --------------------
 * Programa que pide al usuario una cadena de caracteres, la almacena en un arreglo
 * y copia todo su contenido hacia otro arreglo de caracteres.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <iomanip>
#include <string.h> // Para strcpy()
using namespace std;

// Constantes para colores (ANSI escape codes)
const string COLOR_RESET = "\033[0m";
const string COLOR_TITLE = "\033[1;36m";  // Cyan brillante
const string COLOR_HIGHLIGHT = "\033[1;33m";  // Amarillo brillante
const string COLOR_INPUT = "\033[1;32m";  // Verde brillante
const string COLOR_ORIGINAL = "\033[1;34m";  // Azul brillante
const string COLOR_COPY = "\033[1;35m";  // Magenta brillante
const string COLOR_INFO = "\033[1;37m";  // Blanco brillante

// Función para limpiar la pantalla
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Función para mostrar el banner del programa
void mostrarBanner() {
    cout << COLOR_TITLE << "\n";
    cout << "╔═══════════════════════════════════════╗\n";
    cout << "║     COPIA DE CADENAS DE CARACTERES    ║\n";
    cout << "╚═══════════════════════════════════════╝\n\n" << COLOR_RESET;
}

// Función para mostrar una cadena con formato visual
void mostrarCadena(const char* cadena, const char* titulo, string color) {
    int longitud = strlen(cadena);
    
    cout << COLOR_HIGHLIGHT << "\n" << titulo << COLOR_RESET << endl;
    
    // Mostrar cadena con formato de tabla
    // Línea superior
    cout << color << "┌";
    for(int i = 0; i < longitud; i++) {
        cout << "───";
    }
    cout << "┐\n";
    
    // Índices
    cout << "│";
    for(int i = 0; i < longitud; i++) {
        cout << setw(2) << i << " ";
    }
    cout << "│\n";
    
    // Línea separadora
    cout << "├";
    for(int i = 0; i < longitud; i++) {
        cout << "───";
    }
    cout << "┤\n";
    
    // Caracteres
    cout << "│";
    for(int i = 0; i < longitud; i++) {
        cout << " " << cadena[i] << " ";
    }
    cout << "│\n";
    
    // Línea inferior
    cout << "└";
    for(int i = 0; i < longitud; i++) {
        cout << "───";
    }
    cout << "┘" << COLOR_RESET << "\n";
    
    // Mostrar información adicional
    cout << COLOR_INFO << "   Longitud: " << longitud << " caracteres\n";
    cout << "   Dirección de memoria: " << (void*)cadena << COLOR_RESET << "\n";
}

// Función para mostrar una animación del proceso de copia
void mostrarAnimacionCopia() {
    cout << "\n" << COLOR_HIGHLIGHT;
    cout << "        ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓\n";
    cout << "    ┌───────────────────────────┐\n";
    cout << "    │  COPIANDO CARACTERES...   │\n";
    cout << "    └───────────────────────────┘\n";
    cout << "        ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑\n" << COLOR_RESET;
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaracion de variables
    char cadena1[100]; // Arreglo original
    char cadena2[100]; // Arreglo de destino
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa pide una cadena de caracteres al usuario\n";
    cout << "               y la copia a otro arreglo usando la función strcpy().\n\n";
    
    // Pedir la cadena al usuario
    cout << COLOR_HIGHLIGHT << "🔤 Ingrese una cadena de caracteres: " << COLOR_INPUT;
    cin.getline(cadena1, 100, '\n');
    cout << COLOR_RESET;
    
    // Mostrar la cadena original
    mostrarCadena(cadena1, "📊 CADENA ORIGINAL:", COLOR_ORIGINAL);
    
    // Mostrar animación de copia
    mostrarAnimacionCopia();
    
    // Copiar el contenido de cadena1 a cadena2
    strcpy(cadena2, cadena1);
    
    // Mostrar la cadena copiada
    mostrarCadena(cadena2, "📋 CADENA COPIADA:", COLOR_COPY);
    
    // Explicación del proceso
    cout << "\n" << COLOR_HIGHLIGHT << "📝 EXPLICACIÓN DEL PROCESO:" << COLOR_RESET << endl;
    cout << "1. Se reservó espacio para dos arreglos de 100 caracteres.\n";
    cout << "2. Se leyó la cadena del usuario al primer arreglo.\n";
    cout << "3. Se utilizó strcpy() para copiar cada carácter al segundo arreglo.\n";
    cout << "4. La copia incluye automáticamente el carácter nulo '\\0' al final.\n\n";
    
    // Verificación de la copia
    bool sonIguales = (strcmp(cadena1, cadena2) == 0);
    cout << COLOR_HIGHLIGHT << "✅ VERIFICACIÓN: " << COLOR_RESET;
    
    if(sonIguales) {
        cout << "Las cadenas son idénticas, la copia fue exitosa.\n\n";
    } else {
        cout << "Error: Las cadenas no son idénticas.\n\n";
    }
    
    // Añadir instrucciones finales
    cout << "Presione Enter para finalizar...";
    cin.get();
    
    return 0;
} 
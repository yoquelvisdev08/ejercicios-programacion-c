/*
 * 📝 VERIFICADOR DE LONGITUD DE CADENAS 📏
 * =====================================
 * 
 * Bloque 7: Ejercicio 1
 * --------------------
 * Programa que pide al usuario una cadena de caracteres, verifica la longitud de la cadena,
 * y si ésta supera a 10 caracteres la muestra en pantalla, caso contrario no la muestra.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h> // Para strlen()
#include <iomanip>  // Para setw()
using namespace std;

// Constantes para colores (ANSI escape codes)
const string COLOR_RESET = "\033[0m";
const string COLOR_TITLE = "\033[1;36m";  // Cyan brillante
const string COLOR_HIGHLIGHT = "\033[1;33m";  // Amarillo brillante
const string COLOR_INPUT = "\033[1;32m";  // Verde brillante
const string COLOR_SUCCESS = "\033[1;92m";  // Verde claro brillante
const string COLOR_ERROR = "\033[1;91m";  // Rojo claro brillante
const string COLOR_INFO = "\033[1;94m";  // Azul claro brillante

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
    cout << "╔═══════════════════════════════════════════╗\n";
    cout << "║     VERIFICADOR DE LONGITUD DE CADENAS    ║\n";
    cout << "╚═══════════════════════════════════════════╝\n\n" << COLOR_RESET;
}

// Función para mostrar una cadena con formato visual
void mostrarCadena(const char* cadena, int longitud) {
    cout << COLOR_HIGHLIGHT << "\n📊 ANÁLISIS DE LA CADENA:\n";
    cout << "========================\n" << COLOR_RESET;
    
    cout << COLOR_INFO << "┌";
    for(int i = 0; i < longitud + 2; i++) cout << "─";
    cout << "┐\n";
    
    cout << "│ " << cadena << " │\n";
    
    cout << "└";
    for(int i = 0; i < longitud + 2; i++) cout << "─";
    cout << "┘" << COLOR_RESET << "\n\n";
    
    cout << "📏 Longitud: " << COLOR_HIGHLIGHT << longitud << " caracteres" << COLOR_RESET << "\n";
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaracion de variables
    char cadena[100]; // Arreglo para almacenar la cadena
    int longitud; // Para almacenar la longitud de la cadena
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa verifica si una cadena tiene más de 10 caracteres\n";
    cout << "               y la muestra solo si cumple esta condición.\n\n";
    
    // Pedir la cadena al usuario con formato mejorado
    cout << COLOR_HIGHLIGHT << "🔤 Digite una cadena de caracteres: " << COLOR_INPUT;
    cin.getline(cadena, 100, '\n');
    cout << COLOR_RESET;
    
    // Calcular la longitud de la cadena
    longitud = strlen(cadena);
    
    // Verificar si la longitud supera 10 caracteres
    if(longitud > 10) {
        cout << "\n" << COLOR_SUCCESS << "✅ La cadena tiene más de 10 caracteres." << COLOR_RESET;
        mostrarCadena(cadena, longitud);
    } else {
        cout << "\n" << COLOR_ERROR << "⚠️ La cadena tiene " << longitud << " caracteres, no se mostrará el contenido." << COLOR_RESET << "\n";
        cout << COLOR_INFO << "   La cadena debe tener más de 10 caracteres para ser mostrada." << COLOR_RESET << "\n";
    }
    
    // Añadir instrucciones finales
    cout << "\nPresione Enter para finalizar...";
    cin.get();
    
    return 0;
} 
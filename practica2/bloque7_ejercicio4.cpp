/*
 * 🔠 CONCATENACIÓN DE CADENAS 🔠
 * ===========================
 *
 * Bloque 7: Ejercicio 4
 * --------------------
 * Programa que crea una cadena que tiene la frase "Hola que tal", luego crea otra cadena
 * para preguntarle al usuario su nombre, por ultimo añade el nombre al final de la primera
 * cadena y muestra el mensaje completo.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <iomanip>
#include <string.h> // Para strcat()
using namespace std;

// Constantes para colores (ANSI escape codes)
const string COLOR_RESET = "\033[0m";
const string COLOR_TITLE = "\033[1;36m";  // Cyan brillante
const string COLOR_HIGHLIGHT = "\033[1;33m";  // Amarillo brillante
const string COLOR_INPUT = "\033[1;32m";  // Verde brillante
const string COLOR_STRING1 = "\033[1;34m";  // Azul brillante
const string COLOR_STRING2 = "\033[1;35m";  // Magenta brillante
const string COLOR_RESULT = "\033[1;31m";  // Rojo brillante

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
    cout << "╔═══════════════════════════════════╗\n";
    cout << "║      CONCATENACIÓN DE CADENAS     ║\n";
    cout << "╚═══════════════════════════════════╝\n\n" << COLOR_RESET;
}

// Función para mostrar una cadena con formato visual
void mostrarCadena(const char* cadena, const char* titulo, string color) {
    int longitud = strlen(cadena);
    
    cout << COLOR_HIGHLIGHT << "\n" << titulo << COLOR_RESET << endl;
    
    // Mostrar cadena con formato de caja
    cout << color << "┌";
    for(int i = 0; i < longitud + 2; i++) cout << "─";
    cout << "┐\n";
    
    cout << "│ " << cadena << " │\n";
    
    cout << "└";
    for(int i = 0; i < longitud + 2; i++) cout << "─";
    cout << "┘" << COLOR_RESET << "\n";
    
    // Información adicional
    cout << "   Longitud: " << longitud << " caracteres\n";
}

// Función para mostrar una animación del proceso de concatenación
void mostrarAnimacionConcatenacion() {
    cout << "\n" << COLOR_HIGHLIGHT;
    cout << "        ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓\n";
    cout << "    ┌───────────────────────────┐\n";
    cout << "    │  CONCATENANDO CADENAS...  │\n";
    cout << "    └───────────────────────────┘\n";
    cout << "        ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑\n" << COLOR_RESET;
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaracion de variables
    char mensaje[100] = "Hola que tal"; // Mensaje inicial
    char nombre[50]; // Para almacenar el nombre del usuario
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa concatena (une) el nombre del usuario\n";
    cout << "               al final de un mensaje predefinido.\n\n";
    
    // Mostrar el mensaje inicial
    mostrarCadena(mensaje, "📝 MENSAJE INICIAL:", COLOR_STRING1);
    
    // Pedir el nombre al usuario
    cout << "\n" << COLOR_HIGHLIGHT << "👤 Por favor, digite su nombre: " << COLOR_INPUT;
    cin.getline(nombre, 50, '\n');
    cout << COLOR_RESET;
    
    // Mostrar el nombre ingresado
    mostrarCadena(nombre, "👤 NOMBRE INGRESADO:", COLOR_STRING2);
    
    // Mostrar animación de concatenación
    mostrarAnimacionConcatenacion();
    
    // Añadir espacio antes de concatenar
    strcat(mensaje, " ");
    
    // Añadir el nombre al final del mensaje
    strcat(mensaje, nombre);
    
    // Mostrar el mensaje completo
    mostrarCadena(mensaje, "✅ MENSAJE COMPLETO:", COLOR_RESULT);
    
    // Explicación del proceso
    cout << "\n" << COLOR_HIGHLIGHT << "📝 EXPLICACIÓN DEL PROCESO:" << COLOR_RESET << endl;
    cout << "1. Se creó una primera cadena con el texto \"Hola que tal\".\n";
    cout << "2. Se obtuvo el nombre del usuario: \"" << nombre << "\".\n";
    cout << "3. Se añadió un espacio en blanco a la primera cadena.\n";
    cout << "4. Se utilizó strcat() para unir las dos cadenas.\n";
    cout << "5. El resultado final combina ambos textos.\n\n";
    
    // Añadir instrucciones finales
    cout << "Presione Enter para finalizar...";
    cin.get();
    
    return 0;
} 
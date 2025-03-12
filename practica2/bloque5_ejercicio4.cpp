/*
 * 🔄 VECTOR EN ORDEN INVERSO 🔄
 * ===========================
 *
 * Bloque 5: Ejercicio 4
 * --------------------
 * Programa que define un vector de números y muestra en la
 * salida estándar el vector en orden inverso—del último al primer elemento.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <iomanip>
using namespace std;

// Constantes para colores (ANSI escape codes)
const string COLOR_RESET = "\033[0m";
const string COLOR_TITLE = "\033[1;36m";  // Cyan brillante
const string COLOR_HIGHLIGHT = "\033[1;33m";  // Amarillo brillante
const string COLOR_INPUT = "\033[1;32m";  // Verde brillante
const string COLOR_VECTOR = "\033[1;34m";  // Azul brillante
const string COLOR_VECTOR_INVERSE = "\033[1;35m";  // Magenta brillante
const string COLOR_ARROW = "\033[1;31m";  // Rojo brillante

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
    cout << "║      VECTOR EN ORDEN INVERSO      ║\n";
    cout << "╚═══════════════════════════════════╝\n\n" << COLOR_RESET;
}

// Función para mostrar un vector con formato mejorado
void mostrarVector(const int vector[], int tamanio, string titulo, string color) {
    cout << COLOR_HIGHLIGHT << "\n" << titulo << COLOR_RESET << endl;
    
    cout << color;
    // Línea superior del vector
    cout << "┌";
    for(int i = 0; i < tamanio; i++) {
        cout << "──────";
        if(i < tamanio-1) cout << "┬";
    }
    cout << "┐\n";
    
    // Índices del vector
    cout << "│";
    for(int i = 0; i < tamanio; i++) {
        cout << " [" << setw(2) << i << "] ";
        if(i < tamanio-1) cout << "│";
    }
    cout << "│\n";
    
    // Línea separadora
    cout << "├";
    for(int i = 0; i < tamanio; i++) {
        cout << "──────";
        if(i < tamanio-1) cout << "┼";
    }
    cout << "┤\n";
    
    // Valores del vector
    cout << "│";
    for(int i = 0; i < tamanio; i++) {
        cout << " " << setw(4) << vector[i] << " ";
        if(i < tamanio-1) cout << "│";
    }
    cout << "│\n";
    
    // Línea inferior del vector
    cout << "└";
    for(int i = 0; i < tamanio; i++) {
        cout << "──────";
        if(i < tamanio-1) cout << "┴";
    }
    cout << "┘" << COLOR_RESET << "\n";
}

// Función para mostrar una animación de inversión
void mostrarAnimacionInversion() {
    cout << "\n" << COLOR_ARROW;
    cout << "              ↓ ↓ ↓ ↓ ↓\n";
    cout << "        ┌─────────────────────┐\n";
    cout << "        │   INVIRTIENDO...    │\n";
    cout << "        └─────────────────────┘\n";
    cout << "              ↑ ↑ ↑ ↑ ↑\n" << COLOR_RESET;
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaracion de variables
    const int MAX = 100;  // Tamaño máximo del vector
    int numeros[MAX];     // Vector de números
    int invertido[MAX];   // Vector para almacenar los números en orden inverso
    int n;                // Tamaño real del vector
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa almacena números en un vector\n";
    cout << "               y los muestra en orden inverso.\n\n";
    
    // Solicitar el tamaño del vector
    do {
        cout << COLOR_HIGHLIGHT << "📏 Ingrese el tamaño del vector (1-" << MAX << "): " << COLOR_INPUT;
        cin >> n;
        cout << COLOR_RESET;
        
        if(n <= 0 || n > MAX) {
            cout << "\n⚠️  Error: El tamaño debe estar entre 1 y " << MAX << ".\n\n";
        }
    } while(n <= 0 || n > MAX);
    
    cout << "\n"; // Salto de línea entre inputs
    
    // Solicitar los elementos del vector
    cout << COLOR_HIGHLIGHT << "🔢 Ingrese los elementos del vector:\n";
    cout << "==================================\n" << COLOR_RESET;
    
    for(int i = 0; i < n; i++) {
        cout << COLOR_HIGHLIGHT << "   Elemento [" << i << "]: " << COLOR_INPUT;
        cin >> numeros[i];
        cout << COLOR_RESET;
    }
    
    // Crear vector invertido
    for(int i = 0; i < n; i++) {
        invertido[i] = numeros[n-1-i];
    }
    
    // Mostrar el vector original
    mostrarVector(numeros, n, "📊 Vector original:", COLOR_VECTOR);
    
    // Mostrar animación de inversión
    mostrarAnimacionInversion();
    
    // Mostrar el vector en orden inverso
    mostrarVector(invertido, n, "🔄 Vector inverso:", COLOR_VECTOR_INVERSE);
    
    // Añadir instrucciones finales
    cout << "\n" << COLOR_HIGHLIGHT << "✅ Inversión de vector completada con éxito" << COLOR_RESET << "\n\n";
    cout << "Presione Enter para finalizar...";
    cin.ignore();
    cin.get();
    
    return 0;
} 
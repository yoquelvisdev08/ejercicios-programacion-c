/*
 * 📊 VISUALIZACIÓN DE VECTOR CON ÍNDICES 📊
 * =======================================
 *
 * Bloque 5: Ejercicio 3
 * --------------------
 * Programa que lee de la entrada estándar un vector de números y 
 * muestra en la salida estándar los números del vector con sus índices asociados.
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
const string COLOR_TABLE_HEADER = "\033[1;37;44m";  // Blanco brillante sobre azul
const string COLOR_INDEX = "\033[1;34m";  // Azul brillante
const string COLOR_VALUE = "\033[1;35m";  // Magenta brillante

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
    cout << "╔══════════════════════════════════════════╗\n";
    cout << "║    VISUALIZACIÓN DE VECTOR CON ÍNDICES   ║\n";
    cout << "╚══════════════════════════════════════════╝\n\n" << COLOR_RESET;
}

// Función para mostrar el vector con sus índices en un formato de tabla mejorado
void mostrarVectorConIndices(const int vector[], int tamanio) {
    cout << COLOR_HIGHLIGHT << "\n📊 VECTOR CON ÍNDICES:\n";
    cout << "===================\n\n" << COLOR_RESET;
    
    // Encabezado de la tabla con color
    cout << COLOR_TABLE_HEADER << "┌────────────┬─────────────┐\n";
    cout << "│   ÍNDICE   │    VALOR    │\n";
    cout << "├────────────┼─────────────┤" << COLOR_RESET << "\n";
    
    // Filas de la tabla
    for(int i = 0; i < tamanio; i++) {
        cout << "│ " << COLOR_INDEX << setw(10) << i << COLOR_RESET 
             << " │ " << COLOR_VALUE << setw(11) << vector[i] << COLOR_RESET << " │\n";
        
        // Línea separadora excepto después de la última fila
        if(i < tamanio-1) {
            cout << "├────────────┼─────────────┤\n";
        }
    }
    
    // Línea inferior de la tabla
    cout << "└────────────┴─────────────┘\n\n";
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaracion de variables
    const int MAX = 100;  // Tamaño máximo del vector
    int numeros[MAX];     // Vector de números
    int n;                // Tamaño real del vector
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa lee números introducidos por el usuario\n";
    cout << "               y muestra el vector con sus índices asociados.\n\n";
    
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
    
    // Mostrar el vector con sus índices usando la función mejorada
    mostrarVectorConIndices(numeros, n);
    
    // Añadir instrucciones finales
    cout << COLOR_HIGHLIGHT << "✅ Vector mostrado con éxito" << COLOR_RESET << "\n\n";
    cout << "Presione Enter para finalizar...";
    cin.ignore();
    cin.get();
    
    return 0;
} 
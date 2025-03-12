/*
 * 🧮 MULTIPLICACIÓN DE ELEMENTOS EN UN VECTOR 🧮
 * =========================================
 *
 * Bloque 5: Ejercicio 2
 * --------------------
 * Programa que define un vector de números y calcula la multiplicación
 * acumulada de sus elementos.
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
const string COLOR_RESULT = "\033[1;35m";  // Magenta brillante

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
    cout << "╔═════════════════════════════════════════════╗\n";
    cout << "║   MULTIPLICACIÓN DE ELEMENTOS EN VECTOR     ║\n";
    cout << "╚═════════════════════════════════════════════╝\n\n" << COLOR_RESET;
}

// Función para mostrar el vector con formato mejorado
void mostrarVector(const int vector[], int tamanio, string titulo) {
    cout << COLOR_HIGHLIGHT << "\n" << titulo << COLOR_RESET << endl;
    
    // Línea superior del vector
    cout << COLOR_VECTOR << "┌";
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

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaracion de variables
    int tamanio;
    const int MAX = 15; // Limitamos para mejor visualización
    int numeros[MAX];      // Vector de hasta MAX numeros enteros
    int multiplicacion = 1; // Variable para almacenar la multiplicación acumulada
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa almacena números en un vector\n";
    cout << "               y calcula el producto de todos ellos.\n\n";
    
    // Solicitar tamaño del vector
    do {
        cout << COLOR_HIGHLIGHT << "📏 Ingrese el tamaño del vector (1-" << MAX << "): " << COLOR_INPUT;
        cin >> tamanio;
        cout << COLOR_RESET;
        
        if(tamanio <= 0 || tamanio > MAX) {
            cout << "\n⚠️  Error: El tamaño debe estar entre 1 y " << MAX << ".\n\n";
        }
    } while(tamanio <= 0 || tamanio > MAX);
    
    cout << "\n"; // Salto de línea entre inputs
    
    // Solicitar valores al usuario
    cout << COLOR_HIGHLIGHT << "🔢 Ingrese los valores del vector:\n";
    cout << "================================\n" << COLOR_RESET;
    
    for(int i = 0; i < tamanio; i++) {
        cout << COLOR_HIGHLIGHT << "   Elemento [" << i << "]: " << COLOR_INPUT;
        cin >> numeros[i];
        cout << COLOR_RESET;
    }
    
    // Calcular la multiplicación de los elementos del vector
    for(int i = 0; i < tamanio; i++) {
        multiplicacion *= numeros[i]; // Acumulamos el producto de cada elemento
    }
    
    // Mostrar el vector
    mostrarVector(numeros, tamanio, "📊 Vector ingresado:");
    
    // Mostrar el cálculo paso a paso
    cout << "\n" << COLOR_HIGHLIGHT << "🔢 Cálculo: " << COLOR_RESULT;
    for(int i = 0; i < tamanio; i++) {
        cout << numeros[i];
        if(i < tamanio-1) cout << " × ";
    }
    cout << " = " << multiplicacion << COLOR_RESET << "\n";
    
    // Mostrar el resultado con formato
    cout << "\n" << COLOR_RESULT << "✅ RESULTADO: La multiplicación de todos los elementos es " << multiplicacion << COLOR_RESET << "\n\n";
    
    // Añadir instrucciones finales
    cout << "Presione Enter para finalizar...";
    cin.ignore();
    cin.get();
    
    return 0;
} 
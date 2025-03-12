/*
 * 🎲 MATRIZ CON NÚMEROS ALEATORIOS 🎲
 * ===================================
 *
 * Bloque 6: Ejercicio 4
 * --------------------
 * Programa que crea una matriz preguntando al usuario el número de filas y columnas,
 * la llena de números aleatorios, copia el contenido a otra matriz y la muestra en pantalla.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <iomanip>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
using namespace std;

// Constantes para colores (ANSI escape codes)
const string COLOR_RESET = "\033[0m";
const string COLOR_TITLE = "\033[1;36m";  // Cyan brillante
const string COLOR_HIGHLIGHT = "\033[1;33m";  // Amarillo brillante
const string COLOR_INPUT = "\033[1;32m";  // Verde brillante
const string COLOR_ROW = "\033[1;35m";  // Magenta brillante
const string COLOR_COL = "\033[1;34m";  // Azul brillante
const string COLOR_VALUE = "\033[1;37m";  // Blanco brillante
const string COLOR_COPY = "\033[1;31m";   // Rojo brillante

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
    cout << "║     MATRIZ CON NÚMEROS ALEATORIOS     ║\n";
    cout << "╚═══════════════════════════════════════╝\n\n" << COLOR_RESET;
}

// Función para mostrar una matriz con formato mejorado
void mostrarMatriz(const int matriz[50][50], int filas, int columnas, string titulo, string color) {
    cout << COLOR_HIGHLIGHT << "\n" << titulo << COLOR_RESET << endl;
    
    // Encabezado de columnas
    cout << "      ";
    for(int j = 0; j < columnas; j++) {
        cout << COLOR_COL << setw(4) << "Col " << j << " " << COLOR_RESET;
    }
    cout << "\n";
    
    // Línea separadora
    cout << "      ";
    for(int j = 0; j < columnas; j++) {
        cout << "--------";
    }
    cout << "\n";
    
    // Contenido de la matriz
    for(int i = 0; i < filas; i++) {
        // Índice de fila
        cout << COLOR_ROW << " Fila " << setw(1) << i << " |" << COLOR_RESET;
        
        // Valores de la fila
        for(int j = 0; j < columnas; j++) {
            cout << color << setw(7) << matriz[i][j] << " " << COLOR_RESET;
        }
        cout << "\n";
        
        // Separador entre filas (excepto después de la última)
        if(i < filas - 1) {
            cout << "       |";
            for(int j = 0; j < columnas; j++) {
                cout << "--------";
            }
            cout << "\n";
        }
    }
}

// Función para mostrar una animación del proceso de copia
void mostrarAnimacionCopia() {
    cout << "\n" << COLOR_COPY;
    cout << "        ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓\n";
    cout << "    ┌───────────────────────────┐\n";
    cout << "    │  COPIANDO DATOS...        │\n";
    cout << "    └───────────────────────────┘\n";
    cout << "        ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑\n" << COLOR_RESET;
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaracion de variables
    const int MAX = 20;     // Tamaño máximo para mejor visualización
    int matriz1[50][50];    // Primera matriz
    int matriz2[50][50];    // Segunda matriz (copia)
    int filas, columnas;
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa crea una matriz con números aleatorios,\n";
    cout << "               copia el contenido a otra matriz y muestra ambas matrices.\n\n";
    
    // Pedir dimensiones de la matriz con validación
    do {
        cout << COLOR_HIGHLIGHT << "📏 Ingrese el número de filas (1-" << MAX << "): " << COLOR_INPUT;
        cin >> filas;
        cout << COLOR_RESET;
        
        if(filas <= 0 || filas > MAX) {
            cout << "\n⚠️  Error: El número de filas debe estar entre 1 y " << MAX << ".\n\n";
        }
    } while(filas <= 0 || filas > MAX);
    
    cout << "\n"; // Salto de línea entre inputs
    
    do {
        cout << COLOR_HIGHLIGHT << "📏 Ingrese el número de columnas (1-" << MAX << "): " << COLOR_INPUT;
        cin >> columnas;
        cout << COLOR_RESET;
        
        if(columnas <= 0 || columnas > MAX) {
            cout << "\n⚠️  Error: El número de columnas debe estar entre 1 y " << MAX << ".\n\n";
        }
    } while(columnas <= 0 || columnas > MAX);
    
    // Inicializar la semilla para los números aleatorios
    srand(time(NULL));
    
    // Informar al usuario
    cout << "\n" << COLOR_HIGHLIGHT << "🎲 Generando matriz " << filas << "x" << columnas << " con números aleatorios..." << COLOR_RESET << endl;
    
    // Llenar la matriz con números aleatorios
    for(int i = 0; i < filas; i++) {
        for(int j = 0; j < columnas; j++) {
            matriz1[i][j] = rand() % 100; // Números aleatorios entre 0 y 99
        }
    }
    
    // Mostrar la matriz original
    mostrarMatriz(matriz1, filas, columnas, "📊 MATRIZ ORIGINAL:", COLOR_VALUE);
    
    // Mostrar animación de copia
    mostrarAnimacionCopia();
    
    // Copiar los datos a la segunda matriz
    for(int i = 0; i < filas; i++) {
        for(int j = 0; j < columnas; j++) {
            matriz2[i][j] = matriz1[i][j];
        }
    }
    
    // Mostrar la matriz copia
    mostrarMatriz(matriz2, filas, columnas, "📋 MATRIZ COPIA:", COLOR_COPY);
    
    // Añadir instrucciones finales
    cout << "\n" << COLOR_HIGHLIGHT << "✅ Proceso completado con éxito" << COLOR_RESET << "\n\n";
    cout << "Presione Enter para finalizar...";
    cin.ignore();
    cin.get();
    
    return 0;
} 
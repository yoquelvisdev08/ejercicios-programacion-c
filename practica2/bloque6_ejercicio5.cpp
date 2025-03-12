/*
 * �� MATRIZ TRANSPUESTA 🔄
 * ======================
 *
 * Bloque 6: Ejercicio 5
 * --------------------
 * Programa que lee una matriz de 3x3 y crea su matriz traspuesta.
 * La matriz traspuesta es aquella en la que la columna i era la fila i 
 * de la matriz original.
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
const string COLOR_ROW = "\033[1;35m";  // Magenta brillante
const string COLOR_COL = "\033[1;34m";  // Azul brillante
const string COLOR_VALUE = "\033[1;37m";  // Blanco brillante
const string COLOR_TRANS = "\033[1;31m";  // Rojo brillante

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
    cout << "║        MATRIZ TRANSPUESTA         ║\n";
    cout << "╚═══════════════════════════════════╝\n\n" << COLOR_RESET;
}

// Función para mostrar una matriz con formato mejorado
void mostrarMatriz(const int matriz[3][3], string titulo, string color) {
    cout << COLOR_HIGHLIGHT << "\n" << titulo << COLOR_RESET << endl;
    
    // Encabezado de columnas
    cout << "      ";
    for(int j = 0; j < 3; j++) {
        cout << COLOR_COL << setw(4) << "Col " << j << " " << COLOR_RESET;
    }
    cout << "\n";
    
    // Línea separadora
    cout << "      ";
    for(int j = 0; j < 3; j++) {
        cout << "--------";
    }
    cout << "\n";
    
    // Contenido de la matriz
    for(int i = 0; i < 3; i++) {
        // Índice de fila
        cout << COLOR_ROW << " Fila " << setw(1) << i << " |" << COLOR_RESET;
        
        // Valores de la fila
        for(int j = 0; j < 3; j++) {
            cout << color << setw(7) << matriz[i][j] << " " << COLOR_RESET;
        }
        cout << "\n";
        
        // Separador entre filas (excepto después de la última)
        if(i < 3 - 1) {
            cout << "       |";
            for(int j = 0; j < 3; j++) {
                cout << "--------";
            }
            cout << "\n";
        }
    }
}

// Función para mostrar una animación del proceso de transposición
void mostrarAnimacionTransposicion() {
    cout << "\n" << COLOR_TRANS;
    cout << "        ↙ ↙ ↙ ↙ ↙ ↖ ↖ ↖ ↖ ↖\n";
    cout << "    ┌───────────────────────────┐\n";
    cout << "    │  TRANSPONIENDO MATRIZ...  │\n";
    cout << "    └───────────────────────────┘\n";
    cout << "        ↘ ↘ ↘ ↘ ↘ ↗ ↗ ↗ ↗ ↗\n" << COLOR_RESET;
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaracion de variables
    int matriz[3][3];       // Matriz original
    int transpuesta[3][3];  // Matriz transpuesta
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa crea una matriz 3x3 y genera su transpuesta,\n";
    cout << "               donde las filas se convierten en columnas y viceversa.\n\n";
    
    // Pedir datos para la matriz
    cout << COLOR_HIGHLIGHT << "🔢 INGRESO DE DATOS DE LA MATRIZ (3x3):\n";
    cout << "===================================\n" << COLOR_RESET;
    
    for(int i = 0; i < 3; i++) {
        cout << "\n" << COLOR_ROW << "📌 Fila [" << i << "]:" << COLOR_RESET << "\n";
        
        for(int j = 0; j < 3; j++) {
            cout << COLOR_HIGHLIGHT << "   Elemento [" << i << "][" << j << "]: " << COLOR_INPUT;
            cin >> matriz[i][j];
            cout << COLOR_RESET;
        }
    }
    
    // Mostrar la matriz original
    mostrarMatriz(matriz, "📊 MATRIZ ORIGINAL:", COLOR_VALUE);
    
    // Mostrar animación de transposición
    mostrarAnimacionTransposicion();
    
    // Crear la matriz transpuesta
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            transpuesta[j][i] = matriz[i][j];
        }
    }
    
    // Mostrar la matriz transpuesta
    mostrarMatriz(transpuesta, "🔄 MATRIZ TRANSPUESTA:", COLOR_TRANS);
    
    // Explicación visual de la transposición
    cout << "\n" << COLOR_HIGHLIGHT << "📝 EXPLICACIÓN:" << COLOR_RESET << endl;
    cout << "El elemento [i][j] de la matriz original se convierte en\n";
    cout << "el elemento [j][i] de la matriz transpuesta.\n";
    cout << "Por ejemplo: matriz[0][2] = " << matriz[0][2] << " → transpuesta[2][0] = " << transpuesta[2][0] << "\n";
    
    // Añadir instrucciones finales
    cout << "\n" << COLOR_HIGHLIGHT << "✅ Transposición completada con éxito" << COLOR_RESET << "\n\n";
    cout << "Presione Enter para finalizar...";
    cin.ignore();
    cin.get();
    
    return 0;
} 
/*
 * 📊 MATRIZ PERSONALIZADA 📊
 * =======================
 *
 * Bloque 6: Ejercicio 1
 * --------------------
 * Programa para rellenar una matriz pidiendo al usuario el número de filas 
 * y columnas. Posteriormente muestra la matriz en pantalla.
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
    cout << "║        MATRIZ PERSONALIZADA       ║\n";
    cout << "╚═══════════════════════════════════╝\n\n" << COLOR_RESET;
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaracion de variables
    const int MAX = 20;    // Tamaño máximo reducido para mejor visualización
    int matriz[MAX][MAX];  // Matriz de tamaño máximo 20x20
    int filas, columnas;   // Dimensiones reales
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa crea una matriz con el tamaño\n";
    cout << "               que especifique el usuario y la muestra en pantalla.\n\n";
    
    // Solicitar dimensiones de la matriz con validación
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
    
    cout << "\n"; // Espacio adicional antes de ingresar datos
    
    // Rellenar la matriz
    cout << COLOR_HIGHLIGHT << "🔢 INGRESO DE DATOS DE LA MATRIZ (" << filas << "x" << columnas << "):\n";
    cout << "=========================================\n" << COLOR_RESET;
    
    for(int i = 0; i < filas; i++) {
        cout << "\n" << COLOR_ROW << "📌 Fila [" << i << "]:" << COLOR_RESET << "\n";
        
        for(int j = 0; j < columnas; j++) {
            cout << COLOR_HIGHLIGHT << "   Elemento [" << i << "][" << j << "]: " << COLOR_INPUT;
            cin >> matriz[i][j];
            cout << COLOR_RESET;
        }
    }
    
    // Mostrar la matriz con formato mejorado
    cout << "\n" << COLOR_TITLE << "📊 MATRIZ RESULTANTE (" << filas << "x" << columnas << "):\n";
    cout << "===========================\n\n" << COLOR_RESET;
    
    // Crear el encabezado de columnas con mejor formato
    cout << "      ";
    for(int j = 0; j < columnas; j++) {
        cout << COLOR_COL << setw(4) << "Col " << j << " " << COLOR_RESET;
    }
    cout << "\n";
    
    // Línea separadora mejorada
    cout << "      ";
    for(int j = 0; j < columnas; j++) {
        cout << "--------";
    }
    cout << "\n";
    
    // Mostrar los datos con índices de fila con mejor formato
    for(int i = 0; i < filas; i++) {
        cout << COLOR_ROW << " Fila " << setw(1) << i << " |" << COLOR_RESET;
        for(int j = 0; j < columnas; j++) {
            // Cambiar el color según si es un valor en la diagonal, para destacarla
            if (i == j) {
                cout << COLOR_HIGHLIGHT;
            } else {
                cout << COLOR_VALUE;
            }
            cout << setw(7) << matriz[i][j] << " " << COLOR_RESET;
        }
        cout << "\n";
        
        // Agregar una línea horizontal después de cada fila para mejorar la legibilidad
        if (i < filas - 1) {
            cout << "       |";
            for(int j = 0; j < columnas; j++) {
                cout << "--------";
            }
            cout << "\n";
        }
    }
    
    cout << "\n" << COLOR_HIGHLIGHT << "✅ Matriz creada y mostrada con éxito." << COLOR_RESET << "\n\n";
    
    // Añadir instrucciones finales
    cout << "Presione Enter para finalizar...";
    cin.ignore();
    cin.get();
    
    return 0;
} 
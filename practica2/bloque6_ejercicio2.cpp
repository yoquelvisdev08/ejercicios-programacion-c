/*
 * 📊 DIAGONAL PRINCIPAL DE MATRIZ 📊
 * ===============================
 *
 * Bloque 6: Ejercicio 2
 * --------------------
 * Programa que define una matriz de 3x3 y muestra la diagonal principal.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <iomanip>
using namespace std;

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
    cout << "\n";
    cout << "╔═════════════════════════════════════╗\n";
    cout << "║     DIAGONAL PRINCIPAL DE MATRIZ    ║\n";
    cout << "╚═════════════════════════════════════╝\n\n";
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaracion de variables
    const int FILAS = 3;
    const int COLUMNAS = 3;
    int matriz[FILAS][COLUMNAS];
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa crea una matriz de 3x3 y\n";
    cout << "               muestra su diagonal principal.\n\n";
    
    // Solicitar los elementos de la matriz
    cout << "🔢 INGRESO DE DATOS DE LA MATRIZ (3x3):\n";
    cout << "===================================\n";
    
    for(int i = 0; i < FILAS; i++) {
        for(int j = 0; j < COLUMNAS; j++) {
            cout << "   Elemento [" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
        }
    }
    
    // Mostrar la matriz completa con formato mejorado
    cout << "\n📊 MATRIZ COMPLETA:\n";
    cout << "================\n\n";
    
    // Mostrar encabezados de columnas
    cout << "    ";
    for(int j = 0; j < COLUMNAS; j++) {
        cout << setw(5) << j << " ";
    }
    cout << "\n    ";
    
    // Línea separadora
    for(int j = 0; j < COLUMNAS; j++) {
        cout << "------";
    }
    cout << "\n";
    
    // Mostrar filas con índices
    for(int i = 0; i < FILAS; i++) {
        cout << setw(2) << i << " |";
        for(int j = 0; j < COLUMNAS; j++) {
            cout << setw(5) << matriz[i][j] << " ";
        }
        cout << "\n";
    }
    
    // Mostrar la diagonal principal con formato visual
    cout << "\n🎯 DIAGONAL PRINCIPAL:\n";
    cout << "===================\n\n";
    
    for(int i = 0; i < FILAS; i++) {
        // Espacios en blanco antes del número (para visualizar la diagonal)
        for(int espacio = 0; espacio < i; espacio++) {
            cout << "     ";
        }
        cout << "[" << matriz[i][i] << "]\n";
    }
    
    // Mostrar solo los elementos de la diagonal en forma de vector
    cout << "\n📊 Elementos de la diagonal: [ ";
    for(int i = 0; i < FILAS; i++) {
        cout << matriz[i][i];
        if(i < FILAS - 1) cout << ", ";
    }
    cout << " ]\n\n";
    
    return 0;
} 
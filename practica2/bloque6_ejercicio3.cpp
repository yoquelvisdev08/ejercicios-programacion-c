/*
 * 📋 COPIADO DE MATRIZ 📋
 * ====================
 *
 * Bloque 6: Ejercicio 3
 * --------------------
 * Programa que crea una matriz entera de 2x2, la llena de números
 * y luego copia todo su contenido hacia otra matriz.
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
    cout << "╔══════════════════════════════════╗\n";
    cout << "║         COPIADO DE MATRIZ        ║\n";
    cout << "╚══════════════════════════════════╝\n\n";
}

// Función para mostrar una matriz con formato
void mostrarMatriz(int matriz[2][2], string titulo) {
    cout << titulo << ":\n";
    cout << string(titulo.length()+1, '=') << "\n\n";
    
    cout << "    0     1\n";
    cout << "  +-----------+\n";
    
    for(int i = 0; i < 2; i++) {
        cout << i << " | ";
        for(int j = 0; j < 2; j++) {
            cout << setw(4) << matriz[i][j] << "  ";
        }
        cout << "|\n";
    }
    
    cout << "  +-----------+\n\n";
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaracion de variables
    int matriz1[2][2]; // Matriz original
    int matriz2[2][2]; // Matriz donde se copiará
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa crea una matriz de 2x2,\n";
    cout << "               la llena con valores y copia su contenido a otra matriz.\n\n";
    
    // Solicitar los elementos de la matriz
    cout << "🔢 INGRESO DE DATOS DE LA MATRIZ ORIGEN (2x2):\n";
    cout << "=========================================\n";
    
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cout << "   Elemento [" << i << "][" << j << "]: ";
            cin >> matriz1[i][j];
        }
    }
    
    // Mostrar matriz original
    cout << "\n";
    mostrarMatriz(matriz1, "📊 MATRIZ ORIGINAL");
    
    // Copiar el contenido a la otra matriz
    cout << "🔄 Copiando matriz...\n\n";
    
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            matriz2[i][j] = matriz1[i][j];
        }
    }
    
    // Mostrar la matriz copiada
    mostrarMatriz(matriz2, "📋 MATRIZ COPIADA");
    
    // Mensaje de éxito
    cout << "✅ Matriz copiada con éxito!\n\n";
    
    return 0;
} 
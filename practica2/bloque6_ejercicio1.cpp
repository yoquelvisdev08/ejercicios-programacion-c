/*
 * Bloque 6: Ejercicio 1
 * Programa para rellenar una matriz pidiendo al usuario el número de filas y columnas,
 * y posteriormente mostrar la matriz en pantalla.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
using namespace std;

int main() {
    // Declaracion de variables
    int matriz[50][50]; // Matriz de tamaño máximo 50x50
    int filas, columnas;
    int i, j; // Variables para ciclos
    
    // Pedir dimensiones de la matriz
    cout << "Digite el numero de filas: ";
    cin >> filas;
    
    cout << "Digite el numero de columnas: ";
    cin >> columnas;
    
    // Rellenar la matriz
    cout << "\nRellenando la matriz:\n";
    for(i = 0; i < filas; i++) {
        for(j = 0; j < columnas; j++) {
            cout << "Digite un numero [" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
        }
    }
    
    // Mostrar la matriz
    cout << "\nLa matriz es:\n";
    for(i = 0; i < filas; i++) {
        for(j = 0; j < columnas; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl; // Salto de línea para cada fila
    }
    
    return 0;
} 
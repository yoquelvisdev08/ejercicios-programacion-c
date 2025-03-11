/*
 * Bloque 6: Ejercicio 2
 * Programa que define una matriz de 3x3 y escribe un ciclo para que 
 * muestre la diagonal principal de la matriz.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
using namespace std;

int main() {
    // Declaracion de variables
    int matriz[3][3]; // Matriz de 3x3
    int i, j; // Variables para ciclos
    
    // Rellenar la matriz
    cout << "Digite los elementos de la matriz 3x3:\n";
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            cout << "Digite el elemento [" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
        }
    }
    
    // Mostrar la matriz completa
    cout << "\nLa matriz completa es:\n";
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    
    // Mostrar la diagonal principal
    cout << "\nLa diagonal principal es:\n";
    for(i = 0; i < 3; i++) {
        cout << matriz[i][i] << " ";
    }
    cout << endl;
    
    return 0;
} 
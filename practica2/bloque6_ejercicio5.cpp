/*
 * Bloque 6: Ejercicio 5
 * Programa que lee una matriz de 3x3 y crea su matriz traspuesta.
 * La matriz traspuesta es aquella en la que la columna i era la fila i 
 * de la matriz original.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
using namespace std;

int main() {
    // Declaracion de variables
    int matriz[3][3]; // Matriz original
    int transpuesta[3][3]; // Matriz transpuesta
    int i, j; // Variables para ciclos
    
    // Pedir datos para la matriz
    cout << "Digite los elementos de la matriz 3x3:\n";
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            cout << "Digite el elemento [" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
        }
    }
    
    // Crear la matriz transpuesta
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            transpuesta[j][i] = matriz[i][j];
        }
    }
    
    // Mostrar la matriz original
    cout << "\nMatriz Original:\n";
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    
    // Mostrar la matriz transpuesta
    cout << "\nMatriz Transpuesta:\n";
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            cout << transpuesta[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
} 
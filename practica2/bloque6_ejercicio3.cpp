/*
 * Bloque 6: Ejercicio 3
 * Programa que crea una matriz de tipo entera de 2x2, la llena de números 
 * y luego copia todo su contenido hacia otra matriz.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
using namespace std;

int main() {
    // Declaracion de variables
    int matriz1[2][2]; // Primera matriz
    int matriz2[2][2]; // Segunda matriz (copia)
    int i, j; // Variables para ciclos
    
    // Llenar la matriz original
    cout << "Digite los elementos de la matriz original:\n";
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            cout << "Digite un numero [" << i << "][" << j << "]: ";
            cin >> matriz1[i][j];
        }
    }
    
    // Copiar los datos a la segunda matriz
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            matriz2[i][j] = matriz1[i][j];
        }
    }
    
    // Mostrar la matriz original
    cout << "\nMatriz Original:\n";
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            cout << matriz1[i][j] << " ";
        }
        cout << endl;
    }
    
    // Mostrar la matriz copia
    cout << "\nMatriz Copia:\n";
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            cout << matriz2[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
} 
/*
 * Bloque 5: Ejercicio 3
 * Programa que lee de la entrada estándar un vector de números y 
 * muestra en la salida estándar los números del vector con sus índices asociados.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
using namespace std;

int main() {
    // Declaracion de variables
    int numeros[5]; // Vector para almacenar 5 numeros
    int i; // Variable para los ciclos
    
    // Pedir los numeros al usuario
    cout << "Digite 5 numeros: " << endl;
    
    for(i = 0; i < 5; i++) {
        cout << "Digite el numero " << i+1 << ": ";
        cin >> numeros[i]; // Guardamos cada numero en el vector
    }
    
    // Mostrar los numeros con sus indices
    cout << "\nLos numeros con sus indices son: " << endl;
    for(i = 0; i < 5; i++) {
        cout << "numeros[" << i << "] = " << numeros[i] << endl;
    }
    
    return 0;
} 
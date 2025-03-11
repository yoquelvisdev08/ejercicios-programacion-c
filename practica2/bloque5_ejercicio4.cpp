/*
 * Bloque 5: Ejercicio 4
 * Programa que define un vector de números y muestra en la salida estándar 
 * el vector en orden inverso—del último al primer elemento.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
using namespace std;

int main() {
    // Declaracion de variables
    int numeros[5] = {1, 2, 3, 4, 5}; // Vector con valores predefinidos
    int i; // Variable para el ciclo
    
    // Mostrar el vector original
    cout << "Vector original:" << endl;
    for(i = 0; i < 5; i++) {
        cout << numeros[i] << " ";
    }
    
    // Mostrar el vector en orden inverso
    cout << "\n\nVector en orden inverso:" << endl;
    for(i = 4; i >= 0; i--) {
        cout << numeros[i] << " ";
    }
    
    cout << endl;
    
    return 0;
} 
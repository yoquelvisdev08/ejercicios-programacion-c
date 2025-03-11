/*
 * Bloque 5: Ejercicio 1
 * Programa que define un vector de números y calcula la suma de sus elementos.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
using namespace std;

int main() {
    // Declaracion de variables
    int numeros[5]; // Vector de 5 numeros enteros
    int suma = 0;   // Variable para almacenar la suma
    int i;          // Variable para el ciclo for
    
    // Asignacion de valores al vector
    numeros[0] = 10;
    numeros[1] = 20;
    numeros[2] = 30;
    numeros[3] = 40;
    numeros[4] = 50;
    
    // Calcular la suma de los elementos del vector
    for(i = 0; i < 5; i++) {
        suma = suma + numeros[i]; // Acumulamos cada elemento en la variable suma
    }
    
    // Mostrar el resultado
    cout << "La suma de los elementos del vector es: " << suma << endl;
    
    return 0;
} 
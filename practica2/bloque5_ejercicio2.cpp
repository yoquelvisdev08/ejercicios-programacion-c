/*
 * Bloque 5: Ejercicio 2
 * Programa que define un vector de números y calcula la multiplicación acumulada 
 * de sus elementos.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
using namespace std;

int main() {
    // Declaracion de variables
    int numeros[5]; // Vector de 5 numeros enteros
    int multiplicacion = 1; // Variable para almacenar la multiplicacion, se inicia en 1
    int i; // Variable para el ciclo
    
    // Asignacion de valores al vector
    numeros[0] = 1;
    numeros[1] = 2;
    numeros[2] = 3;
    numeros[3] = 4;
    numeros[4] = 5;
    
    // Calcular la multiplicacion acumulada
    for(i = 0; i < 5; i++) {
        multiplicacion = multiplicacion * numeros[i]; // Multiplicamos cada elemento
    }
    
    // Mostrar el resultado
    cout << "La multiplicacion acumulada de los elementos es: " << multiplicacion << endl;
    
    return 0;
} 
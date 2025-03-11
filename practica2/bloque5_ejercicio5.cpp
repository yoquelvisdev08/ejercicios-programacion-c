/*
 * Bloque 5: Ejercicio 5
 * Programa que lee de la entrada estándar un vector de enteros y 
 * determina el mayor elemento del vector.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
using namespace std;

int main() {
    // Declaracion de variables
    int numeros[100]; // Vector grande para almacenar los numeros
    int n; // Cantidad de numeros que ingresará el usuario
    int mayor = 0; // Para almacenar el mayor elemento
    int i; // Variable para ciclos
    
    // Pedir cantidad de elementos
    cout << "Digite el numero de elementos: ";
    cin >> n;
    
    // Pedir los numeros
    for(i = 0; i < n; i++) {
        cout << "Digite un numero [" << i << "]: ";
        cin >> numeros[i];
        
        // Si el elemento actual es mayor que la variable 'mayor'
        if(numeros[i] > mayor) {
            mayor = numeros[i]; // Actualizamos el valor de mayor
        }
    }
    
    // Mostrar el mayor elemento
    cout << "\nEl mayor elemento del vector es: " << mayor << endl;
    
    return 0;
} 
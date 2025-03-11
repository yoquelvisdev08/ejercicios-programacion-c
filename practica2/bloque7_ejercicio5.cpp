/*
 * Bloque 7: Ejercicio 5
 * Programa que determina si una palabra es palíndroma.
 * Una palabra es palíndroma cuando se lee igual de izquierda a derecha y de derecha a izquierda.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h> // Para strlen()
using namespace std;

int main() {
    // Declaracion de variables
    char palabra[50]; // Para almacenar la palabra
    int longitud; // Para la longitud de la palabra
    bool esPalindromo = true; // Bandera para verificar si es palíndromo
    int i, j; // Variables para ciclos
    
    // Pedir la palabra al usuario
    cout << "Digite una palabra para determinar si es palindroma: ";
    cin.getline(palabra, 50, '\n');
    
    // Calcular la longitud de la palabra
    longitud = strlen(palabra);
    
    // Verificar si es palíndromo
    for(i = 0, j = longitud - 1; i < longitud/2; i++, j--) {
        if(palabra[i] != palabra[j]) {
            esPalindromo = false;
            break; // Si encuentra una diferencia, no es palíndromo
        }
    }
    
    // Mostrar el resultado
    if(esPalindromo) {
        cout << "\nLa palabra \"" << palabra << "\" SI es palindroma." << endl;
    } else {
        cout << "\nLa palabra \"" << palabra << "\" NO es palindroma." << endl;
    }
    
    return 0;
} 
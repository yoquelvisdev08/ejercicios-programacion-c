/*
 * Bloque 7: Ejercicio 3
 * Programa que pide al usuario que digite 2 cadenas de caracteres, e indica si ambas cadenas
 * son iguales, en caso de no serlo, indica cuál es mayor alfabéticamente.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h> // Para strcmp()
using namespace std;

int main() {
    // Declaracion de variables
    char cadena1[100]; // Primera cadena
    char cadena2[100]; // Segunda cadena
    int comparacion; // Para almacenar el resultado de la comparación
    
    // Pedir las cadenas al usuario
    cout << "Digite la primera cadena: ";
    cin.getline(cadena1, 100, '\n');
    
    cout << "Digite la segunda cadena: ";
    cin.getline(cadena2, 100, '\n');
    
    // Comparar las cadenas
    comparacion = strcmp(cadena1, cadena2);
    
    // Mostrar el resultado
    if(comparacion == 0) {
        cout << "\nLas cadenas son iguales." << endl;
    } else if(comparacion > 0) {
        cout << "\nLa primera cadena es mayor alfabeticamente." << endl;
    } else {
        cout << "\nLa segunda cadena es mayor alfabeticamente." << endl;
    }
    
    return 0;
} 
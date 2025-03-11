/*
 * Bloque 7: Ejercicio 1
 * Programa que pide al usuario una cadena de caracteres, verifica la longitud de la cadena,
 * y si ésta supera a 10 caracteres la muestra en pantalla, caso contrario no la muestra.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h> // Para strlen()
using namespace std;

int main() {
    // Declaracion de variables
    char cadena[100]; // Arreglo para almacenar la cadena
    int longitud; // Para almacenar la longitud de la cadena
    
    // Pedir la cadena al usuario
    cout << "Digite una cadena de caracteres: ";
    cin.getline(cadena, 100, '\n');
    
    // Calcular la longitud de la cadena
    longitud = strlen(cadena);
    
    // Verificar si la longitud supera 10 caracteres
    if(longitud > 10) {
        cout << "\nLa cadena tiene " << longitud << " caracteres y es: " << cadena << endl;
    } else {
        cout << "\nLa cadena tiene " << longitud << " caracteres, no se mostrara el contenido." << endl;
    }
    
    return 0;
} 
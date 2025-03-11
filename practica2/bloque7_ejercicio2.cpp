/*
 * Bloque 7: Ejercicio 2
 * Programa que pide al usuario una cadena de caracteres, la almacena en un arreglo
 * y copia todo su contenido hacia otro arreglo de caracteres.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h> // Para strcpy()
using namespace std;

int main() {
    // Declaracion de variables
    char cadena1[100]; // Arreglo original
    char cadena2[100]; // Arreglo de destino
    
    // Pedir la cadena al usuario
    cout << "Digite una cadena de caracteres: ";
    cin.getline(cadena1, 100, '\n');
    
    // Copiar el contenido de cadena1 a cadena2
    strcpy(cadena2, cadena1);
    
    // Mostrar ambas cadenas para verificar
    cout << "\nCadena Original: " << cadena1 << endl;
    cout << "Cadena Copiada: " << cadena2 << endl;
    
    return 0;
} 
/*
 * Bloque 7: Ejercicio 4
 * Programa que crea una cadena que tiene la frase "Hola que tal", luego crea otra cadena
 * para preguntarle al usuario su nombre, por ultimo añade el nombre al final de la primera
 * cadena y muestra el mensaje completo.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h> // Para strcat()
using namespace std;

int main() {
    // Declaracion de variables
    char mensaje[100] = "Hola que tal "; // Mensaje inicial
    char nombre[50]; // Para almacenar el nombre del usuario
    
    // Pedir el nombre al usuario
    cout << "Por favor, digite su nombre: ";
    cin.getline(nombre, 50, '\n');
    
    // Añadir el nombre al final del mensaje
    strcat(mensaje, nombre);
    
    // Mostrar el mensaje completo
    cout << "\nMensaje completo: " << mensaje << endl;
    
    return 0;
} 
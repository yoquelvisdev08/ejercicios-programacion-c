/*
 * Bloque 8: Ejercicio 8
 * Programa que define una estructura que sirve para representar a una persona. 
 * La estructura contiene dos campos: el nombre de la persona y un valor de tipo lógico
 * que indica si la persona tiene algún tipo de discapacidad. Dado un vector de personas
 * rellena dos nuevos vectores: uno que contiene las personas sin discapacidad y otro
 * con las personas con discapacidad.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h>
using namespace std;

// Definición de la estructura Persona
struct Persona {
    char nombre[50];
    bool discapacidad; // true si tiene discapacidad, false si no tiene
};

int main() {
    // Declaración de variables
    int n; // Número de personas
    Persona *personas; // Vector original de personas
    Persona *sin_discapacidad; // Vector para personas sin discapacidad
    Persona *con_discapacidad; // Vector para personas con discapacidad
    int contador_sin = 0; // Contador de personas sin discapacidad
    int contador_con = 0; // Contador de personas con discapacidad
    int i; // Variable para ciclos
    int opcion; // Para la selección de si tiene o no discapacidad
    
    // Pedir cantidad de personas
    cout << "Digite el numero de personas: ";
    cin >> n;
    
    // Crear los vectores dinámicos
    personas = new Persona[n];
    sin_discapacidad = new Persona[n]; // En el peor caso, todos sin discapacidad
    con_discapacidad = new Persona[n]; // En el peor caso, todos con discapacidad
    
    // Pedir datos para cada persona
    for(i = 0; i < n; i++) {
        cout << "\nPersona " << i+1 << ":" << endl;
        
        cin.ignore(); // Limpiar buffer
        cout << "Nombre: ";
        cin.getline(personas[i].nombre, 50, '\n');
        
        cout << "Tiene alguna discapacidad? (1=Si, 0=No): ";
        cin >> opcion;
        
        // Asignar el valor booleano según la opción
        if(opcion == 1) {
            personas[i].discapacidad = true;
        } else {
            personas[i].discapacidad = false;
        }
    }
    
    // Separar las personas en los dos vectores
    for(i = 0; i < n; i++) {
        if(personas[i].discapacidad) {
            // Persona con discapacidad
            strcpy(con_discapacidad[contador_con].nombre, personas[i].nombre);
            con_discapacidad[contador_con].discapacidad = true;
            contador_con++;
        } else {
            // Persona sin discapacidad
            strcpy(sin_discapacidad[contador_sin].nombre, personas[i].nombre);
            sin_discapacidad[contador_sin].discapacidad = false;
            contador_sin++;
        }
    }
    
    // Mostrar las personas sin discapacidad
    cout << "\n------ PERSONAS SIN DISCAPACIDAD ------" << endl;
    if(contador_sin > 0) {
        for(i = 0; i < contador_sin; i++) {
            cout << i+1 << ". " << sin_discapacidad[i].nombre << endl;
        }
    } else {
        cout << "No hay personas sin discapacidad." << endl;
    }
    
    // Mostrar las personas con discapacidad
    cout << "\n------ PERSONAS CON DISCAPACIDAD ------" << endl;
    if(contador_con > 0) {
        for(i = 0; i < contador_con; i++) {
            cout << i+1 << ". " << con_discapacidad[i].nombre << endl;
        }
    } else {
        cout << "No hay personas con discapacidad." << endl;
    }
    
    // Liberar memoria
    delete[] personas;
    delete[] sin_discapacidad;
    delete[] con_discapacidad;
    
    return 0;
}
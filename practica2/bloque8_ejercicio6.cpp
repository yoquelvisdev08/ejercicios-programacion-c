/*
 * Bloque 8: Ejercicio 6
 * Programa que utiliza las 2 estructuras del problema 5, pero ahora pide datos
 * para N alumnos, calcula cuál de todos tiene el mejor promedio, e imprime sus datos.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h>
using namespace std;

// Definición de la estructura Promedio
struct Promedio {
    float nota1;
    float nota2;
    float nota3;
    float promedio_final; // Para almacenar el promedio calculado
};

// Definición de la estructura Alumno con Promedio anidado
struct Alumno {
    char nombre[50];
    char sexo[10];
    int edad;
    Promedio calificaciones; // Estructura anidada
};

int main() {
    // Declaración de variables
    int n; // Cantidad de alumnos
    Alumno *alumnos; // Arreglo dinámico para almacenar los alumnos
    int pos_mejor = 0; // Posición del alumno con mejor promedio
    float mejor_promedio = 0; // Para almacenar el mejor promedio
    int i; // Variable para ciclos
    
    // Pedir cantidad de alumnos
    cout << "Digite el numero de alumnos: ";
    cin >> n;
    
    // Crear el arreglo dinámico para los alumnos
    alumnos = new Alumno[n];
    
    // Pedir datos para cada alumno
    for(i = 0; i < n; i++) {
        cout << "\nDigite los datos del alumno " << i+1 << ":" << endl;
        
        cin.ignore(); // Limpiar buffer
        cout << "Nombre: ";
        cin.getline(alumnos[i].nombre, 50, '\n');
        
        cout << "Sexo (Masculino/Femenino): ";
        cin.getline(alumnos[i].sexo, 10, '\n');
        
        cout << "Edad: ";
        cin >> alumnos[i].edad;
        
        // Pedir las notas
        cout << "\nDigite las calificaciones del alumno:" << endl;
        
        cout << "Nota 1: ";
        cin >> alumnos[i].calificaciones.nota1;
        
        cout << "Nota 2: ";
        cin >> alumnos[i].calificaciones.nota2;
        
        cout << "Nota 3: ";
        cin >> alumnos[i].calificaciones.nota3;
        
        // Calcular el promedio
        alumnos[i].calificaciones.promedio_final = (alumnos[i].calificaciones.nota1 +
                                                 alumnos[i].calificaciones.nota2 +
                                                 alumnos[i].calificaciones.nota3) / 3;
        
        // Verificar si este alumno tiene mejor promedio
        if(alumnos[i].calificaciones.promedio_final > mejor_promedio) {
            mejor_promedio = alumnos[i].calificaciones.promedio_final;
            pos_mejor = i;
        }
    }
    
    // Mostrar los datos del alumno con mejor promedio
    cout << "\n------ ALUMNO CON MEJOR PROMEDIO ------" << endl;
    cout << "Nombre: " << alumnos[pos_mejor].nombre << endl;
    cout << "Sexo: " << alumnos[pos_mejor].sexo << endl;
    cout << "Edad: " << alumnos[pos_mejor].edad << " anos" << endl;
    cout << "Notas: " << alumnos[pos_mejor].calificaciones.nota1 << ", "
                    << alumnos[pos_mejor].calificaciones.nota2 << ", "
                    << alumnos[pos_mejor].calificaciones.nota3 << endl;
    cout << "Mejor Promedio: " << alumnos[pos_mejor].calificaciones.promedio_final << endl;
    
    // Liberar memoria
    delete[] alumnos;
    
    return 0;
} 
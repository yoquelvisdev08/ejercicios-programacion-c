/*
 * Bloque 8: Ejercicio 5
 * Programa con 2 estructuras: una llamada promedio que tiene los campos nota1, nota2, nota3;
 * y otra llamada alumno que tiene los campos nombre, sexo, edad; hace que la estructura
 * promedio esté anidada en la estructura alumno, pide todos los datos para un alumno,
 * calcula su promedio, y por último imprime todos sus datos incluido el promedio.
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
    Alumno alumno1;
    
    // Pedir datos del alumno
    cout << "Digite los datos del alumno:" << endl;
    
    cout << "Nombre: ";
    cin.getline(alumno1.nombre, 50, '\n');
    
    cout << "Sexo (Masculino/Femenino): ";
    cin.getline(alumno1.sexo, 10, '\n');
    
    cout << "Edad: ";
    cin >> alumno1.edad;
    
    // Pedir las notas
    cout << "\nDigite las calificaciones del alumno:" << endl;
    
    cout << "Nota 1: ";
    cin >> alumno1.calificaciones.nota1;
    
    cout << "Nota 2: ";
    cin >> alumno1.calificaciones.nota2;
    
    cout << "Nota 3: ";
    cin >> alumno1.calificaciones.nota3;
    
    // Calcular el promedio
    alumno1.calificaciones.promedio_final = (alumno1.calificaciones.nota1 +
                                           alumno1.calificaciones.nota2 +
                                           alumno1.calificaciones.nota3) / 3;
    
    // Mostrar los datos del alumno
    cout << "\n------ DATOS DEL ALUMNO ------" << endl;
    cout << "Nombre: " << alumno1.nombre << endl;
    cout << "Sexo: " << alumno1.sexo << endl;
    cout << "Edad: " << alumno1.edad << " anos" << endl;
    cout << "Notas: " << alumno1.calificaciones.nota1 << ", "
                     << alumno1.calificaciones.nota2 << ", "
                     << alumno1.calificaciones.nota3 << endl;
    cout << "Promedio: " << alumno1.calificaciones.promedio_final << endl;
    
    return 0;
} 
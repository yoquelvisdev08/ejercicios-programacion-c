/*
 * Bloque 8: Ejercicio 4
 * Programa con un arreglo de estructura llamada atleta para N atletas que contiene los campos:
 * nombre, país, número de medallas. Y devuelve los datos (Nombre, país) del atleta
 * que ha ganado el mayor número de medallas.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h>
using namespace std;

// Definición de la estructura Atleta
struct Atleta {
    char nombre[50];
    char pais[30];
    int num_medallas;
};

int main() {
    // Declaración de variables
    int n; // Cantidad de atletas
    Atleta *atletas; // Arreglo dinámico para almacenar los atletas
    int pos_mayor = 0; // Posición del atleta con más medallas
    int mayor_medallas = 0; // Para almacenar el mayor número de medallas
    int i; // Variable para ciclos
    
    // Pedir cantidad de atletas
    cout << "Digite el numero de atletas: ";
    cin >> n;
    
    // Crear el arreglo dinámico para los atletas
    atletas = new Atleta[n];
    
    // Pedir datos de los atletas
    for(i = 0; i < n; i++) {
        cout << "\nDigite los datos del atleta " << i+1 << ":" << endl;
        
        cin.ignore(); // Limpiar buffer
        cout << "Nombre: ";
        cin.getline(atletas[i].nombre, 50, '\n');
        
        cout << "Pais: ";
        cin.getline(atletas[i].pais, 30, '\n');
        
        cout << "Numero de medallas: ";
        cin >> atletas[i].num_medallas;
        
        // Verificar si tiene más medallas
        if(atletas[i].num_medallas > mayor_medallas) {
            mayor_medallas = atletas[i].num_medallas;
            pos_mayor = i;
        }
    }
    
    // Mostrar los datos del atleta con más medallas
    cout << "\n------ ATLETA CON MAYOR NUMERO DE MEDALLAS ------" << endl;
    cout << "Nombre: " << atletas[pos_mayor].nombre << endl;
    cout << "Pais: " << atletas[pos_mayor].pais << endl;
    cout << "Numero de medallas: " << atletas[pos_mayor].num_medallas << endl;
    
    // Liberar memoria
    delete[] atletas;
    
    return 0;
} 
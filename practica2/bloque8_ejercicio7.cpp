/*
 * Bloque 8: Ejercicio 7
 * Programa que define una estructura que indica el tiempo empleado por un ciclista
 * en una etapa. La estructura tiene tres campos: horas, minutos y segundos.
 * Calcula el tiempo total empleado en correr todas las etapas.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
using namespace std;

// Definición de la estructura Tiempo
struct Tiempo {
    int horas;
    int minutos;
    int segundos;
};

int main() {
    // Declaración de variables
    int n; // Número de etapas
    Tiempo *etapas; // Arreglo dinámico para almacenar los tiempos por etapa
    Tiempo total = {0, 0, 0}; // Tiempo total inicializado en cero
    int i; // Variable para ciclos
    
    // Pedir cantidad de etapas
    cout << "Digite el numero de etapas: ";
    cin >> n;
    
    // Crear el arreglo dinámico para las etapas
    etapas = new Tiempo[n];
    
    // Pedir datos para cada etapa
    for(i = 0; i < n; i++) {
        cout << "\nEtapa " << i+1 << ":" << endl;
        
        cout << "Horas: ";
        cin >> etapas[i].horas;
        
        cout << "Minutos: ";
        cin >> etapas[i].minutos;
        
        cout << "Segundos: ";
        cin >> etapas[i].segundos;
    }
    
    // Calcular el tiempo total
    for(i = 0; i < n; i++) {
        total.horas += etapas[i].horas;
        total.minutos += etapas[i].minutos;
        total.segundos += etapas[i].segundos;
    }
    
    // Ajustar los minutos y segundos si son mayores o iguales a 60
    total.minutos += total.segundos / 60;
    total.segundos = total.segundos % 60;
    
    total.horas += total.minutos / 60;
    total.minutos = total.minutos % 60;
    
    // Mostrar el tiempo total
    cout << "\n------ TIEMPO TOTAL ------" << endl;
    cout << "Horas: " << total.horas << endl;
    cout << "Minutos: " << total.minutos << endl;
    cout << "Segundos: " << total.segundos << endl;
    cout << "Tiempo total: " << total.horas << "h " 
                           << total.minutos << "m " 
                           << total.segundos << "s" << endl;
    
    // Liberar memoria
    delete[] etapas;
    
    return 0;
} 
/*
 * Bloque 6: Ejercicio 4
 * Programa que crea una matriz preguntando al usuario el número de filas y columnas,
 * la llena de números aleatorios, copia el contenido a otra matriz y la muestra en pantalla.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime> // Para time()
using namespace std;

int main() {
    // Declaracion de variables
    int matriz1[50][50]; // Primera matriz
    int matriz2[50][50]; // Segunda matriz (copia)
    int filas, columnas;
    int i, j; // Variables para ciclos
    
    // Inicializar la semilla para los números aleatorios
    srand(time(NULL));
    
    // Pedir dimensiones de la matriz
    cout << "Digite el numero de filas: ";
    cin >> filas;
    
    cout << "Digite el numero de columnas: ";
    cin >> columnas;
    
    // Llenar la matriz con números aleatorios
    for(i = 0; i < filas; i++) {
        for(j = 0; j < columnas; j++) {
            matriz1[i][j] = rand() % 100; // Números aleatorios entre 0 y 99
        }
    }
    
    // Copiar los datos a la segunda matriz
    for(i = 0; i < filas; i++) {
        for(j = 0; j < columnas; j++) {
            matriz2[i][j] = matriz1[i][j];
        }
    }
    
    // Mostrar la matriz original
    cout << "\nMatriz Original (con numeros aleatorios):\n";
    for(i = 0; i < filas; i++) {
        for(j = 0; j < columnas; j++) {
            cout << matriz1[i][j] << "\t";
        }
        cout << endl;
    }
    
    // Mostrar la matriz copia
    cout << "\nMatriz Copia:\n";
    for(i = 0; i < filas; i++) {
        for(j = 0; j < columnas; j++) {
            cout << matriz2[i][j] << "\t";
        }
        cout << endl;
    }
    
    return 0;
} 
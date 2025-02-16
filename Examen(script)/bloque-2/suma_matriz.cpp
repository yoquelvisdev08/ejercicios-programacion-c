#include <iostream>
using namespace std;

// Función recursiva para sumar elementos de la matriz
int suma(int fila, int col, int orden, int mat[][100]) {
    if(fila == 0 && col == 0) {
        return mat[0][0];  // Caso base
    } else if(col < 0) {
        return suma(fila - 1, orden - 1, orden, mat);  // Nueva fila
    } else {
        return mat[fila][col] + suma(fila, col - 1, orden, mat);  // Suma en la misma fila
    }
}

int main() {
    int orden;
    int matriz[100][100];  // Matriz con tamaño máximo predefinido
    
    // Entrada del orden de la matriz
    do {
        cout << "Ingrese el orden de la matriz cuadrada (1-100): ";
        cin >> orden;
        
        if(orden <= 0 || orden > 100) {
            cout << "Error: El orden debe estar entre 1 y 100.\n";
        }
    } while(orden <= 0 || orden > 100);
    
    // Ingreso de elementos
    cout << "\nIngrese los elementos de la matriz " << orden << "x" << orden << ":\n";
    for(int i = 0; i < orden; i++) {
        for(int j = 0; j < orden; j++) {
            cout << "Elemento [" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
        }
    }
    
    // Cálculo de la suma
    int resultado = suma(orden-1, orden-1, orden, matriz);
    
    // Mostrar la matriz
    cout << "\nMatriz ingresada:\n";
    for(int i = 0; i < orden; i++) {
        for(int j = 0; j < orden; j++) {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
    
    // Mostrar resultado
    cout << "\nLa suma de todos los elementos es: " << resultado << endl;
    
    // Mostrar proceso de suma
    cout << "\nProceso de suma:\n";
    int suma_parcial = 0;
    for(int i = 0; i < orden; i++) {
        for(int j = 0; j < orden; j++) {
            suma_parcial += matriz[i][j];
            cout << "+" << matriz[i][j] << " = " << suma_parcial << endl;
        }
    }
    
    return 0;
} 
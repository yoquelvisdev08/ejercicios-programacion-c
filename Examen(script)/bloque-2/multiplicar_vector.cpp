#include <iostream>
using namespace std;

// Función recursiva para multiplicar elementos del vector
int multiplicar(int vec[], int tam) {
    if(tam == 0) {
        return vec[0];  // Caso base
    }
    return vec[tam] * multiplicar(vec, tam - 1);  // Fórmula Recursiva
}

int main() {
    int n;
    
    // Entrada del tamaño del vector
    do {
        cout << "Ingrese el tamaño del vector (> 0): ";
        cin >> n;
        
        if(n <= 0) {
            cout << "Error: El tamaño debe ser mayor que 0.\n";
        }
    } while(n <= 0);
    
    // Declaración dinámica del vector
    int* vector = new int[n];
    
    // Ingreso de elementos
    cout << "\nIngrese los elementos del vector:\n";
    for(int i = 0; i < n; i++) {
        cout << "Elemento " << i << ": ";
        cin >> vector[i];
    }
    
    // Cálculo de la multiplicación
    int resultado = multiplicar(vector, n-1);
    
    // Mostrar el proceso
    cout << "\nMultiplicación de elementos: ";
    for(int i = 0; i < n; i++) {
        cout << vector[i];
        if(i < n-1) cout << " × ";
    }
    cout << " = " << resultado << endl;
    
    // Mostrar proceso paso a paso
    cout << "\nProceso recursivo:\n";
    int temp = 1;
    for(int i = 0; i < n; i++) {
        temp *= vector[i];
        cout << "Paso " << (i+1) << ": ";
        for(int j = 0; j <= i; j++) {
            cout << vector[j];
            if(j < i) cout << " × ";
        }
        cout << " = " << temp << endl;
    }
    
    // Liberar memoria
    delete[] vector;
    
    return 0;
} 
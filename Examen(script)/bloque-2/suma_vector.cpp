#include <iostream>
using namespace std;

// Función recursiva para sumar elementos del vector
int suma_vec(int v[], int n) {
    if(n == 0) {
        return v[n];  // Caso base
    } else {
        return suma_vec(v, n - 1) + v[n];  // Fórmula Recursiva
    }
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
    
    // Cálculo de la suma
    int suma = suma_vec(vector, n-1);
    
    // Mostrar el proceso
    cout << "\nElementos del vector: ";
    for(int i = 0; i < n; i++) {
        cout << vector[i];
        if(i < n-1) cout << " + ";
    }
    cout << " = " << suma << endl;
    
    // Liberar memoria
    delete[] vector;
    
    return 0;
} 
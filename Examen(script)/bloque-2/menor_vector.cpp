#include <iostream>
using namespace std;

// Función recursiva para encontrar el menor elemento
int menorvec(int x[], int n, int menor) {
    if(n == 0) {
        if(menor > x[n]) {
            return x[0];
        } else {
            return menor;
        }
    } else {
        if(menor > x[n]) {
            return menorvec(x, n - 1, x[n]);
        } else {
            return menorvec(x, n - 1, menor);
        }
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
    
    // Encontrar el menor elemento
    int menor = menorvec(vector, n-1, vector[n-1]);
    
    // Mostrar el vector
    cout << "\nVector ingresado: ";
    for(int i = 0; i < n; i++) {
        cout << vector[i];
        if(i < n-1) cout << ", ";
    }
    cout << endl;
    
    // Mostrar resultado
    cout << "El menor elemento es: " << menor << endl;
    
    // Liberar memoria
    delete[] vector;
    
    return 0;
} 
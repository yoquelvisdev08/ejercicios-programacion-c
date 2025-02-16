#include <iostream>
using namespace std;

// Función recursiva para calcular Fibonacci
int fibonacci(int n) {
    if(n == 1 || n == 2) {
        return 1;  // Casos Base
    } else {
        return fibonacci(n-1) + fibonacci(n-2);  // Fórmula Recursiva
    }
}

int main() {
    int numero;
    
    // Entrada de datos con validación
    do {
        cout << "Ingrese la posición del número Fibonacci a calcular (>= 1): ";
        cin >> numero;
        
        if(numero < 1) {
            cout << "Error: El número debe ser mayor o igual a 1.\n";
        }
    } while(numero < 1);
    
    // Cálculo y muestra del resultado
    cout << "\nEl número Fibonacci en la posición " << numero << " es: " << fibonacci(numero) << endl;
    
    // Mostrar la secuencia hasta el número pedido
    cout << "\nSecuencia Fibonacci hasta la posición " << numero << ":\n";
    for(int i = 1; i <= numero; i++) {
        cout << fibonacci(i);
        if(i < numero) cout << ", ";
    }
    cout << endl;
    
    return 0;
} 
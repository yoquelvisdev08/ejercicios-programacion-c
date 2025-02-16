#include <iostream>
using namespace std;

// Función recursiva para calcular el factorial
int factorial(int n) {
    if(n == 0) {
        return 1;  // Caso Base
    } else {
        return n * factorial(n-1);  // Fórmula Recursiva
    }
}

int main() {
    int numero;
    
    // Entrada de datos con validación
    do {
        cout << "Ingrese un número no negativo para calcular su factorial: ";
        cin >> numero;
        
        if(numero < 0) {
            cout << "Error: El número debe ser no negativo.\n";
        }
    } while(numero < 0);
    
    // Cálculo y muestra del resultado
    cout << "El factorial de " << numero << " es: " << factorial(numero) << endl;
    
    // Mostrar el proceso paso a paso
    cout << "\nProceso de cálculo:\n";
    cout << numero << "! = ";
    for(int i = numero; i > 0; i--) {
        cout << i;
        if(i > 1) cout << " × ";
    }
    if(numero == 0) cout << "1";
    cout << " = " << factorial(numero) << endl;
    
    return 0;
} 
#include <iostream>
using namespace std;

// Función recursiva para sumar los dígitos
int sumar_dig(int n) {
    if(n == 0) {
        return n;  // Caso base
    } else {
        return sumar_dig(n / 10) + (n % 10);  // Fórmula Recursiva
    }
}

int main() {
    int numero;
    
    // Entrada de datos con validación
    do {
        cout << "Ingrese un número positivo para sumar sus dígitos: ";
        cin >> numero;
        
        if(numero < 0) {
            cout << "Error: El número debe ser positivo.\n";
        }
    } while(numero < 0);
    
    // Cálculo y muestra del resultado
    int suma = sumar_dig(numero);
    
    cout << "\nNúmero ingresado: " << numero << endl;
    cout << "Suma de sus dígitos: " << suma << endl;
    
    // Mostrar el proceso paso a paso
    cout << "\nProceso de suma:\n";
    int temp = numero;
    cout << "Dígitos: ";
    bool primero = true;
    while(temp > 0) {
        if(!primero) cout << " + ";
        cout << temp % 10;
        temp /= 10;
        primero = false;
    }
    cout << " = " << suma << endl;
    
    return 0;
} 
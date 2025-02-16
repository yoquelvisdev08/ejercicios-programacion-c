#include <iostream>
using namespace std;

// Función recursiva para invertir un número
int invertir(int n) {
    if(n < 10) {
        return n;  // Caso base
    } else {
        return (n % 10) + invertir(n / 10) * 10;  // Fórmula Recursiva
    }
}

int main() {
    int numero;
    
    // Entrada de datos con validación
    do {
        cout << "Ingrese un número positivo para invertir: ";
        cin >> numero;
        
        if(numero < 0) {
            cout << "Error: El número debe ser positivo.\n";
        }
    } while(numero < 0);
    
    // Cálculo y muestra del resultado
    int resultado = invertir(numero);
    
    cout << "\nNúmero original: " << numero << endl;
    cout << "Número invertido: " << resultado << endl;
    
    // Mostrar el proceso paso a paso
    cout << "\nProceso de inversión:\n";
    int temp = numero;
    cout << "Dígitos extraídos: ";
    while(temp > 0) {
        cout << temp % 10;
        temp /= 10;
        if(temp > 0) cout << " <- ";
    }
    cout << endl;
    
    return 0;
} 
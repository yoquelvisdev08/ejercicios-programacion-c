#include <iostream>
using namespace std;

// Función recursiva para calcular el MCD (Algoritmo de Euclides)
int sacar_mcd(int a, int b) {
    if(b == 0) {
        return a;  // Caso base
    } else {
        return sacar_mcd(b, a % b);  // Fórmula Recursiva
    }
}

int main() {
    int num1, num2;
    
    // Entrada de datos
    cout << "Cálculo del Máximo Común Divisor (MCD)\n\n";
    cout << "Ingrese el primer número: ";
    cin >> num1;
    cout << "Ingrese el segundo número: ";
    cin >> num2;
    
    // Validación de números positivos
    if(num1 <= 0 || num2 <= 0) {
        cout << "Error: Los números deben ser positivos.\n";
        return 1;
    }
    
    // Cálculo del MCD
    int mcd = sacar_mcd(num1, num2);
    
    // Mostrar el proceso paso a paso
    cout << "\nProceso de cálculo del MCD:\n";
    int a = num1, b = num2;
    while(b != 0) {
        cout << a << " = " << (a/b) << " × " << b << " + " << (a%b) << endl;
        int temp = b;
        b = a % b;
        a = temp;
    }
    
    cout << "\nEl MCD de " << num1 << " y " << num2 << " es: " << mcd << endl;
    
    return 0;
} 
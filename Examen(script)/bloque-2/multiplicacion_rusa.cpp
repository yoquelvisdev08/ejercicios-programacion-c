#include <iostream>
using namespace std;

// Función recursiva para multiplicación rusa
int mult_rusa(int A, int B) {
    if(A == 1) {
        return B;  // Caso base
    }
    if(A % 2 != 0) {
        return (B + mult_rusa(A/2, B*2));  // Si A es impar
    } else {
        return mult_rusa(A/2, B*2);  // Si A es par
    }
}

int main() {
    int A, B;
    
    // Entrada de datos
    cout << "Multiplicación usando el método Ruso\n";
    cout << "Ingrese el primer número (A): ";
    cin >> A;
    cout << "Ingrese el segundo número (B): ";
    cin >> B;
    
    // Validación de números positivos
    if(A <= 0 || B <= 0) {
        cout << "Error: Los números deben ser positivos.\n";
        return 1;
    }
    
    // Cálculo y resultado
    int resultado = mult_rusa(A, B);
    
    // Mostrar el proceso paso a paso
    cout << "\nProceso de multiplicación rusa:\n";
    cout << "A\tB\tSuma Parcial\n";
    
    int tempA = A;
    int tempB = B;
    int suma = 0;
    
    while(tempA >= 1) {
        cout << tempA << "\t" << tempB << "\t";
        if(tempA % 2 != 0) {
            suma += tempB;
            cout << suma;
        } else {
            cout << "-";
        }
        cout << endl;
        
        tempA /= 2;
        tempB *= 2;
    }
    
    cout << "\nResultado final: " << A << " × " << B << " = " << resultado << endl;
    
    return 0;
} 
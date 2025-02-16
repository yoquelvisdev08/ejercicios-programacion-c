#include <iostream>
using namespace std;

// Función recursiva para división por restas
int division(int a, int b) {
    if(b > a) {
        return 0;  // Caso Base
    } else {
        return division(a-b, b) + 1;  // Fórmula Recursiva
    }
}

int main() {
    int dividendo, divisor;
    
    // Entrada de datos con validación
    cout << "Ingrese el dividendo: ";
    cin >> dividendo;
    
    do {
        cout << "Ingrese el divisor (debe ser positivo): ";
        cin >> divisor;
        
        if(divisor <= 0) {
            cout << "Error: El divisor debe ser mayor que 0.\n";
        }
    } while(divisor <= 0);
    
    // Cálculo y muestra del resultado
    int cociente = division(dividendo, divisor);
    int residuo = dividendo - (cociente * divisor);
    
    cout << "\nResultado de la división por restas:\n";
    cout << dividendo << " ÷ " << divisor << " = " << cociente << endl;
    cout << "Residuo = " << residuo << endl;
    
    // Mostrar el proceso de restas
    cout << "\nProceso de división por restas:\n";
    int temp = dividendo;
    for(int i = 0; i < cociente; i++) {
        cout << temp << " - " << divisor << " = " << (temp - divisor) << endl;
        temp -= divisor;
    }
    
    return 0;
} 
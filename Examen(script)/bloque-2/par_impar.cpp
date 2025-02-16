#include <iostream>
using namespace std;

// Declaración adelantada de la función impar
bool impar(int n);

// Función recursiva para verificar si es par
bool par(int n) {
    if(n == 0) {
        return true;  // Caso base: 0 es par
    } else {
        return impar(n-1);  // Llamada cruzada
    }
}

// Función recursiva para verificar si es impar
bool impar(int n) {
    if(n == 0) {
        return false;  // Caso base: 0 no es impar
    } else {
        return par(n-1);  // Llamada cruzada
    }
}

int main() {
    int numero;
    
    // Entrada de datos
    cout << "Verificación de número par/impar usando recursividad cruzada\n\n";
    cout << "Ingrese un número no negativo: ";
    cin >> numero;
    
    // Validación de número no negativo
    if(numero < 0) {
        cout << "Error: El número debe ser no negativo.\n";
        return 1;
    }
    
    // Verificación y resultado
    bool es_par = par(numero);
    cout << "\nEl número " << numero << " es " << (es_par ? "PAR" : "IMPAR") << endl;
    
    // Mostrar proceso
    cout << "\nProceso de verificación:\n";
    cout << "Número inicial: " << numero << endl;
    for(int i = numero; i >= 0; i--) {
        cout << i << " -> " << (par(i) ? "par" : "impar") << endl;
    }
    
    return 0;
} 
#include <iostream>
using namespace std;

// Función recursiva para verificar si es positivo
bool positivo(int n) {
    if(n < 0) return true;
    else return negativo(n);
}

// Función recursiva para verificar si es negativo
bool negativo(int n) {
    if(n > 0) return false;
    else return positivo(n);
}

int main() {
    int numero;
    
    // Entrada de datos
    cout << "Verificación de número positivo/negativo\n\n";
    cout << "Ingrese un número (diferente de 0): ";
    cin >> numero;
    
    // Validación de número no cero
    if(numero == 0) {
        cout << "Error: El número no puede ser cero.\n";
        return 1;
    }
    
    // Verificación del signo
    bool es_positivo = positivo(numero);
    
    // Mostrar resultado
    cout << "\nEl número " << numero << " es ";
    if(es_positivo) {
        cout << "POSITIVO" << endl;
    } else {
        cout << "NEGATIVO" << endl;
    }
    
    // Mostrar proceso de verificación
    cout << "\nProceso de verificación:\n";
    int temp = numero;
    cout << "Número inicial: " << temp << endl;
    cout << "Resultado de verificación: " << (es_positivo ? "Positivo" : "Negativo") << endl;
    
    return 0;
} 
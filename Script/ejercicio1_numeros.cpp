#include <iostream>
using namespace std;

int main() {
    // Declaración del arreglo para almacenar 20 números
    double numeros[20];
    
    // 1. Ingreso de datos
    cout << "Por favor ingrese 20 números reales:\n";
    for(int i = 0; i < 20; i++) {
        cout << "Número " << (i+1) << ": ";
        cin >> numeros[i];
    }
    
    // 2. Ordenamiento burbuja optimizado (de mayor a menor)
    bool hubo_cambio;
    for(int i = 0; i < 19; i++) {
        hubo_cambio = false;
        // En cada pasada, el número más pequeño "burbujea" hacia el final
        for(int j = 0; j < 19-i; j++) {
            // Comparamos elementos adyacentes
            if(numeros[j] < numeros[j+1]) {
                // Intercambio usando variable temporal
                double temp = numeros[j];
                numeros[j] = numeros[j+1];
                numeros[j+1] = temp;
                hubo_cambio = true;
            }
        }
        // Si no hubo cambios en esta pasada, el arreglo ya está ordenado
        if(!hubo_cambio) break;
    }
    
    // 3. Mostrar resultados
    cout << "\nNúmeros ordenados de forma decreciente:\n";
    for(int i = 0; i < 20; i++) {
        cout << numeros[i];
        if(i < 19) cout << ", ";
    }
    cout << endl;
    
    return 0;
} 
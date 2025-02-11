#include <iostream>
using namespace std;

int main() {
    int numero;
    
    cout << "--- Ciclo Do-While ---\n";
    do {
        cout << "Ingrese un número positivo (0 para salir): ";
        cin >> numero;
        
        if(numero > 0) {
            cout << "Ingresaste: " << numero << endl;
        }
    } while(numero != 0);
    
    return 0;
} 
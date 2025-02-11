#include <iostream>
using namespace std;

int main() {
    int contador = 1;
    int limite;
    
    cout << "Ingrese hasta qué número contar: ";
    cin >> limite;
    
    cout << "\n--- Ciclo While ---\n";
    while(contador <= limite) {
        cout << "Número: " << contador << endl;
        contador++;
    }
    
    return 0;
} 
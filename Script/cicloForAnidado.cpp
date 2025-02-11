#include <iostream>
using namespace std;

int main() {
    int filas;
    
    cout << "Ingrese el número de filas para el triángulo: ";
    cin >> filas;
    
    cout << "\n--- Ciclos For Anidados ---\n";
    for(int i = 1; i <= filas; i++) {
        for(int j = 1; j <= i; j++) {
            cout << "* ";
        }
        cout << endl;
    }
    
    return 0;
} 
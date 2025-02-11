#include <iostream>
using namespace std;

int main() {
    int tabla;
    
    cout << "Ingrese qué tabla de multiplicar desea ver: ";
    cin >> tabla;
    
    cout << "\n--- Ciclo For ---\n";
    for(int i = 1; i <= 10; i++) {
        cout << tabla << " x " << i << " = " << (tabla * i) << endl;
    }
    
    return 0;
} 
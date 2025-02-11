#include <iostream>
using namespace std;

int main() {
    int numero;
    
    cout << "Ingrese un numero: ";
    cin >> numero;
    
    if (numero % 2 == 0) {
        cout << "El numero " << numero << " es par" << endl;
    } else {
        cout << "El numero " << numero << " es impar" << endl;
    }
    
    return 0;
}

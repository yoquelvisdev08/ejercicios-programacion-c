#include <iostream>
using namespace std;

int main() {
    int suma = 0;
    
    cout << "Sumando los multiplos de 3 hasta 50:" << endl;
    
    for(int i = 1; i <= 50; i++) {
        if(i % 3 == 0) {  // Verifica si el número es múltiplo de 3
            suma += i;     // Suma el número si es múltiplo de 3
            cout << i << " + ";
        }
    }
    
    cout << "\nLa suma total es: " << suma << endl;
    
    return 0;
}

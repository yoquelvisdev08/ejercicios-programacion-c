#include <iostream>
#include <array>
using namespace std;

int main() {
    array<int, 5> numeros = {1, 2, 3, 4, 5};
    
    cout << "--- Ciclo For-Each ---\n";
    cout << "Elementos del array: ";
    for(const int& num : numeros) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
} 
#include <iostream>
using namespace std;

// Declaración anticipada de la función sumaIterativa
int x(int);

int main(){
    int n, result;
    // Solicita al usuario ingresar un número
    cout << "Ingrese un numero: ";
    cin >> n;
    // Llama a la función iterativa y guarda el resultado
    result = x(n);
    // Muestra el resultado
    cout << "El resultado es: " << result << endl;
    return 0;
}

// Función iterativa que suma todos los números desde n hasta 0
int x(int n){
    int suma = 0;
    while(n > 0){
        suma += n;
        n--;
    }
    return suma;
} 
#include <iostream>
using namespace std;

// Declaración anticipada de la función x
int x(int);

int main(){
    int n,result;
    // Solicita al usuario ingresar un número
    cout << "Ingrese un numero: ";
    cin >> n;
    // Llama a la función recursiva y guarda el resultado
    result = x(n);
    // Muestra el resultado
    cout << "El resultado es: " << result << endl;
    return 0;
}

// Función recursiva que suma todos los números desde n hasta 0
int x(int n){
    // Caso base: cuando n llega a 0 o es negativo
    if(n>0)
        return n + x(n-1);  // Caso recursivo: suma n + la suma de todos los números menores
    else
        return 0;  // Retorna 0 cuando llega al caso base
}
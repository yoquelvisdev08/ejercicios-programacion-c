#include <iostream>
using namespace std;

// Declaración anticipada de la función fibonacci
int fibonacci(int n);

int main(){
    int numero;
    
    // Solicitar el número de término al usuario
    cout << "Ingrese que termino de la secuencia Fibonacci desea calcular: ";
    cin >> numero;
    
    // Validar que el número sea positivo
    if(numero < 0){
        cout << "Por favor ingrese un numero positivo" << endl;
        return 1;
    }
    
    // Calcular y mostrar el resultado
    cout << "El termino " << numero << " de la secuencia Fibonacci es: " 
         << fibonacci(numero) << endl;
    
    // Mostrar la secuencia hasta ese término
    cout << "\nLa secuencia hasta ese termino es: " << endl;
    for(int i = 0; i <= numero; i++){
        cout << fibonacci(i) << " ";
    }
    cout << endl;
    
    return 0;
}

// Función recursiva para calcular Fibonacci
int fibonacci(int n){
    // Casos base
    if(n == 0) 
        return 0;
    if(n == 1) 
        return 1;
    
    // Caso recursivo: Fn = Fn-1 + Fn-2
    return fibonacci(n-1) + fibonacci(n-2);
} 
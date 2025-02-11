#include <iostream>
using namespace std;

// Declaración anticipada de la función potencia
int potencia(int base, int exponente);

int main(){
    int base, exponente, resultado;
    
    // Solicitar datos al usuario
    cout << "Ingrese el numero base: ";
    cin >> base;
    cout << "Ingrese el exponente: ";
    cin >> exponente;
    
    // Calcular la potencia usando recursividad
    resultado = potencia(base, exponente);
    
    // Mostrar el resultado
    cout << base << " elevado a " << exponente << " es: " << resultado << endl;
    
    return 0;
}

// Función recursiva para calcular la potencia
int potencia(int base, int exponente){
    // Caso base: cualquier número elevado a 0 es 1
    if(exponente == 0)
        return 1;
    // Caso base: cualquier número elevado a 1 es el mismo número
    if(exponente == 1)
        return base;
    // Caso recursivo: multiplicamos la base por sí misma (exponente-1) veces
    return base * potencia(base, exponente - 1);
} 
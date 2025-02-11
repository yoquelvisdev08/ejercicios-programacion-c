#include <iostream>
#include <string>
#include <stack>
#include <array>
using namespace std;

int main() {
    // Inicialización del array como pila
    const int MAX_SIZE = 10;
    array<string, MAX_SIZE> arr_pila;
    stack<string> pila;
    
    // Mostrar estado inicial
    cout << "Estado inicial de las estructuras:" << endl;
    cout << "Pila y Array vacíos" << endl;
    cout << "Tamaño inicial de la pila: " << pila.size() << endl;

    // Agregar elementos a ambas estructuras
    string paises[] = {"Mexico", "Colombia", "Argentina", "Chile", "Peru"};
    
    // Llenar stack
    for(const auto& pais : paises) {
        pila.push(pais);
        cout << "Agregado a pila: " << pais << endl;
    }

    // Llenar array
    for(int i = 0; i < 5; i++) {
        arr_pila[i] = paises[i];
    }

    // Mostrar elementos de la pila
    cout << "\nElementos en la pila:" << endl;
    stack<string> pila_temp = pila;  // Crear copia para no modificar la original
    while(!pila_temp.empty()) {
        cout << pila_temp.top() << endl;
        pila_temp.pop();
    }
    cout << "Tamaño actual de la pila: " << pila.size() << endl;

    // Mostrar elementos del array
    cout << "\nElementos en el array:" << endl;
    for(int i = 0; i < 5; i++) {
        cout << arr_pila[i] << endl;
    }

    // Eliminar elementos de la pila
    cout << "\nEliminando elementos de la pila:" << endl;
    cout << "Eliminando: " << pila.top() << endl;
    pila.pop();
    cout << "Eliminando: " << pila.top() << endl;
    pila.pop();

    // Mostrar estado final de la pila
    cout << "\nEstado final de la pila:" << endl;
    pila_temp = pila;
    while(!pila_temp.empty()) {
        cout << pila_temp.top() << endl;
        pila_temp.pop();
    }
    cout << "Tamaño final de la pila: " << pila.size() << endl;

    return 0;
}
#include <iostream>
using namespace std;

// Estructura para la lista enlazada
struct Nodo {
    int dato;
    Nodo* siguiente;
    
    Nodo(int valor) : dato(valor), siguiente(nullptr) {}
};

// Función para sumar elementos usando lista enlazada
int sumarLista(Nodo* cabeza) {
    int suma = 0;
    Nodo* actual = cabeza;
    
    while(actual != nullptr) {
        suma += actual->dato;
        actual = actual->siguiente;
    }
    return suma;
}

// Función para sumar elementos usando arreglo
int sumarArreglo(int arr[], int n) {
    int suma = 0;
    for(int i = 0; i < n; i++) {
        suma += arr[i];
    }
    return suma;
}

int main() {
    int n;
    
    // Entrada del tamaño
    do {
        cout << "Ingrese la cantidad de elementos: ";
        cin >> n;
        if(n <= 0) cout << "Error: Debe ser un número positivo.\n";
    } while(n <= 0);
    
    // Crear arreglo y lista
    int* arreglo = new int[n];
    Nodo* cabeza = nullptr;
    Nodo* ultimo = nullptr;
    
    // Ingreso de datos
    cout << "\nIngrese los " << n << " elementos:\n";
    for(int i = 0; i < n; i++) {
        int valor;
        cout << "Elemento " << (i+1) << ": ";
        cin >> valor;
        
        // Guardar en arreglo
        arreglo[i] = valor;
        
        // Guardar en lista
        Nodo* nuevo = new Nodo(valor);
        if(cabeza == nullptr) {
            cabeza = nuevo;
            ultimo = nuevo;
        } else {
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
    }
    
    // Calcular sumas
    int sumaArr = sumarArreglo(arreglo, n);
    int sumaList = sumarLista(cabeza);
    
    // Mostrar resultados
    cout << "\nResultados usando arreglo:\n";
    cout << "Elementos: ";
    for(int i = 0; i < n; i++) {
        cout << arreglo[i];
        if(i < n-1) cout << " + ";
    }
    cout << " = " << sumaArr << endl;
    
    cout << "\nResultados usando lista:\n";
    cout << "Elementos: ";
    Nodo* actual = cabeza;
    while(actual != nullptr) {
        cout << actual->dato;
        if(actual->siguiente != nullptr) cout << " + ";
        actual = actual->siguiente;
    }
    cout << " = " << sumaList << endl;
    
    // Liberar memoria
    delete[] arreglo;
    while(cabeza != nullptr) {
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
    
    return 0;
} 
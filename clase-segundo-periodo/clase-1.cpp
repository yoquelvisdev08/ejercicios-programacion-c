#include <iostream>
using namespace std;

// Función de búsqueda lineal - O(n)
int busquedaLineal(int arr[], int n, int key) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == key) {
            return i; // Retorna la posición si encuentra el elemento
        }
    }
    return -1; // Retorna -1 si no encuentra el elemento
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};  // Arreglo del 1 al 5
    int key = 4;                   // Elemento a buscar
    int n = 5;                     // Tamaño del arreglo

    int resultado = busquedaLineal(arr, n, key);

    if(resultado != -1) {
        cout << "Elemento " << key << " encontrado en la posicion " << resultado << endl;
    } else {
        cout << "Elemento " << key << " no encontrado" << endl;
    }

    return 0;
}
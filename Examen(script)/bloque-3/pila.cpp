#include <iostream>
using namespace std;

// Implementación usando arreglo
class PilaArreglo {
private:
    int* arr;
    int tope;
    int capacidad;
    
public:
    PilaArreglo(int tam) {
        capacidad = tam;
        arr = new int[capacidad];
        tope = -1;
    }
    
    ~PilaArreglo() {
        delete[] arr;
    }
    
    void push(int valor) {
        if(tope < capacidad - 1) {
            arr[++tope] = valor;
        } else {
            cout << "Pila llena\n";
        }
    }
    
    int pop() {
        if(tope >= 0) {
            return arr[tope--];
        }
        cout << "Pila vacía\n";
        return -1;
    }
    
    void mostrar() {
        cout << "Pila (arreglo): ";
        for(int i = tope; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// Estructura para lista enlazada
struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo(int valor) : dato(valor), siguiente(nullptr) {}
};

// Implementación usando lista enlazada
class PilaLista {
private:
    Nodo* tope;
    
public:
    PilaLista() : tope(nullptr) {}
    
    ~PilaLista() {
        while(tope != nullptr) {
            Nodo* temp = tope;
            tope = tope->siguiente;
            delete temp;
        }
    }
    
    void push(int valor) {
        Nodo* nuevo = new Nodo(valor);
        nuevo->siguiente = tope;
        tope = nuevo;
    }
    
    int pop() {
        if(tope != nullptr) {
            int valor = tope->dato;
            Nodo* temp = tope;
            tope = tope->siguiente;
            delete temp;
            return valor;
        }
        cout << "Pila vacía\n";
        return -1;
    }
    
    void mostrar() {
        cout << "Pila (lista): ";
        Nodo* actual = tope;
        while(actual != nullptr) {
            cout << actual->dato << " ";
            actual = actual->siguiente;
        }
        cout << endl;
    }
};

int main() {
    int n;
    cout << "Ingrese el tamaño de las pilas: ";
    cin >> n;
    
    PilaArreglo pilaArr(n);
    PilaLista pilaList;
    
    cout << "\nOperaciones disponibles:\n";
    cout << "1. Push\n";
    cout << "2. Pop\n";
    cout << "3. Mostrar\n";
    cout << "4. Salir\n";
    
    int opcion;
    do {
        cout << "\nIngrese operación: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
                int valor;
                cout << "Valor a insertar: ";
                cin >> valor;
                pilaArr.push(valor);
                pilaList.push(valor);
                break;
            }
            case 2: {
                cout << "Valor removido (arreglo): " << pilaArr.pop() << endl;
                cout << "Valor removido (lista): " << pilaList.pop() << endl;
                break;
            }
            case 3: {
                pilaArr.mostrar();
                pilaList.mostrar();
                break;
            }
        }
    } while(opcion != 4);
    
    return 0;
} 
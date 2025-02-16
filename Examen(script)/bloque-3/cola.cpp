#include <iostream>
using namespace std;

// Implementación usando arreglo
class ColaArreglo {
private:
    int* arr;
    int frente, final;
    int capacidad;
    
public:
    ColaArreglo(int tam) {
        capacidad = tam;
        arr = new int[capacidad];
        frente = final = -1;
    }
    
    ~ColaArreglo() {
        delete[] arr;
    }
    
    void encolar(int valor) {
        if(final < capacidad - 1) {
            if(frente == -1) frente = 0;
            arr[++final] = valor;
        } else {
            cout << "Cola llena\n";
        }
    }
    
    int desencolar() {
        if(frente >= 0 && frente <= final) {
            return arr[frente++];
        }
        cout << "Cola vacía\n";
        return -1;
    }
    
    void mostrar() {
        cout << "Cola (arreglo): ";
        for(int i = frente; i <= final; i++) {
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
class ColaLista {
private:
    Nodo *frente, *final;
    
public:
    ColaLista() : frente(nullptr), final(nullptr) {}
    
    ~ColaLista() {
        while(frente != nullptr) {
            Nodo* temp = frente;
            frente = frente->siguiente;
            delete temp;
        }
    }
    
    void encolar(int valor) {
        Nodo* nuevo = new Nodo(valor);
        if(final == nullptr) {
            frente = final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
    }
    
    int desencolar() {
        if(frente != nullptr) {
            int valor = frente->dato;
            Nodo* temp = frente;
            frente = frente->siguiente;
            if(frente == nullptr) final = nullptr;
            delete temp;
            return valor;
        }
        cout << "Cola vacía\n";
        return -1;
    }
    
    void mostrar() {
        cout << "Cola (lista): ";
        Nodo* actual = frente;
        while(actual != nullptr) {
            cout << actual->dato << " ";
            actual = actual->siguiente;
        }
        cout << endl;
    }
};

int main() {
    int n;
    cout << "Ingrese el tamaño de las colas: ";
    cin >> n;
    
    ColaArreglo colaArr(n);
    ColaLista colaList;
    
    cout << "\nOperaciones disponibles:\n";
    cout << "1. Encolar\n";
    cout << "2. Desencolar\n";
    cout << "3. Mostrar\n";
    cout << "4. Salir\n";
    
    int opcion;
    do {
        cout << "\nIngrese operación: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
                int valor;
                cout << "Valor a encolar: ";
                cin >> valor;
                colaArr.encolar(valor);
                colaList.encolar(valor);
                break;
            }
            case 2: {
                cout << "Valor desencolado (arreglo): " << colaArr.desencolar() << endl;
                cout << "Valor desencolado (lista): " << colaList.desencolar() << endl;
                break;
            }
            case 3: {
                colaArr.mostrar();
                colaList.mostrar();
                break;
            }
        }
    } while(opcion != 4);
    
    return 0;
} 
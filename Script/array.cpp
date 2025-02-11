#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    // Inicialización de la lista
    list<string> paises = {"Mexico", "Colombia", "Argentina", "Chile", "Peru"};
    
    // Mostrar lista original
    cout << "Lista original:" << endl;
    for(string pais : paises) {
        cout << pais << endl;
    }
    cout << "Tamaño inicial: " << paises.size() << endl;

    // Agregar países
    paises.push_front("Brasil");
    paises.push_front("China");
    paises.push_front("Japon");
    // agregar atras
    paises.push_back("Ecuador");
    paises.push_back("Roma");
    paises.push_back("Francia");

    cout << "Tamaño Incrementado: " << paises.size() << endl;

    // Eliminar países
    paises.pop_front();
    paises.pop_back();
       
        cout << "Tamaño Incrementado: " << paises.size() << endl;


    // Mostrar lista final
    cout << "\nLista final:" << endl;
    for(const string& pais : paises) {
        cout << pais << endl;
    }
    cout << "Tamaño final: " << paises.size() << endl;

    return 0;
}
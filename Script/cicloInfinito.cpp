#include <iostream>
using namespace std;

int main() { 
    int contador = 1;
    
    cout << "Iniciando ciclo infinito..." << endl;
    
    for(;;) {  // Ciclo for sin condiciones = ciclo infinito
        cout << "Iteracion #" << contador << endl;
        contador++;
        
        // Opcional: pequeña pausa para no saturar la consola
        for(int i = 0; i < 10000000; i++) { }
    }
    
    return 0;  // Esta línea nunca se ejecutará
} 
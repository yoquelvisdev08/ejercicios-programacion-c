#include <iostream>

int main() {
    int base = 2;
    int exponente = 3;
    int resultado = 1;
    
    // Multiplicamos 2 por sí mismo 3 veces
    for(int i = 0; i < exponente; i++) {
        resultado = resultado * base;
    }
    
    // Mostramos el resultado
    std::cout << "El resultado es: " << resultado << std::endl;
    
    return 0;
} 
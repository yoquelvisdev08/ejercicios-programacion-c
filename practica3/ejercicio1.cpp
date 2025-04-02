/**
 * @file ejercicio1.cpp
 * @brief Programa que determina el mayor de dos números usando un puntero a función
 * @author Yoquelvis Jorge abreu 
 */

#include <iostream>

/**
 * @brief Función que determina el mayor de dos números
 * @param a Primer número a comparar
 * @param b Segundo número a comparar
 * @return El mayor de los dos números
 */
int encontrarMayor(int a, int b) {
    // Operador ternario: evalúa si a > b, si es verdadero retorna a, de lo contrario retorna b
    // Es equivalente a:
    // if (a > b) {
    //    return a;
    // } else {
    //    return b;
    // }
    return (a > b) ? a : b;
}

int main() {
    // Declaración de variables
    int numero1, numero2, resultado;
    
    // Declaración del puntero a función
    // Este puntero apunta a una función que recibe dos enteros y retorna un entero
    int (*ptrFuncion)(int, int);
    
    // Asignación de la dirección de la función al puntero
    ptrFuncion = encontrarMayor;
    
    // Solicitar datos al usuario
    std::cout << "Programa para determinar el mayor de dos números\n";
    std::cout << "================================================\n\n";
    
    std::cout << "Ingrese el primer número: ";
    std::cin >> numero1;
    
    std::cout << "Ingrese el segundo número: ";
    std::cin >> numero2;
    
    // Llamada a la función a través del puntero
    resultado = ptrFuncion(numero1, numero2);
    
    // Mostrar resultado
    std::cout << "\nEl mayor entre " << numero1 << " y " << numero2 
              << " es: " << resultado << std::endl;
    
    return 0;
} 
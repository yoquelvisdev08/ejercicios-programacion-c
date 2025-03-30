#include <iostream>
#include <vector>

/**
 * @brief Suma todos los elementos de un vector
 * @param numeros Vector de enteros
 * @return La suma de todos los elementos
 */
int sumarVector(const std::vector<int>& numeros) {
    int suma = 0;
    for (int numero : numeros) {
        suma += numero;
    }
    return suma;
}

/**
 * @brief Función principal del programa
 * @return 0 si todo sale bien
 */
int main() {
    // Crear un vector con algunos números
    std::vector<int> numeros = {1, 2, 3, 4, 5, 10, 20, 30};
    
    // Sumar los elementos del vector
    int resultado = sumarVector(numeros);
    
    // Mostrar el resultado
    std::cout << "La suma de los elementos del vector es: " << resultado << std::endl;
    
    return 0;
} 
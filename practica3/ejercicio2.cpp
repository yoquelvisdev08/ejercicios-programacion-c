/**
 * @file ejercicio2.cpp
 * @brief Programa que suma, resta, multiplica y divide dos valores usando punteros a función
 * @author Yoquelvis Jorge Abreu
 */

#include <iostream>

/**
 * @brief Función para sumar dos números
 * @param a Primer número
 * @param b Segundo número
 * @return Resultado de la suma (a + b)
 */
double sumar(double a, double b) {
    return a + b;
}

/**
 * @brief Función para restar dos números
 * @param a Primer número
 * @param b Segundo número
 * @return Resultado de la resta (a - b)
 */
double restar(double a, double b) {
    return a - b;
}

/**
 * @brief Función para multiplicar dos números
 * @param a Primer número
 * @param b Segundo número
 * @return Resultado de la multiplicación (a * b)
 */
double multiplicar(double a, double b) {
    return a * b;
}

/**
 * @brief Función para dividir dos números
 * @param a Numerador
 * @param b Denominador
 * @return Resultado de la división (a / b)
 */
double dividir(double a, double b) {
    // Verificación de división por cero
    if (b == 0) {
        std::cout << "Error: No se puede dividir por cero." << std::endl;
        return 0;
    }
    return a / b;
}

/**
 * @brief Función para mostrar el resultado de una operación
 * @param a Primer operando
 * @param b Segundo operando
 * @param operacion Puntero a la función que realizará la operación
 * @param nombreOperacion Nombre de la operación para mostrar
 */
void mostrarResultado(double a, double b, double (*operacion)(double, double), const char* nombreOperacion) {
    double resultado = operacion(a, b);
    std::cout << "El resultado de la " << nombreOperacion << " es: " << resultado << std::endl;
}

int main() {
    // Declaración de variables
    double numero1, numero2;
    
    // Declaración de los punteros a función
    double (*ptrSuma)(double, double) = sumar;
    double (*ptrResta)(double, double) = restar;
    double (*ptrMultiplicacion)(double, double) = multiplicar;
    double (*ptrDivision)(double, double) = dividir;
    
    // Solicitar datos al usuario
    std::cout << "Programa para realizar operaciones aritméticas usando punteros a función\n";
    std::cout << "======================================================================\n\n";
    
    std::cout << "Ingrese el primer número: ";
    std::cin >> numero1;
    
    std::cout << "Ingrese el segundo número: ";
    std::cin >> numero2;
    
    // Realizar operaciones usando los punteros a función
    std::cout << "\nResultados de las operaciones:\n";
    std::cout << "-----------------------------\n";
    
    // Llamadas a través de la función mostrarResultado que utiliza punteros a función
    mostrarResultado(numero1, numero2, ptrSuma, "suma");
    mostrarResultado(numero1, numero2, ptrResta, "resta");
    mostrarResultado(numero1, numero2, ptrMultiplicacion, "multiplicación");
    mostrarResultado(numero1, numero2, ptrDivision, "división");
    
    // Mostrar ejemplos de uso directo de los punteros a función
    std::cout << "\nEjemplos adicionales (llamadas directas):\n";
    std::cout << "--------------------------------------\n";
    std::cout << "Suma directa: " << ptrSuma(numero1, numero2) << std::endl;
    std::cout << "Resta directa: " << ptrResta(numero1, numero2) << std::endl;
    
    return 0;
} 
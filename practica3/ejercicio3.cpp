/**
 * @file ejercicio3.cpp
 * @brief Programa que gestiona la memoria para un valor float y luego libera la memoria
 * @author Yoquelvis Jorge Abreu
 */

#include <iostream>
#include <cstdlib> // Necesario para malloc y free

int main() {
    // Declaración de variables
    float *ptrFloat = nullptr;
    float valor;
    
    std::cout << "Programa de gestión dinámica de memoria para un valor flotante\n";
    std::cout << "=============================================================\n\n";
    
    // 1. Asignación dinámica de memoria usando malloc
    // Reservamos memoria para un float (sizeof(float) bytes)
    ptrFloat = (float*)malloc(sizeof(float));
    
    // Verificamos si la asignación de memoria fue exitosa
    if (ptrFloat == nullptr) {
        std::cout << "Error: No se pudo asignar memoria." << std::endl;
        return 1; // Salir con código de error
    }
    
    std::cout << "Memoria asignada exitosamente en la dirección: " << ptrFloat << std::endl;
    
    // 2. Solicitamos al usuario un valor para almacenar en la memoria asignada
    std::cout << "Ingrese un valor decimal (float): ";
    std::cin >> valor;
    
    // 3. Asignamos el valor a la memoria reservada
    *ptrFloat = valor;
    
    // 4. Mostramos el valor almacenado y su dirección de memoria
    std::cout << "\nDatos almacenados en memoria dinámica:\n";
    std::cout << "---------------------------------------\n";
    std::cout << "Valor almacenado: " << *ptrFloat << std::endl;
    std::cout << "Dirección de memoria: " << ptrFloat << std::endl;
    
    // 5. Liberamos la memoria asignada
    std::cout << "\nLiberando memoria...\n";
    free(ptrFloat);
    std::cout << "Memoria liberada exitosamente.\n";
    
    // 6. Importante: establecemos el puntero a nullptr después de liberar
    // para evitar acceso a memoria liberada (dangling pointer)
    ptrFloat = nullptr;
    
    // 7. Demostración de que el puntero ya no apunta a un área válida de memoria
    std::cout << "\nDespués de liberar la memoria:\n";
    std::cout << "-----------------------------\n";
    std::cout << "Dirección del puntero: " << ptrFloat << std::endl;
    
    // No intentamos acceder a *ptrFloat aquí porque causaría un error
    // ya que la memoria ha sido liberada
    
    // Alternativa usando new y delete (más común en C++ moderno)
    std::cout << "\nAlternativa usando new/delete (estilo C++ moderno):\n";
    std::cout << "------------------------------------------------\n";
    
    // Asignación con new
    float *ptrFloatNew = new float;
    *ptrFloatNew = valor;
    
    std::cout << "Memoria asignada con new en: " << ptrFloatNew << std::endl;
    std::cout << "Valor almacenado: " << *ptrFloatNew << std::endl;
    
    // Liberación con delete
    delete ptrFloatNew;
    std::cout << "Memoria liberada con delete.\n";
    ptrFloatNew = nullptr;
    
    return 0;
} 
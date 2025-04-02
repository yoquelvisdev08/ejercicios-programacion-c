/**
 * @file ejercicio4.cpp
 * @brief Programa que gestiona dinámicamente un arreglo de tamaño definido por el usuario
 * @author Yoquelvis Jorge Abreu
 */

#include <iostream>
#include <limits>   // Para validar entrada de datos
#include <iomanip>  // Para formatear la salida

/**
 * @brief Función para limpiar el buffer de entrada
 * Esta función se utiliza después de detectar una entrada inválida
 */
void limpiarBuffer() {
    // Restablece el estado del flujo de entrada después de un error
    std::cin.clear();
    
    // Descarta todos los caracteres en el buffer hasta encontrar un salto de línea
    // numeric_limits<std::streamsize>::max() obtiene el valor máximo posible para representar el tamaño de un stream
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Función para validar que el tamaño del arreglo sea positivo
 * @param mensaje Mensaje a mostrar al usuario
 * @return Tamaño válido del arreglo
 */
int capturarTamanoValido(const char* mensaje) {
    int tamano;
    bool entradaValida = false;
    
    // Bucle do-while para garantizar la entrada de un valor válido
    // Continuará solicitando entrada hasta que se proporcione un valor válido
    do {
        std::cout << mensaje;
        std::cin >> tamano;
        
        // Verificar si la entrada es un número y es positivo
        // std::cin.fail() devuelve true si la última operación de entrada falló
        if (std::cin.fail() || tamano <= 0) {
            std::cout << "Error: Debe ingresar un número entero positivo." << std::endl;
            limpiarBuffer();
        } else {
            entradaValida = true;
        }
    } while (!entradaValida);
    
    return tamano;
}

int main() {
    // Declaración de variables
    int tamanoArreglo;
    int *arreglo = nullptr;  // Inicializar el puntero a nullptr (buena práctica)
    
    // Título del programa
    std::cout << "Programa de gestión dinámica de un arreglo de enteros\n";
    std::cout << "====================================================\n\n";
    
    // 1. Capturar el tamaño del arreglo
    tamanoArreglo = capturarTamanoValido("Ingrese el tamaño del arreglo: ");
    
    // 2. Asignación dinámica de memoria para el arreglo
    std::cout << "\nAsignando memoria para un arreglo de " << tamanoArreglo << " enteros...\n";
    
    // new int[tamanoArreglo] reserva un bloque contiguo de memoria para almacenar 'tamanoArreglo' enteros
    // Esta operación de asignación dinámica devuelve un puntero a la primera posición del bloque
    arreglo = new int[tamanoArreglo];  // Usamos new[] para arreglos
    
    // Verificar si la asignación de memoria fue exitosa
    // En C++ moderno, new lanza una excepción std::bad_alloc si falla, pero es buena práctica verificar
    if (arreglo == nullptr) {
        std::cout << "Error: No se pudo asignar memoria para el arreglo." << std::endl;
        return 1;  // Salir con código de error
    }
    
    std::cout << "Memoria asignada exitosamente en la dirección: " << arreglo << std::endl;
    
    // 3. Capturar los valores del arreglo usando el puntero
    std::cout << "\nCaptura de valores para el arreglo:\n";
    std::cout << "--------------------------------\n";
    
    for (int i = 0; i < tamanoArreglo; i++) {
        bool entradaValida = false;
        
        do {
            std::cout << "Ingrese el valor para la posición [" << i << "]: ";
            
            // *(arreglo + i) es aritmética de punteros:
            // 1. arreglo + i: Calcula la dirección de memoria del elemento i-ésimo
            //    (El compilador ajusta automáticamente el desplazamiento según el tamaño del tipo)
            // 2. *(arreglo + i): Desreferencia esa dirección para acceder al valor almacenado
            std::cin >> *(arreglo + i);  // Equivalente a arreglo[i]
            
            // Verificar si la entrada es un número
            if (std::cin.fail()) {
                std::cout << "Error: Debe ingresar un número entero." << std::endl;
                limpiarBuffer();
            } else {
                entradaValida = true;
            }
        } while (!entradaValida);
    }
    
    // 4. Mostrar los valores almacenados en el arreglo
    std::cout << "\nValores almacenados en el arreglo:\n";
    std::cout << "--------------------------------\n";
    
    // 4.1 Mostrar usando notación de arreglo
    // La notación arreglo[i] es azúcar sintáctico para *(arreglo + i)
    std::cout << "Usando notación de arreglo (arreglo[i]):\n";
    for (int i = 0; i < tamanoArreglo; i++) {
        std::cout << "arreglo[" << i << "] = " << arreglo[i] << std::endl;
    }
    
    // 4.2 Mostrar usando aritmética de punteros
    std::cout << "\nUsando aritmética de punteros (*(arreglo + i)):\n";
    for (int i = 0; i < tamanoArreglo; i++) {
        std::cout << "*(arreglo + " << i << ") = " << *(arreglo + i) << std::endl;
    }
    
    // 4.3 Mostrar usando un puntero auxiliar
    std::cout << "\nUsando un puntero auxiliar que recorre el arreglo:\n";
    
    // Creamos un puntero auxiliar que inicialmente apunta al mismo lugar que arreglo
    int *ptrAux = arreglo;  // Puntero auxiliar que apunta al inicio del arreglo
    
    for (int i = 0; i < tamanoArreglo; i++) {
        // *ptrAux accede al valor almacenado en la dirección actual donde apunta ptrAux
        std::cout << "*ptrAux = " << *ptrAux << " (Dirección: " << ptrAux << ")" << std::endl;
        
        // ptrAux++ incrementa la dirección a la que apunta ptrAux en sizeof(int) bytes
        // Es decir, avanza al siguiente elemento del arreglo
        ptrAux++;  // Avanzar el puntero a la siguiente posición
    }
    
    // 5. Calcular algunas estadísticas básicas
    if (tamanoArreglo > 0) {
        int suma = 0;
        int maximo = arreglo[0];
        int minimo = arreglo[0];
        
        for (int i = 0; i < tamanoArreglo; i++) {
            suma += arreglo[i];
            if (arreglo[i] > maximo) maximo = arreglo[i];
            if (arreglo[i] < minimo) minimo = arreglo[i];
        }
        
        // static_cast<double>(suma) realiza una conversión explícita (cast)
        // del entero 'suma' a tipo double para permitir una división decimal
        // Esto evita truncamientos en la división entera
        double promedio = static_cast<double>(suma) / tamanoArreglo;
        
        std::cout << "\nEstadísticas del arreglo:\n";
        std::cout << "------------------------\n";
        std::cout << "Suma: " << suma << std::endl;
        
        // std::fixed y std::setprecision(2) formatean la salida para mostrar
        // el promedio con 2 decimales fijos
        std::cout << "Promedio: " << std::fixed << std::setprecision(2) << promedio << std::endl;
        std::cout << "Valor máximo: " << maximo << std::endl;
        std::cout << "Valor mínimo: " << minimo << std::endl;
    }
    
    // 6. Liberar la memoria asignada
    std::cout << "\nLiberando memoria...\n";
    
    // delete[] es el operador que libera memoria asignada con new[]
    // Es crucial usar delete[] (no delete) para arreglos dinámicos
    // para asegurar que se llamen los destructores de todos los elementos
    delete[] arreglo;  // Importante: usamos delete[] para arreglos, no delete
    
    std::cout << "Memoria liberada exitosamente.\n";
    
    // 7. Establecer el puntero a nullptr después de liberar memoria
    // Esto previene los "dangling pointers" (punteros que apuntan a memoria ya liberada)
    // y facilita la identificación de posibles errores si intentamos usar el puntero accidentalmente
    arreglo = nullptr;
    
    return 0;
} 
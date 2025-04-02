/**
 * @file ejercicio5.cpp
 * @brief Programa que define una estructura estudiante y maneja un arreglo de estudiantes con punteros
 * @author Yoquelvis Jorge Abreu
 */

#include <iostream>
#include <limits>    // Para validar entrada de datos
#include <string>    // Para manejo de cadenas
#include <iomanip>   // Para formatear la salida

// Definición de la estructura Estudiante
struct Estudiante {
    std::string nombre;
    int edad;
    std::string matricula;
    std::string carrera;
};

/**
 * @brief Función para limpiar el buffer de entrada
 * Esta función se utiliza después de detectar una entrada inválida
 */
void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Función para capturar un entero con validación
 * @param mensaje Mensaje a mostrar al usuario
 * @param minimo Valor mínimo aceptable
 * @param maximo Valor máximo aceptable
 * @return Entero validado
 */
int capturarEntero(const char* mensaje, int minimo, int maximo) {
    int valor;
    bool entradaValida = false;
    
    do {
        std::cout << mensaje;
        std::cin >> valor;
        
        // Verificar si la entrada es un número y está en el rango esperado
        if (std::cin.fail() || valor < minimo || valor > maximo) {
            std::cout << "Error: Ingrese un número entre " << minimo << " y " << maximo << std::endl;
            limpiarBuffer();
        } else {
            entradaValida = true;
        }
    } while (!entradaValida);
    
    return valor;
}

/**
 * @brief Función para capturar los datos de un estudiante
 * @param estudiante Puntero a la estructura Estudiante donde se guardarán los datos
 * @param indice Índice del estudiante en el arreglo (para mostrar en pantalla)
 */
void capturarDatosEstudiante(Estudiante* estudiante, int indice) {
    std::cout << "\n--- Captura de datos del Estudiante #" << (indice + 1) << " ---\n";
    
    // Capturar nombre (limpiar buffer primero para evitar problemas con getline)
    limpiarBuffer();
    std::cout << "Nombre: ";
    std::getline(std::cin, estudiante->nombre);
    
    // Capturar edad con validación (entre 17 y 99 años)
    estudiante->edad = capturarEntero("Edad: ", 17, 99);
    
    // Capturar matrícula
    limpiarBuffer();
    std::cout << "Matrícula: ";
    std::getline(std::cin, estudiante->matricula);
    
    // Capturar carrera
    std::cout << "Carrera: ";
    std::getline(std::cin, estudiante->carrera);
}

/**
 * @brief Función para mostrar los datos de un estudiante
 * @param estudiante Puntero a la estructura Estudiante cuyos datos se mostrarán
 * @param indice Índice del estudiante en el arreglo (para mostrar en pantalla)
 */
void mostrarDatosEstudiante(const Estudiante* estudiante, int indice) {
    std::cout << "\n--- Información del Estudiante #" << (indice + 1) << " ---\n";
    std::cout << "Nombre: " << estudiante->nombre << std::endl;
    std::cout << "Edad: " << estudiante->edad << " años" << std::endl;
    std::cout << "Matrícula: " << estudiante->matricula << std::endl;
    std::cout << "Carrera: " << estudiante->carrera << std::endl;
}

/**
 * @brief Función para mostrar una tabla con todos los estudiantes
 * @param estudiantes Puntero al arreglo de estudiantes
 * @param cantidad Cantidad de estudiantes en el arreglo
 */
void mostrarTablaEstudiantes(const Estudiante* estudiantes, int cantidad) {
    // Imprimir encabezado de la tabla
    std::cout << "\n-------------------------- TABLA DE ESTUDIANTES --------------------------\n";
    std::cout << std::left << std::setw(5) << "No." 
              << std::setw(25) << "Nombre" 
              << std::setw(10) << "Edad" 
              << std::setw(15) << "Matrícula" 
              << "Carrera" << std::endl;
    std::cout << std::string(75, '-') << std::endl;
    
    // Imprimir datos de cada estudiante
    for (int i = 0; i < cantidad; i++) {
        std::cout << std::left << std::setw(5) << (i + 1)
                  << std::setw(25) << estudiantes[i].nombre
                  << std::setw(10) << estudiantes[i].edad
                  << std::setw(15) << estudiantes[i].matricula
                  << estudiantes[i].carrera << std::endl;
    }
    std::cout << std::string(75, '-') << std::endl;
}

/**
 * @brief Función para encontrar el estudiante de mayor edad
 * @param estudiantes Puntero al arreglo de estudiantes
 * @param cantidad Cantidad de estudiantes en el arreglo
 * @return Índice del estudiante con mayor edad
 */
int encontrarEstudianteMayorEdad(const Estudiante* estudiantes, int cantidad) {
    int indiceMayor = 0;
    
    for (int i = 1; i < cantidad; i++) {
        if (estudiantes[i].edad > estudiantes[indiceMayor].edad) {
            indiceMayor = i;
        }
    }
    
    return indiceMayor;
}

/**
 * @brief Función para encontrar el estudiante de menor edad
 * @param estudiantes Puntero al arreglo de estudiantes
 * @param cantidad Cantidad de estudiantes en el arreglo
 * @return Índice del estudiante con menor edad
 */
int encontrarEstudianteMenorEdad(const Estudiante* estudiantes, int cantidad) {
    int indiceMenor = 0;
    
    for (int i = 1; i < cantidad; i++) {
        if (estudiantes[i].edad < estudiantes[indiceMenor].edad) {
            indiceMenor = i;
        }
    }
    
    return indiceMenor;
}

int main() {
    // Constante para el número de estudiantes a capturar
    const int NUM_ESTUDIANTES = 5;
    
    // Declaración del puntero que apuntará al arreglo de estudiantes
    Estudiante* ptrEstudiantes = nullptr;
    
    // Asignación dinámica de memoria para el arreglo de estudiantes
    // ptrEstudiantes ahora apunta al primer elemento del arreglo
    ptrEstudiantes = new Estudiante[NUM_ESTUDIANTES];
    
    // Verificar si la asignación de memoria fue exitosa
    if (ptrEstudiantes == nullptr) {
        std::cout << "Error: No se pudo asignar memoria para el arreglo de estudiantes." << std::endl;
        return 1;  // Salir con código de error
    }
    
    // Título del programa
    std::cout << "Programa de gestión de estudiantes con estructuras y punteros\n";
    std::cout << "===========================================================\n\n";
    
    // Capturar los datos de los estudiantes usando el puntero
    // Usando aritmética de punteros explícita
    for (int i = 0; i < NUM_ESTUDIANTES; i++) {
        // ptrEstudiantes + i calcula la dirección del elemento i
        // *(ptrEstudiantes + i) accede al elemento en esa dirección
        capturarDatosEstudiante(ptrEstudiantes + i, i);
    }
    
    // Mostrar los datos almacenados de cada estudiante
    std::cout << "\n\nInformación de los estudiantes capturados:\n";
    for (int i = 0; i < NUM_ESTUDIANTES; i++) {
        // Usando aritmética de punteros explícita
        mostrarDatosEstudiante(ptrEstudiantes + i, i);
    }
    
    // Mostrar todos los estudiantes en formato de tabla
    mostrarTablaEstudiantes(ptrEstudiantes, NUM_ESTUDIANTES);
    
    // Encontrar y mostrar el estudiante de mayor edad
    int indiceMayor = encontrarEstudianteMayorEdad(ptrEstudiantes, NUM_ESTUDIANTES);
    std::cout << "\nEstudiante de mayor edad:\n";
    mostrarDatosEstudiante(ptrEstudiantes + indiceMayor, indiceMayor);
    
    // Encontrar y mostrar el estudiante de menor edad
    int indiceMenor = encontrarEstudianteMenorEdad(ptrEstudiantes, NUM_ESTUDIANTES);
    std::cout << "\nEstudiante de menor edad:\n";
    mostrarDatosEstudiante(ptrEstudiantes + indiceMenor, indiceMenor);
    
    // Liberar la memoria asignada
    std::cout << "\nLiberando memoria...\n";
    delete[] ptrEstudiantes;  // Usamos delete[] para liberar arreglos
    std::cout << "Memoria liberada exitosamente.\n";
    
    // Establecer el puntero a nullptr después de liberar
    ptrEstudiantes = nullptr;
    
    return 0;
} 
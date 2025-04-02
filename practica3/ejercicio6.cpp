/**
 * @file ejercicio6.cpp
 * @brief Programa que captura datos de empleados y los guarda/muestra desde un archivo
 * @author Yoquelvis Jorge Abreu
 */

#include <iostream>
#include <fstream>    // Para manejo de archivos
#include <string>     // Para manejo de cadenas
#include <limits>     // Para validar entrada de datos
#include <iomanip>    // Para formatear la salida
#include <vector>     // Para almacenar empleados de forma dinámica

// Definición de la estructura Empleado
struct Empleado {
    std::string nombre;
    std::string departamento;
    int edad;
    double salario;
    std::string posicion;
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
 * @brief Función para validar entradas numéricas enteras
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
 * @brief Función para validar entradas numéricas de punto flotante
 * @param mensaje Mensaje a mostrar al usuario
 * @param minimo Valor mínimo aceptable
 * @return Número de punto flotante validado
 */
double capturarDouble(const char* mensaje, double minimo) {
    double valor;
    bool entradaValida = false;
    
    do {
        std::cout << mensaje;
        std::cin >> valor;
        
        // Verificar si la entrada es un número y es mayor o igual al mínimo
        if (std::cin.fail() || valor < minimo) {
            std::cout << "Error: Ingrese un número válido mayor o igual a " << minimo << std::endl;
            limpiarBuffer();
        } else {
            entradaValida = true;
        }
    } while (!entradaValida);
    
    return valor;
}

/**
 * @brief Función para capturar los datos de un empleado
 * @param empleado Referencia a la estructura Empleado donde se guardarán los datos
 * @param indice Índice del empleado (para mostrar en pantalla)
 */
void capturarDatosEmpleado(Empleado& empleado, int indice) {
    std::cout << "\n--- Captura de datos del Empleado #" << (indice + 1) << " ---\n";
    
    // Capturar nombre (limpiar buffer primero para evitar problemas con getline)
    limpiarBuffer();
    std::cout << "Nombre: ";
    std::getline(std::cin, empleado.nombre);
    
    // Capturar departamento
    std::cout << "Departamento: ";
    std::getline(std::cin, empleado.departamento);
    
    // Capturar edad con validación (entre 18 y 70 años)
    empleado.edad = capturarEntero("Edad: ", 18, 70);
    
    // Capturar salario con validación (mayor o igual a 0)
    empleado.salario = capturarDouble("Salario: ", 0.0);
    
    // Capturar posición
    limpiarBuffer();
    std::cout << "Posición: ";
    std::getline(std::cin, empleado.posicion);
}

/**
 * @brief Función para mostrar los datos de un empleado
 * @param empleado Referencia constante a la estructura Empleado
 * @param indice Índice del empleado (para mostrar en pantalla)
 */
void mostrarDatosEmpleado(const Empleado& empleado, int indice) {
    std::cout << "\n--- Información del Empleado #" << (indice + 1) << " ---\n";
    std::cout << "Nombre: " << empleado.nombre << std::endl;
    std::cout << "Departamento: " << empleado.departamento << std::endl;
    std::cout << "Edad: " << empleado.edad << " años" << std::endl;
    std::cout << "Salario: $" << std::fixed << std::setprecision(2) << empleado.salario << std::endl;
    std::cout << "Posición: " << empleado.posicion << std::endl;
}

/**
 * @brief Función para guardar los datos de los empleados en un archivo
 * @param empleados Vector de empleados a guardar
 * @param nombreArchivo Nombre del archivo donde se guardarán los datos
 * @return true si la operación fue exitosa, false en caso contrario
 */
bool guardarEmpleadosEnArchivo(const std::vector<Empleado>& empleados, const std::string& nombreArchivo) {
    // Abrir el archivo en modo escritura
    std::ofstream archivo(nombreArchivo);
    
    // Verificar si el archivo se abrió correctamente
    if (!archivo) {
        std::cout << "Error: No se pudo abrir el archivo para escritura." << std::endl;
        return false;
    }
    
    // Escribir el número total de empleados
    archivo << empleados.size() << std::endl;
    
    // Escribir los datos de cada empleado
    for (size_t i = 0; i < empleados.size(); i++) {
        const Empleado& empleado = empleados[i];
        archivo << empleado.nombre << std::endl;
        archivo << empleado.departamento << std::endl;
        archivo << empleado.edad << std::endl;
        archivo << empleado.salario << std::endl;
        archivo << empleado.posicion << std::endl;
    }
    
    // Cerrar el archivo
    archivo.close();
    
    return true;
}

/**
 * @brief Función para cargar los datos de empleados desde un archivo
 * @param empleados Vector donde se cargarán los empleados
 * @param nombreArchivo Nombre del archivo de donde se leerán los datos
 * @return true si la operación fue exitosa, false en caso contrario
 */
bool cargarEmpleadosDesdeArchivo(std::vector<Empleado>& empleados, const std::string& nombreArchivo) {
    // Limpiar el vector antes de cargar los datos
    empleados.clear();
    
    // Abrir el archivo en modo lectura
    std::ifstream archivo(nombreArchivo);
    
    // Verificar si el archivo existe y se abrió correctamente
    if (!archivo) {
        std::cout << "Error: No se pudo abrir el archivo para lectura." << std::endl;
        return false;
    }
    
    // Leer el número total de empleados
    size_t numEmpleados;
    archivo >> numEmpleados;
    archivo.ignore(); // Ignorar el salto de línea después del número
    
    // Leer los datos de cada empleado
    for (size_t i = 0; i < numEmpleados; i++) {
        Empleado empleado;
        
        // Leer nombre
        std::getline(archivo, empleado.nombre);
        
        // Leer departamento
        std::getline(archivo, empleado.departamento);
        
        // Leer edad
        archivo >> empleado.edad;
        archivo.ignore(); // Ignorar el salto de línea
        
        // Leer salario
        archivo >> empleado.salario;
        archivo.ignore(); // Ignorar el salto de línea
        
        // Leer posición
        std::getline(archivo, empleado.posicion);
        
        // Agregar el empleado al vector
        empleados.push_back(empleado);
    }
    
    // Cerrar el archivo
    archivo.close();
    
    return true;
}

/**
 * @brief Función para mostrar una tabla con todos los empleados
 * @param empleados Vector de empleados a mostrar
 */
void mostrarTablaEmpleados(const std::vector<Empleado>& empleados) {
    // Imprimir encabezado de la tabla
    std::cout << "\n-------------------------- TABLA DE EMPLEADOS --------------------------\n";
    std::cout << std::left << std::setw(5) << "No." 
              << std::setw(20) << "Nombre" 
              << std::setw(15) << "Departamento" 
              << std::setw(8) << "Edad" 
              << std::setw(12) << "Salario" 
              << "Posición" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    // Imprimir datos de cada empleado
    for (size_t i = 0; i < empleados.size(); i++) {
        std::cout << std::left << std::setw(5) << (i + 1)
                  << std::setw(20) << empleados[i].nombre
                  << std::setw(15) << empleados[i].departamento
                  << std::setw(8) << empleados[i].edad
                  << "$" << std::right << std::setw(10) << std::fixed << std::setprecision(2) << empleados[i].salario
                  << "  " << std::left << empleados[i].posicion << std::endl;
    }
    std::cout << std::string(80, '-') << std::endl;
}

/**
 * @brief Función para calcular y mostrar estadísticas de los empleados
 * @param empleados Vector de empleados para calcular estadísticas
 */
void mostrarEstadisticas(const std::vector<Empleado>& empleados) {
    if (empleados.empty()) {
        std::cout << "No hay empleados para calcular estadísticas." << std::endl;
        return;
    }
    
    // Variables para estadísticas
    double salarioTotal = 0.0;
    double salarioMinimo = empleados[0].salario;
    double salarioMaximo = empleados[0].salario;
    int edadTotal = 0;
    int edadMinima = empleados[0].edad;
    int edadMaxima = empleados[0].edad;
    
    // Calcular estadísticas
    for (size_t i = 0; i < empleados.size(); i++) {
        const Empleado& empleado = empleados[i];
        salarioTotal += empleado.salario;
        edadTotal += empleado.edad;
        
        if (empleado.salario < salarioMinimo) salarioMinimo = empleado.salario;
        if (empleado.salario > salarioMaximo) salarioMaximo = empleado.salario;
        
        if (empleado.edad < edadMinima) edadMinima = empleado.edad;
        if (empleado.edad > edadMaxima) edadMaxima = empleado.edad;
    }
    
    // Calcular promedios
    double salarioPromedio = salarioTotal / empleados.size();
    double edadPromedio = static_cast<double>(edadTotal) / empleados.size();
    
    // Mostrar estadísticas
    std::cout << "\n----- ESTADÍSTICAS DE EMPLEADOS -----\n";
    std::cout << "Número total de empleados: " << empleados.size() << std::endl;
    std::cout << "Salario promedio: $" << std::fixed << std::setprecision(2) << salarioPromedio << std::endl;
    std::cout << "Salario mínimo: $" << std::fixed << std::setprecision(2) << salarioMinimo << std::endl;
    std::cout << "Salario máximo: $" << std::fixed << std::setprecision(2) << salarioMaximo << std::endl;
    std::cout << "Edad promedio: " << std::fixed << std::setprecision(1) << edadPromedio << " años" << std::endl;
    std::cout << "Edad mínima: " << edadMinima << " años" << std::endl;
    std::cout << "Edad máxima: " << edadMaxima << " años" << std::endl;
}

int main() {
    // Nombre del archivo donde se guardarán los datos
    const std::string NOMBRE_ARCHIVO = "empleados.dat";
    
    // Vector para almacenar los empleados
    std::vector<Empleado> empleados;
    
    // Variables para el menú
    int opcion;
    bool salir = false;
    
    // Título del programa
    std::cout << "Programa de gestión de empleados con archivos\n";
    std::cout << "============================================\n";
    
    // Menú principal
    while (!salir) {
        std::cout << "\nMENÚ PRINCIPAL\n";
        std::cout << "1. Capturar datos de empleados\n";
        std::cout << "2. Mostrar datos de empleados desde archivo\n";
        std::cout << "3. Mostrar estadísticas\n";
        std::cout << "4. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        
        if (std::cin.fail()) {
            std::cout << "Error: Ingrese un número válido.\n";
            limpiarBuffer();
            continue;
        }
        
        switch (opcion) {
            case 1: {
                // Capturar datos de empleados
                limpiarBuffer();
                int numEmpleados = capturarEntero("Ingrese la cantidad de empleados a registrar: ", 1, 100);
                
                // Limpiar el vector antes de capturar nuevos datos
                empleados.clear();
                
                // Capturar los datos de cada empleado
                for (int i = 0; i < numEmpleados; i++) {
                    Empleado nuevoEmpleado;
                    capturarDatosEmpleado(nuevoEmpleado, i);
                    empleados.push_back(nuevoEmpleado);
                }
                
                // Guardar los datos en el archivo
                if (guardarEmpleadosEnArchivo(empleados, NOMBRE_ARCHIVO)) {
                    std::cout << "\nLos datos se han guardado correctamente en el archivo '" << NOMBRE_ARCHIVO << "'.\n";
                }
                break;
            }
            case 2: {
                // Cargar los datos desde el archivo
                if (cargarEmpleadosDesdeArchivo(empleados, NOMBRE_ARCHIVO)) {
                    std::cout << "\nSe han cargado " << empleados.size() << " empleados desde el archivo.\n";
                    
                    // Mostrar los datos de los empleados
                    for (size_t i = 0; i < empleados.size(); i++) {
                        mostrarDatosEmpleado(empleados[i], static_cast<int>(i));
                    }
                    
                    // Mostrar tabla de empleados
                    mostrarTablaEmpleados(empleados);
                } else {
                    std::cout << "No se pudieron cargar los datos. Asegúrese de haber capturado empleados primero.\n";
                }
                break;
            }
            case 3: {
                // Mostrar estadísticas
                if (cargarEmpleadosDesdeArchivo(empleados, NOMBRE_ARCHIVO)) {
                    mostrarEstadisticas(empleados);
                } else {
                    std::cout << "No se pudieron cargar los datos para estadísticas.\n";
                }
                break;
            }
            case 4: {
                // Salir del programa
                std::cout << "Gracias por usar el programa. ¡Hasta pronto!\n";
                salir = true;
                break;
            }
            default: {
                std::cout << "Opción inválida. Por favor, seleccione una opción del menú.\n";
            }
        }
    }
    
    return 0;
} 
/*
 * 👥 CLASIFICADOR DE PERSONAS POR DISCAPACIDAD 👥
 * ============================================
 * 
 * Bloque 8: Ejercicio 8
 * --------------------
 * Programa que define una estructura que sirve para representar a una persona. 
 * La estructura contiene dos campos: el nombre de la persona y un valor de tipo lógico
 * que indica si la persona tiene algún tipo de discapacidad. Dado un vector de personas
 * rellena dos nuevos vectores: uno que contiene las personas sin discapacidad y otro
 * con las personas con discapacidad.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h>
#include <iomanip>
#include <limits>
using namespace std;

// Constantes para colores (ANSI escape codes)
const string COLOR_RESET = "\033[0m";
const string COLOR_TITLE = "\033[1;36m";  // Cyan brillante
const string COLOR_HIGHLIGHT = "\033[1;33m";  // Amarillo brillante
const string COLOR_INPUT = "\033[1;32m";  // Verde brillante
const string COLOR_INFO = "\033[1;34m";  // Azul brillante
const string COLOR_ERROR = "\033[1;31m";  // Rojo brillante
const string COLOR_SUCCESS = "\033[1;92m";  // Verde claro brillante
const string COLOR_WARNING = "\033[1;33m";  // Amarillo brillante
const string COLOR_WITH = "\033[1;35m";  // Magenta brillante
const string COLOR_WITHOUT = "\033[1;94m";  // Azul claro brillante

// Definición de la estructura Persona
struct Persona {
    char nombre[50];
    bool discapacidad; // true si tiene discapacidad, false si no tiene
};

// Función para limpiar la pantalla
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Función para mostrar el banner del programa
void mostrarBanner() {
    cout << COLOR_TITLE << "\n";
    cout << "╔═════════════════════════════════════════════════╗\n";
    cout << "║    CLASIFICADOR DE PERSONAS POR DISCAPACIDAD    ║\n";
    cout << "╚═════════════════════════════════════════════════╝\n\n" << COLOR_RESET;
}

// Función para mostrar una barra de progreso
void mostrarProgreso(int actual, int total) {
    cout << "\n📊 Progreso: [";
    int porcentaje = (actual * 20) / total;
    for(int i = 0; i < 20; i++) {
        if(i < porcentaje) {
            cout << COLOR_SUCCESS << "█" << COLOR_RESET;
        } else {
            cout << "░";
        }
    }
    cout << "] " << (actual * 100) / total << "%\n\n";
}

// Función para mostrar una lista de personas con formato
void mostrarListaPersonas(const Persona* personas, int cantidad, const char* titulo, string color) {
    cout << COLOR_HIGHLIGHT << "\n📋 " << titulo << " (" << cantidad << ")\n";
    cout << "========================================\n" << COLOR_RESET;
    
    if(cantidad > 0) {
        cout << color << "┌────┬─────────────────────────────────────┐\n";
        cout << "│ #  │ NOMBRE                              │\n";
        cout << "├────┼─────────────────────────────────────┤\n";
        
        for(int i = 0; i < cantidad; i++) {
            cout << "│ " << setw(2) << left << (i+1) << " │ ";
            cout << setw(35) << left << personas[i].nombre << " │\n";
        }
        
        cout << "└────┴─────────────────────────────────────┘" << COLOR_RESET << "\n";
    } else {
        cout << COLOR_WARNING << "⚠️ No hay personas en esta categoría.\n" << COLOR_RESET;
    }
}

// Función para mostrar un gráfico de distribución
void mostrarGraficoDistribucion(int con_disc, int sin_disc, int total) {
    float porcentaje_con = ((float)con_disc / total) * 100;
    float porcentaje_sin = ((float)sin_disc / total) * 100;
    
    int barras_con = (int)(porcentaje_con / 2.5); // 40 barras total, cada una 2.5%
    int barras_sin = (int)(porcentaje_sin / 2.5);
    
    cout << COLOR_HIGHLIGHT << "\n📊 DISTRIBUCIÓN GRÁFICA:\n";
    cout << "======================\n\n" << COLOR_RESET;
    
    cout << COLOR_WITH << "Con discapacidad    [";
    for(int i = 0; i < 40; i++) {
        if(i < barras_con) cout << "█";
        else cout << "░";
    }
    cout << "] " << fixed << setprecision(1) << porcentaje_con << "% (" << con_disc << ")\n" << COLOR_RESET;
    
    cout << COLOR_WITHOUT << "Sin discapacidad    [";
    for(int i = 0; i < 40; i++) {
        if(i < barras_sin) cout << "█";
        else cout << "░";
    }
    cout << "] " << fixed << setprecision(1) << porcentaje_sin << "% (" << sin_disc << ")\n" << COLOR_RESET;
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaración de variables
    int n; // Número de personas
    Persona *personas; // Vector original de personas
    Persona *sin_discapacidad; // Vector para personas sin discapacidad
    Persona *con_discapacidad; // Vector para personas con discapacidad
    int contador_sin = 0; // Contador de personas sin discapacidad
    int contador_con = 0; // Contador de personas con discapacidad
    int opcion; // Para la selección de si tiene o no discapacidad
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa clasifica a un conjunto de personas en dos grupos\n";
    cout << "               según si tienen o no algún tipo de discapacidad.\n\n";
    
    // Pedir cantidad de personas con validación
    do {
        cout << COLOR_HIGHLIGHT << "👥 Ingrese el número de personas a registrar: " << COLOR_INPUT;
        cin >> n;
        cout << COLOR_RESET;
        
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << COLOR_ERROR << "⚠️ Error: Debe ingresar un número válido.\n\n" << COLOR_RESET;
        }
        else if(n <= 0) {
            cout << COLOR_ERROR << "⚠️ Error: Debe registrar al menos una persona.\n\n" << COLOR_RESET;
        }
    } while(n <= 0 || cin.fail());
    
    // Crear los vectores dinámicos
    personas = new Persona[n];
    sin_discapacidad = new Persona[n]; // En el peor caso, todos sin discapacidad
    con_discapacidad = new Persona[n]; // En el peor caso, todos con discapacidad
    
    // Pedir datos para cada persona
    for(int i = 0; i < n; i++) {
        cout << "\n" << COLOR_INFO << "👤 PERSONA " << i+1 << " DE " << n << ":\n";
        cout << "-------------------\n" << COLOR_RESET;
        
        cin.ignore(i == 0 ? 1 : 10000, '\n'); // Limpiar buffer
        cout << COLOR_HIGHLIGHT << "   Nombre: " << COLOR_INPUT;
        cin.getline(personas[i].nombre, 50, '\n');
        cout << COLOR_RESET;
        
        // Pedir si tiene discapacidad con validación
        do {
            cout << "\n" << COLOR_HIGHLIGHT << "   ¿Tiene alguna discapacidad?\n";
            cout << "   " << COLOR_SUCCESS << "1) Sí\n";
            cout << "   " << COLOR_WARNING << "0) No\n";
            cout << COLOR_HIGHLIGHT << "   Opción: " << COLOR_INPUT;
            cin >> opcion;
            cout << COLOR_RESET;
            
            if(cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << COLOR_ERROR << "   ⚠️ Error: Debe ingresar un número válido.\n\n" << COLOR_RESET;
            }
            else if(opcion != 0 && opcion != 1) {
                cout << COLOR_ERROR << "   ⚠️ Error: Debe ingresar 0 (No) o 1 (Sí).\n\n" << COLOR_RESET;
            }
        } while((opcion != 0 && opcion != 1) || cin.fail());
        
        // Asignar el valor booleano según la opción
        personas[i].discapacidad = (opcion == 1);
        
        // Mostrar progreso
        mostrarProgreso(i + 1, n);
    }
    
    // Separar las personas en los dos vectores
    for(int i = 0; i < n; i++) {
        if(personas[i].discapacidad) {
            // Persona con discapacidad
            strcpy(con_discapacidad[contador_con].nombre, personas[i].nombre);
            con_discapacidad[contador_con].discapacidad = true;
            contador_con++;
        } else {
            // Persona sin discapacidad
            strcpy(sin_discapacidad[contador_sin].nombre, personas[i].nombre);
            sin_discapacidad[contador_sin].discapacidad = false;
            contador_sin++;
        }
    }
    
    // Limpiar pantalla y mostrar resultados
    limpiarPantalla();
    mostrarBanner();
    
    // Mostrar el resumen de la clasificación
    cout << COLOR_HIGHLIGHT << "📊 RESUMEN DE LA CLASIFICACIÓN\n";
    cout << "============================\n\n" << COLOR_RESET;
    
    cout << COLOR_INFO << "Total de personas registradas: " << COLOR_HIGHLIGHT << n << COLOR_RESET << "\n";
    cout << COLOR_WITH << "Personas con discapacidad: " << contador_con << COLOR_RESET << "\n";
    cout << COLOR_WITHOUT << "Personas sin discapacidad: " << contador_sin << COLOR_RESET << "\n";
    
    // Mostrar gráfico de distribución
    mostrarGraficoDistribucion(contador_con, contador_sin, n);
    
    // Mostrar las personas sin discapacidad
    mostrarListaPersonas(sin_discapacidad, contador_sin, "PERSONAS SIN DISCAPACIDAD", COLOR_WITHOUT);
    
    // Mostrar las personas con discapacidad
    mostrarListaPersonas(con_discapacidad, contador_con, "PERSONAS CON DISCAPACIDAD", COLOR_WITH);
    
    // Liberar memoria
    delete[] personas;
    delete[] sin_discapacidad;
    delete[] con_discapacidad;
    
    // Añadir instrucciones finales
    cout << "\nPresione Enter para finalizar...";
    cin.ignore(10000, '\n');
    cin.get();
    
    return 0;
}
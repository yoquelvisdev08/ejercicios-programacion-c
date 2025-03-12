/*
 * 📚 SISTEMA DE GESTIÓN ACADÉMICA 📚
 * ================================
 * 
 * Bloque 8: Ejercicio 2
 * --------------------
 * Este programa gestiona información de estudiantes y determina
 * automáticamente quién tiene el mejor rendimiento académico.
 * Permite registrar datos de 3 alumnos y muestra los detalles
 * del estudiante con el promedio más alto.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h>
#include <iomanip>
#include <limits>
using namespace std;

// Definición de la estructura alumno
struct Alumno {
    char nombre[50];
    int edad;
    float promedio;
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
    cout << "\n";
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║      REGISTRO DE ESTUDIANTES v1.0     ║\n";
    cout << "╚══════════════════════════════════════╝\n\n";
}

// Función para mostrar una barra de progreso
void mostrarProgreso(int actual, int total) {
    cout << "\n📊 Progreso: [";
    int porcentaje = (actual * 20) / total;
    for(int i = 0; i < 20; i++) {
        if(i < porcentaje) cout << "█";
        else cout << "░";
    }
    cout << "] " << (actual * 100) / total << "%\n\n";
}

// Función para validar la edad (entre 6 y 100 años)
int pedirEdad(const char* mensaje) {
    int edad;
    bool valido = false;
    
    do {
        cout << mensaje;
        cin >> edad;
        
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n⚠️ Error: Por favor ingrese un número válido para la edad.\n\n";
        }
        else if(edad < 6 || edad > 100) {
            cout << "\n⚠️ Error: La edad debe estar entre 6 y 100 años.\n\n";
        }
        else {
            valido = true;
        }
    } while(!valido);
    
    return edad;
}

// Función para validar el promedio (entre 0 y 10)
float pedirPromedio(const char* mensaje) {
    float promedio;
    bool valido = false;
    
    do {
        cout << mensaje;
        cin >> promedio;
        
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n⚠️ Error: Por favor ingrese un número válido para el promedio.\n\n";
        }
        else if(promedio < 0 || promedio > 10) {
            cout << "\n⚠️ Error: El promedio debe estar entre 0 y 10.\n\n";
        }
        else {
            valido = true;
        }
    } while(!valido);
    
    return promedio;
}

int main() {
    Alumno alumnos[3];
    int indice_mayor = 0;
    float mayor_promedio = 0;
    
    // Limpiar pantalla y mostrar banner inicial
    limpiarPantalla();
    mostrarBanner();
    
    cout << "🎓 REGISTRO DE CALIFICACIONES\n";
    cout << "============================\n\n";
    cout << "Por favor, ingrese los datos de los 3 estudiantes:\n\n";
    
    // Pedir datos para los 3 alumnos
    for(int i = 0; i < 3; i++) {
        cout << "📝 ESTUDIANTE " << i+1 << " de 3\n";
        cout << "-------------------\n";
        
        cin.ignore(i == 0 ? 0 : numeric_limits<streamsize>::max(), '\n');
        
        cout << "👤 Nombre: ";
        cin.getline(alumnos[i].nombre, 50, '\n');
        
        cout << "\n"; // Salto de línea entre inputs
        
        alumnos[i].edad = pedirEdad("🎂 Edad: ");
        
        cout << "\n"; // Salto de línea entre inputs
        
        alumnos[i].promedio = pedirPromedio("📊 Promedio (0-10): ");
        
        // Verificar si este alumno tiene el mayor promedio
        if(alumnos[i].promedio > mayor_promedio) {
            mayor_promedio = alumnos[i].promedio;
            indice_mayor = i;
        }
        
        // Mostrar progreso
        mostrarProgreso(i + 1, 3);
    }
    
    // Limpiar pantalla y mostrar resultados
    limpiarPantalla();
    mostrarBanner();
    
    // Mostrar los datos del alumno con el mejor promedio
    cout << "🏆 ESTUDIANTE DESTACADO\n";
    cout << "=====================\n\n";
    
    cout << setfill(' ') << fixed << setprecision(2);
    cout << left << setw(15) << "👤 Nombre:" << alumnos[indice_mayor].nombre << endl;
    cout << left << setw(15) << "🎂 Edad:" << alumnos[indice_mayor].edad << " años" << endl;
    cout << left << setw(15) << "📊 Promedio:" << alumnos[indice_mayor].promedio << endl;
    
    // Mostrar medalla según el promedio
    cout << "\n🎉 ¡Felicitaciones! ";
    if(alumnos[indice_mayor].promedio >= 9.0) cout << "¡Medalla de Oro! 🥇";
    else if(alumnos[indice_mayor].promedio >= 8.0) cout << "¡Medalla de Plata! 🥈";
    else cout << "¡Medalla de Bronce! 🥉";
    cout << "\n\n";
    
    // Añadir tabla comparativa de todos los estudiantes
    cout << "📋 RESUMEN DE TODOS LOS ESTUDIANTES:\n";
    cout << "==================================\n\n";
    
    cout << "┌───────┬─────────────────────┬───────┬──────────┬─────────┐\n";
    cout << "│ NUM   │ NOMBRE              │ EDAD  │ PROMEDIO │ MEDALLA │\n";
    cout << "├───────┼─────────────────────┼───────┼──────────┼─────────┤\n";
    
    for(int i = 0; i < 3; i++) {
        cout << "│ " << setw(5) << left << (i+1) << " │ ";
        cout << setw(19) << left << alumnos[i].nombre << " │ ";
        cout << setw(5) << left << alumnos[i].edad << " │ ";
        cout << setw(8) << left << fixed << setprecision(2) << alumnos[i].promedio << " │ ";
        
        // Mostrar medalla según el promedio
        if(alumnos[i].promedio >= 9.0) cout << setw(7) << left << "🥇" << " │\n";
        else if(alumnos[i].promedio >= 8.0) cout << setw(7) << left << "🥈" << " │\n";
        else if(alumnos[i].promedio >= 7.0) cout << setw(7) << left << "🥉" << " │\n";
        else cout << setw(7) << left << "  " << " │\n";
    }
    
    cout << "└───────┴─────────────────────┴───────┴──────────┴─────────┘\n\n";
    
    // Añadir instrucciones finales
    cout << "Presione Enter para finalizar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    
    return 0;
} 
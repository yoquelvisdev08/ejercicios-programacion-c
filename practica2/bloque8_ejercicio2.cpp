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
        
        cout << "👤 Nombre: ";
        cin.ignore(i == 0 ? 0 : numeric_limits<streamsize>::max(), '\n');
        cin.getline(alumnos[i].nombre, 50, '\n');
        
        cout << "🎂 Edad: ";
        cin >> alumnos[i].edad;
        
        do {
            cout << "📊 Promedio (0-10): ";
            cin >> alumnos[i].promedio;
            if(alumnos[i].promedio < 0 || alumnos[i].promedio > 10) {
                cout << "❌ Error: El promedio debe estar entre 0 y 10\n";
            }
        } while(alumnos[i].promedio < 0 || alumnos[i].promedio > 10);
        
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
    
    return 0;
} 
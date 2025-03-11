/*
 * 🏃 SISTEMA DE GESTIÓN DE CORREDORES 🏃
 * =====================================
 * 
 * Bloque 8: Ejercicio 1
 * --------------------
 * Este programa gestiona la información de corredores y determina
 * automáticamente su categoría de competición basada en la edad:
 * 
 * 🏆 Categorías:
 * - 🌟 Juvenil: ≤ 18 años
 * - 💪 Senior: ≤ 40 años
 * - 👑 Veterano: > 40 años
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;

// Definición de la estructura corredor
struct Corredor {
    char nombre[50];
    int edad;
    char sexo[10];
    char club[30];
    char categoria[20];
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
    cout << "║     REGISTRO DE CORREDORES v1.0      ║\n";
    cout << "╚══════════════════════════════════════╝\n\n";
}

int main() {
    Corredor corredor1;
    
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Pedir datos al usuario con formato mejorado
    cout << "📝 Por favor, ingrese los datos del corredor:\n";
    cout << "============================================\n\n";
    
    cout << "👤 Nombre: ";
    cin.getline(corredor1.nombre, 50, '\n');
    
    cout << "🎂 Edad: ";
    cin >> corredor1.edad;
    cin.ignore();
    
    cout << "⚥ Sexo (Masculino/Femenino): ";
    cin.getline(corredor1.sexo, 10, '\n');
    
    cout << "🏢 Club: ";
    cin.getline(corredor1.club, 30, '\n');
    
    // Asignar categoría según la edad
    if(corredor1.edad <= 18) {
        strcpy(corredor1.categoria, "Juvenil 🌟");
    } else if(corredor1.edad <= 40) {
        strcpy(corredor1.categoria, "Senior 💪");
    } else {
        strcpy(corredor1.categoria, "Veterano 👑");
    }
    
    // Limpiar pantalla y mostrar resultados
    limpiarPantalla();
    mostrarBanner();
    
    // Mostrar los datos del corredor con formato mejorado
    cout << "📊 FICHA DEL CORREDOR\n";
    cout << "====================\n\n";
    
    cout << setfill(' ') << fixed;
    cout << left << setw(15) << "👤 Nombre:" << corredor1.nombre << endl;
    cout << left << setw(15) << "🎂 Edad:" << corredor1.edad << " años" << endl;
    cout << left << setw(15) << "⚥ Sexo:" << corredor1.sexo << endl;
    cout << left << setw(15) << "🏢 Club:" << corredor1.club << endl;
    cout << left << setw(15) << "🏆 Categoría:" << corredor1.categoria << endl;
    
    cout << "\n✨ ¡Registro completado con éxito! ✨\n\n";
    
    return 0;
} 
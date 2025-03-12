/*
 * 🏆 SISTEMA DE REGISTRO DE ATLETAS 🏆
 * =================================
 *
 * Bloque 8: Ejercicio 4
 * --------------------
 * Programa que crea un arreglo de estructura llamada atleta para N atletas
 * que contiene: nombre, país, número de medallas, y devuelve los datos
 * (Nombre, país) del atleta que ha ganado el mayor número de medallas.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h>
#include <iomanip>
#include <limits>
using namespace std;

// Definición de la estructura Atleta
struct Atleta {
    char nombre[50];
    char pais[50];
    int medallas;
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
    cout << "╔═══════════════════════════════════════╗\n";
    cout << "║      REGISTRO OLÍMPICO DE ATLETAS     ║\n";
    cout << "╚═══════════════════════════════════════╝\n\n";
}

// Función para mostrar una línea de progreso
void mostrarProgreso(int actual, int total) {
    float porcentaje = (float)actual / total * 100;
    int barraLongitud = 30;
    int completo = (int)(porcentaje * barraLongitud / 100);
    
    cout << "\n📊 Progreso: [";
    for(int i = 0; i < barraLongitud; i++) {
        if(i < completo) cout << "█";
        else cout << "░";
    }
    cout << "] " << fixed << setprecision(1) << porcentaje << "%\n\n";
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaración de variables
    int n;
    Atleta *atletas;
    int indice_mayor = 0;
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa registra datos de atletas olímpicos\n";
    cout << "               y encuentra al atleta con mayor número de medallas.\n\n";
    
    // Solicitar el número de atletas con validación
    do {
        cout << "📊 Ingrese el número de atletas a registrar: ";
        cin >> n;
        
        if(n <= 0) {
            cout << "⚠️  Error: Debe registrar al menos un atleta.\n\n";
        }
    } while(n <= 0);
    
    // Crear el arreglo dinámico de atletas
    atletas = new Atleta[n];
    
    // Solicitar los datos de los atletas
    cout << "\n🏅 REGISTRO DE DATOS DE ATLETAS:\n";
    cout << "=============================\n";
    
    for(int i = 0; i < n; i++) {
        cout << "\n👤 ATLETA #" << (i+1) << " de " << n << ":\n";
        cout << "----------------\n";
        
        // Limpiar buffer para evitar problemas con getline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "  🏃 Nombre: ";
        cin.getline(atletas[i].nombre, 50);
        
        cout << "  🌎 País: ";
        cin.getline(atletas[i].pais, 50);
        
        do {
            cout << "  🥇 Número de medallas: ";
            cin >> atletas[i].medallas;
            
            if(atletas[i].medallas < 0) {
                cout << "  ⚠️  Error: El número de medallas no puede ser negativo.\n";
            }
        } while(atletas[i].medallas < 0);
        
        // Actualizar el atleta con mayor número de medallas
        if(i == 0 || atletas[i].medallas > atletas[indice_mayor].medallas) {
            indice_mayor = i;
        }
        
        // Mostrar progreso
        mostrarProgreso(i+1, n);
    }
    
    // Mostrar tabla con todos los atletas
    limpiarPantalla();
    mostrarBanner();
    
    cout << "📊 TABLA DE ATLETAS REGISTRADOS:\n";
    cout << "==============================\n\n";
    
    cout << "+-----+------------------------+------------------------+------------+\n";
    cout << "| NUM |         NOMBRE         |          PAÍS          |  MEDALLAS  |\n";
    cout << "+-----+------------------------+------------------------+------------+\n";
    
    for(int i = 0; i < n; i++) {
        cout << "| " << setw(3) << (i+1) << " | "
             << setw(22) << left << atletas[i].nombre << " | "
             << setw(22) << left << atletas[i].pais << " | "
             << setw(10) << right << atletas[i].medallas << " |";
        
        // Marcar al atleta con más medallas
        if(i == indice_mayor) {
            cout << " 🏆";
        }
        
        cout << "\n";
    }
    
    cout << "+-----+------------------------+------------------------+------------+\n\n";
    
    // Mostrar los datos del atleta con más medallas
    cout << "🏆 ATLETA CON MAYOR NÚMERO DE MEDALLAS:\n";
    cout << "====================================\n\n";
    
    cout << "👤 Nombre: " << atletas[indice_mayor].nombre << "\n";
    cout << "🌎 País: " << atletas[indice_mayor].pais << "\n";
    cout << "🥇 Medallas: " << atletas[indice_mayor].medallas << "\n\n";
    
    // Mensaje de reconocimiento
    cout << "✨ ¡" << atletas[indice_mayor].nombre << " de " 
         << atletas[indice_mayor].pais << " es el atleta más destacado";
    
    if(atletas[indice_mayor].medallas == 1) {
        cout << " con 1 medalla! ✨\n\n";
    } else {
        cout << " con " << atletas[indice_mayor].medallas << " medallas! ✨\n\n";
    }
    
    // Liberar memoria
    delete[] atletas;
    
    return 0;
} 
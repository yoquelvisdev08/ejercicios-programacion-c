/*
 * 💼 SISTEMA DE GESTIÓN DE PERSONAL 💼
 * =================================
 * 
 * Bloque 8: Ejercicio 3
 * --------------------
 * Este programa gestiona información de empleados y analiza
 * sus salarios para identificar los extremos salariales
 * en la empresa. Permite registrar N empleados y muestra
 * los detalles de quienes tienen el mayor y menor salario.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h>
#include <iomanip>
#include <limits>
using namespace std;

// Definición de la estructura Empleado
struct Empleado {
    char nombre[50];
    char cargo[30];
    float salario;
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
    cout << "║    GESTIÓN DE RECURSOS HUMANOS v1.0   ║\n";
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

// Función para formatear el salario
string formatearSalario(float salario) {
    char buffer[50];
    sprintf(buffer, "$%,.2f", salario);
    return string(buffer);
}

int main() {
    int n;
    Empleado *empleados;
    int pos_mayor = 0;
    int pos_menor = 0;
    float mayor_salario = 0;
    float menor_salario = numeric_limits<float>::max();
    
    // Limpiar pantalla y mostrar banner inicial
    limpiarPantalla();
    mostrarBanner();
    
    cout << "👥 REGISTRO DE EMPLEADOS\n";
    cout << "=======================\n\n";
    
    // Pedir cantidad de empleados
    do {
        cout << "📋 Número de empleados a registrar: ";
        cin >> n;
        if(n <= 0) {
            cout << "❌ Error: Debe registrar al menos un empleado\n\n";
        }
    } while(n <= 0);
    
    // Crear el arreglo dinámico
    empleados = new Empleado[n];
    
    cout << "\n✨ Por favor, ingrese los datos de los empleados:\n\n";
    
    // Pedir datos de los empleados
    for(int i = 0; i < n; i++) {
        cout << "👤 EMPLEADO " << i+1 << " de " << n << "\n";
        cout << "-------------------\n";
        
        cin.ignore(i == 0 ? 0 : numeric_limits<streamsize>::max(), '\n');
        
        cout << "📝 Nombre: ";
        cin.getline(empleados[i].nombre, 50, '\n');
        
        cout << "💼 Cargo: ";
        cin.getline(empleados[i].cargo, 30, '\n');
        
        do {
            cout << "💰 Salario: $";
            cin >> empleados[i].salario;
            if(empleados[i].salario <= 0) {
                cout << "❌ Error: El salario debe ser mayor que 0\n";
            }
        } while(empleados[i].salario <= 0);
        
        // Verificar salarios extremos
        if(empleados[i].salario > mayor_salario) {
            mayor_salario = empleados[i].salario;
            pos_mayor = i;
        }
        if(empleados[i].salario < menor_salario) {
            menor_salario = empleados[i].salario;
            pos_menor = i;
        }
        
        // Mostrar progreso
        mostrarProgreso(i + 1, n);
    }
    
    // Limpiar pantalla y mostrar resultados
    limpiarPantalla();
    mostrarBanner();
    
    cout << "📊 ANÁLISIS SALARIAL\n";
    cout << "===================\n\n";
    
    // Mostrar empleado con mayor salario
    cout << "🏆 SALARIO MÁS ALTO\n";
    cout << "-------------------\n";
    cout << setfill(' ') << fixed << setprecision(2);
    cout << left << setw(15) << "👤 Nombre:" << empleados[pos_mayor].nombre << endl;
    cout << left << setw(15) << "💼 Cargo:" << empleados[pos_mayor].cargo << endl;
    cout << left << setw(15) << "💰 Salario:" << formatearSalario(empleados[pos_mayor].salario) << endl;
    
    cout << "\n📉 SALARIO MÁS BAJO\n";
    cout << "-------------------\n";
    cout << left << setw(15) << "👤 Nombre:" << empleados[pos_menor].nombre << endl;
    cout << left << setw(15) << "💼 Cargo:" << empleados[pos_menor].cargo << endl;
    cout << left << setw(15) << "💰 Salario:" << formatearSalario(empleados[pos_menor].salario) << endl;
    
    // Mostrar diferencia salarial
    cout << "\n📈 BRECHA SALARIAL\n";
    cout << "----------------\n";
    cout << "Diferencia: " << formatearSalario(mayor_salario - menor_salario) << endl;
    
    // Liberar memoria
    delete[] empleados;
    
    cout << "\n✨ Análisis completado con éxito ✨\n\n";
    
    return 0;
} 
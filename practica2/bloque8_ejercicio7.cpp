/*
 * ⏱️ CRONÓMETRO DE CICLISMO ⏱️
 * =========================
 * 
 * Bloque 8: Ejercicio 7
 * --------------------
 * Programa que define una estructura que indica el tiempo empleado por un ciclista
 * en una etapa. La estructura tiene tres campos: horas, minutos y segundos.
 * Calcula el tiempo total empleado en correr todas las etapas.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
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
const string COLOR_RESULT = "\033[1;35m";  // Magenta brillante
const string COLOR_SUCCESS = "\033[1;92m";  // Verde claro brillante

// Definición de la estructura Tiempo
struct Tiempo {
    int horas;
    int minutos;
    int segundos;
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
    cout << "╔═══════════════════════════════════════╗\n";
    cout << "║        CRONÓMETRO DE CICLISMO         ║\n";
    cout << "╚═══════════════════════════════════════╝\n\n" << COLOR_RESET;
}

// Función para pedir un valor de tiempo con validación
int pedirTiempo(const char* mensaje, int min, int max) {
    int valor;
    bool valido = false;
    
    do {
        cout << COLOR_HIGHLIGHT << mensaje << COLOR_INPUT;
        cin >> valor;
        cout << COLOR_RESET;
        
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << COLOR_ERROR << "   ⚠️ Error: Debe ingresar un número válido.\n\n" << COLOR_RESET;
        }
        else if(valor < min || valor > max) {
            cout << COLOR_ERROR << "   ⚠️ Error: El valor debe estar entre " << min << " y " << max << ".\n\n" << COLOR_RESET;
        }
        else {
            valido = true;
        }
    } while(!valido);
    
    return valor;
}

// Función para formatear tiempo en formato HH:MM:SS
string formatearTiempo(const Tiempo& t) {
    char buffer[20];
    sprintf(buffer, "%02d:%02d:%02d", t.horas, t.minutos, t.segundos);
    return string(buffer);
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

// Función para mostrar una visualización gráfica del tiempo total
void mostrarGraficoTiempo(const Tiempo& tiempo) {
    // Convertir todo a segundos para la visualización
    int segundos_totales = tiempo.horas * 3600 + tiempo.minutos * 60 + tiempo.segundos;
    
    // Determinar escala: cada bloque representa 10 minutos (600 segundos)
    int bloques = segundos_totales / 600;
    if (segundos_totales % 600 > 0) bloques++; // Redondeando hacia arriba
    
    cout << COLOR_INFO << "   Cada █ representa 10 minutos\n\n";
    cout << "   [";
    for(int i = 0; i < bloques; i++) {
        if(i % 6 == 0 && i > 0) {
            cout << COLOR_RESULT << "⎮" << COLOR_INFO; // Marca cada hora
        }
        cout << COLOR_HIGHLIGHT << "█";
    }
    cout << COLOR_INFO << "] " << formatearTiempo(tiempo) << COLOR_RESET << "\n\n";
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaración de variables
    int n; // Número de etapas
    Tiempo *etapas; // Arreglo dinámico para almacenar los tiempos por etapa
    Tiempo total = {0, 0, 0}; // Tiempo total inicializado en cero
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa calcula el tiempo total empleado por un ciclista\n";
    cout << "               en varias etapas de una competición.\n\n";
    
    // Pedir cantidad de etapas con validación
    do {
        cout << COLOR_HIGHLIGHT << "🚲 Ingrese el número de etapas: " << COLOR_INPUT;
        cin >> n;
        cout << COLOR_RESET;
        
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << COLOR_ERROR << "⚠️ Error: Debe ingresar un número válido.\n\n" << COLOR_RESET;
        }
        else if(n <= 0) {
            cout << COLOR_ERROR << "⚠️ Error: Debe registrar al menos una etapa.\n\n" << COLOR_RESET;
        }
    } while(n <= 0 || cin.fail());
    
    // Crear el arreglo dinámico para las etapas
    etapas = new Tiempo[n];
    
    // Pedir datos para cada etapa
    for(int i = 0; i < n; i++) {
        cout << "\n" << COLOR_INFO << "⏱️ ETAPA " << i+1 << " DE " << n << ":\n";
        cout << "---------------------\n" << COLOR_RESET;
        
        etapas[i].horas = pedirTiempo("   Horas: ", 0, 23);
        cout << "\n"; // Salto de línea entre inputs
        
        etapas[i].minutos = pedirTiempo("   Minutos: ", 0, 59);
        cout << "\n"; // Salto de línea entre inputs
        
        etapas[i].segundos = pedirTiempo("   Segundos: ", 0, 59);
        
        // Mostrar progreso
        mostrarProgreso(i + 1, n);
    }
    
    // Calcular el tiempo total
    for(int i = 0; i < n; i++) {
        total.horas += etapas[i].horas;
        total.minutos += etapas[i].minutos;
        total.segundos += etapas[i].segundos;
    }
    
    // Ajustar los minutos y segundos si son mayores o iguales a 60
    total.minutos += total.segundos / 60;
    total.segundos = total.segundos % 60;
    
    total.horas += total.minutos / 60;
    total.minutos = total.minutos % 60;
    
    // Limpiar pantalla y mostrar resultados
    limpiarPantalla();
    mostrarBanner();
    
    // Mostrar tabla de etapas
    cout << COLOR_HIGHLIGHT << "📊 REGISTRO DE TIEMPOS POR ETAPA\n";
    cout << "==============================\n\n" << COLOR_RESET;
    
    cout << COLOR_INFO << "┌────────┬────────────┬────────────┬────────────┬────────────┐\n";
    cout << "│ ETAPA  │   HORAS    │  MINUTOS   │ SEGUNDOS   │   TIEMPO   │\n";
    cout << "├────────┼────────────┼────────────┼────────────┼────────────┤" << COLOR_RESET << "\n";
    
    for(int i = 0; i < n; i++) {
        cout << "│ " << setw(6) << left << (i+1) << " │ ";
        cout << setw(10) << left << etapas[i].horas << " │ ";
        cout << setw(10) << left << etapas[i].minutos << " │ ";
        cout << setw(10) << left << etapas[i].segundos << " │ ";
        cout << COLOR_RESULT << setw(10) << left << formatearTiempo(etapas[i]) << COLOR_RESET << " │\n";
    }
    
    cout << COLOR_INFO << "├────────┴────────────┴────────────┴────────────┼────────────┤\n";
    cout << "│                    TIEMPO TOTAL                 │ ";
    cout << COLOR_RESULT << setw(10) << left << formatearTiempo(total) << COLOR_RESET << " │\n";
    cout << COLOR_INFO << "└─────────────────────────────────────────────┴────────────┘" << COLOR_RESET << "\n\n";
    
    // Mostrar el tiempo total con más detalles
    cout << COLOR_HIGHLIGHT << "⏱️ TIEMPO TOTAL EMPLEADO\n";
    cout << "======================\n\n" << COLOR_RESET;
    
    cout << COLOR_INFO << "┌───────────────────────────────────────┐\n";
    cout << "│            DESGLOSE DE TIEMPO           │\n";
    cout << "├───────────────────────────────────────┤\n";
    cout << "│ " << left << setw(15) << "Horas:" << left << setw(24) << total.horas << "│\n";
    cout << "│ " << left << setw(15) << "Minutos:" << left << setw(24) << total.minutos << "│\n";
    cout << "│ " << left << setw(15) << "Segundos:" << left << setw(24) << total.segundos << "│\n";
    cout << "├───────────────────────────────────────┤\n";
    cout << "│ " << left << setw(15) << "Tiempo total:" << COLOR_RESULT << left << setw(24) << formatearTiempo(total) << COLOR_INFO << "│\n";
    cout << "└───────────────────────────────────────┘" << COLOR_RESET << "\n\n";
    
    // Mostrar gráfico del tiempo total
    cout << COLOR_HIGHLIGHT << "📈 REPRESENTACIÓN GRÁFICA DEL TIEMPO TOTAL:\n" << COLOR_RESET;
    mostrarGraficoTiempo(total);
    
    // Liberar memoria
    delete[] etapas;
    
    // Añadir estadísticas adicionales si se registraron múltiples etapas
    if(n > 1) {
        cout << COLOR_HIGHLIGHT << "📋 ESTADÍSTICAS ADICIONALES:\n";
        cout << "===========================\n\n" << COLOR_RESET;
        
        cout << COLOR_INFO << "✓ Promedio por etapa: " << COLOR_RESULT << formatearTiempo({total.horas/n, total.minutos/n, total.segundos/n}) << COLOR_RESET << "\n";
        cout << COLOR_INFO << "✓ Total de etapas recorridas: " << COLOR_RESULT << n << COLOR_RESET << "\n\n";
    }
    
    // Añadir instrucciones finales
    cout << "Presione Enter para finalizar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    
    return 0;
} 
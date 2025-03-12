/*
 * 📝 COMPARADOR DE CADENAS 📝
 * ========================
 *
 * Bloque 7: Ejercicio 3
 * --------------------
 * Programa que pide al usuario que digite 2 cadenas de caracteres,
 * e indica si ambas cadenas son iguales. En caso de no serlo,
 * indica cuál es mayor alfabéticamente.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h> // Para strcmp()
#include <iomanip>
using namespace std;

// Constantes para colores (ANSI escape codes)
const string COLOR_RESET = "\033[0m";
const string COLOR_TITLE = "\033[1;36m";  // Cyan brillante
const string COLOR_HIGHLIGHT = "\033[1;33m";  // Amarillo brillante
const string COLOR_INPUT = "\033[1;32m";  // Verde brillante
const string COLOR_STRING1 = "\033[1;34m";  // Azul brillante
const string COLOR_STRING2 = "\033[1;35m";  // Magenta brillante
const string COLOR_TABLE = "\033[1;37;44m";  // Blanco brillante sobre azul
const string COLOR_RESULT = "\033[1;31m";  // Rojo brillante

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
    cout << "╔═══════════════════════════════════╗\n";
    cout << "║       COMPARADOR DE CADENAS       ║\n";
    cout << "╚═══════════════════════════════════╝\n\n" << COLOR_RESET;
}

// Función para mostrar una cadena con formato visual
void mostrarCadena(const char* cadena, const char* titulo, string color) {
    int longitud = strlen(cadena);
    
    cout << COLOR_HIGHLIGHT << "\n" << titulo << COLOR_RESET << endl;
    
    // Mostrar cadena con formato de caja
    cout << color << "┌";
    for(int i = 0; i < longitud + 2; i++) cout << "─";
    cout << "┐\n";
    
    cout << "│ " << cadena << " │\n";
    
    cout << "└";
    for(int i = 0; i < longitud + 2; i++) cout << "─";
    cout << "┘" << COLOR_RESET << "\n";
    
    // Información adicional
    cout << "   Longitud: " << longitud << " caracteres\n";
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaracion de variables
    char cadena1[100];
    char cadena2[100];
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa compara dos cadenas de texto e indica\n";
    cout << "               si son iguales o cuál es mayor alfabéticamente.\n\n";
    
    // Solicitar las cadenas
    cout << COLOR_HIGHLIGHT << "🔤 INGRESO DE CADENAS DE TEXTO:\n";
    cout << "=============================\n" << COLOR_RESET;
    
    cout << COLOR_HIGHLIGHT << "📝 Ingrese la primera cadena: " << COLOR_INPUT;
    cin.getline(cadena1, 100, '\n');
    cout << COLOR_RESET;
    
    cout << "\n"; // Salto de línea entre inputs
    
    cout << COLOR_HIGHLIGHT << "📝 Ingrese la segunda cadena: " << COLOR_INPUT;
    cin.getline(cadena2, 100, '\n');
    cout << COLOR_RESET;
    
    // Mostrar las cadenas ingresadas
    mostrarCadena(cadena1, "📊 PRIMERA CADENA:", COLOR_STRING1);
    mostrarCadena(cadena2, "📊 SEGUNDA CADENA:", COLOR_STRING2);
    
    // Comparar las cadenas
    cout << "\n" << COLOR_HIGHLIGHT << "🔍 COMPARANDO CADENAS...\n";
    cout << "=====================\n" << COLOR_RESET;
    
    // Resultado de la comparación
    int resultado = strcmp(cadena1, cadena2);
    
    // Tabla de comparación con mejor formato
    cout << COLOR_TABLE << "┌────────────────────────┬───────────────────────┐\n";
    cout << "│ CRITERIO                │ RESULTADO               │\n";
    cout << "├────────────────────────┼───────────────────────┤" << COLOR_RESET << "\n";
    
    // Fila 1: ¿Son iguales?
    cout << "│ ¿Las cadenas son        │ ";
    if(resultado == 0) {
        cout << COLOR_RESULT << "✅ SÍ son iguales" << COLOR_RESET << "        │\n";
    } else {
        cout << COLOR_RESULT << "❌ NO son iguales" << COLOR_RESET << "        │\n";
    }
    
    // Fila 2: Orden alfabético
    cout << "│ Orden alfabético        │ ";
    if(resultado != 0) {
        if(resultado > 0) {
            cout << COLOR_RESULT << "\"" << cadena2 << "\" precede a \"" << cadena1 << "\"" << COLOR_RESET;
            // Rellenar espacios
            for(int i = 0; i < 20 - (strlen(cadena1) + strlen(cadena2) + 15); i++) cout << " ";
            cout << "│\n";
        } else {
            cout << COLOR_RESULT << "\"" << cadena1 << "\" precede a \"" << cadena2 << "\"" << COLOR_RESET;
            // Rellenar espacios
            for(int i = 0; i < 20 - (strlen(cadena1) + strlen(cadena2) + 15); i++) cout << " ";
            cout << "│\n";
        }
    } else {
        cout << COLOR_RESULT << "No aplica" << COLOR_RESET << "                │\n";
    }
    
    cout << "└────────────────────────┴───────────────────────┘\n";
    
    // Explicación del proceso
    cout << "\n" << COLOR_HIGHLIGHT << "📝 EXPLICACIÓN DEL PROCESO:" << COLOR_RESET << endl;
    cout << "1. Se leyeron dos cadenas del usuario.\n";
    cout << "2. Se utilizó strcmp() para comparar las cadenas carácter por carácter.\n";
    cout << "3. strcmp() devuelve:\n";
    cout << "   - 0 si las cadenas son idénticas\n";
    cout << "   - <0 si la primera cadena es menor (precede alfabéticamente)\n";
    cout << "   - >0 si la primera cadena es mayor\n\n";
    
    // Conclusión más clara
    cout << COLOR_HIGHLIGHT << "📌 CONCLUSIÓN: " << COLOR_RESET;
    if(resultado == 0) {
        cout << COLOR_RESULT << "Ambas cadenas son exactamente iguales." << COLOR_RESET << "\n\n";
    } else if(resultado > 0) {
        cout << COLOR_RESULT << "La cadena \"" << cadena2 << "\" es alfabéticamente mayor que \"" << cadena1 << "\"." << COLOR_RESET << "\n\n";
    } else {
        cout << COLOR_RESULT << "La cadena \"" << cadena1 << "\" es alfabéticamente mayor que \"" << cadena2 << "\"." << COLOR_RESET << "\n\n";
    }
    
    // Añadir instrucciones finales
    cout << "Presione Enter para finalizar...";
    cin.ignore();
    cin.get();
    
    return 0;
} 
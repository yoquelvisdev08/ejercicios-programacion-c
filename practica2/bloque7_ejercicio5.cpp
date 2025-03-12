/*
 * 🔄 VERIFICADOR DE PALÍNDROMOS 🔄
 * =============================
 *
 * Bloque 7: Ejercicio 5
 * --------------------
 * Programa que determina si una palabra es palíndroma.
 * (Se lee igual de izquierda a derecha que de derecha a izquierda)
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h>
#include <cctype>  // Para tolower()
#include <iomanip>
using namespace std;

// Constantes para colores (ANSI escape codes)
const string COLOR_RESET = "\033[0m";
const string COLOR_TITLE = "\033[1;36m";  // Cyan brillante
const string COLOR_HIGHLIGHT = "\033[1;33m";  // Amarillo brillante
const string COLOR_INPUT = "\033[1;32m";  // Verde brillante
const string COLOR_NORMAL = "\033[1;34m";  // Azul brillante
const string COLOR_INVERSE = "\033[1;35m";  // Magenta brillante
const string COLOR_MATCH = "\033[1;32m";  // Verde brillante
const string COLOR_MISMATCH = "\033[1;31m";  // Rojo brillante
const string COLOR_RESULT = "\033[1;37m";  // Blanco brillante

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
    cout << "║      VERIFICADOR DE PALÍNDROMOS       ║\n";
    cout << "╚═══════════════════════════════════════╝\n\n" << COLOR_RESET;
}

// Función para convertir una cadena a minúsculas y sin espacios
void limpiarCadena(const char* original, char* limpia) {
    int j = 0;
    
    for(int i = 0; i < strlen(original); i++) {
        if(isalpha(original[i])) {
            limpia[j++] = tolower(original[i]);
        }
    }
    
    limpia[j] = '\0';  // Agregar terminador de cadena
}

// Función para mostrar la animación de verificación
void mostrarAnimacionVerificacion(const char* palabra, bool esPalindromo) {
    int longitud = strlen(palabra);
    int mitad = longitud / 2;
    
    cout << "\n" << COLOR_HIGHLIGHT << "🔍 VERIFICACIÓN CARÁCTER POR CARÁCTER:\n";
    cout << "===================================\n" << COLOR_RESET;
    
    // Mostrar la verificación de cada par de caracteres
    for(int i = 0; i < mitad; i++) {
        int j = longitud - 1 - i;
        
        cout << "Comparando: ";
        
        // Posición izquierda
        cout << "Posición " << setw(2) << i << " [";
        if(palabra[i] == palabra[j]) {
            cout << COLOR_MATCH << palabra[i] << COLOR_RESET;
        } else {
            cout << COLOR_MISMATCH << palabra[i] << COLOR_RESET;
        }
        cout << "] ";
        
        // Flecha de comparación
        if(palabra[i] == palabra[j]) {
            cout << COLOR_MATCH << "==" << COLOR_RESET;
        } else {
            cout << COLOR_MISMATCH << "!=" << COLOR_RESET;
        }
        
        // Posición derecha
        cout << " Posición " << setw(2) << j << " [";
        if(palabra[i] == palabra[j]) {
            cout << COLOR_MATCH << palabra[j] << COLOR_RESET;
        } else {
            cout << COLOR_MISMATCH << palabra[j] << COLOR_RESET;
        }
        cout << "] ";
        
        // Resultado de la comparación
        if(palabra[i] == palabra[j]) {
            cout << COLOR_MATCH << "✓ Coincide" << COLOR_RESET;
        } else {
            cout << COLOR_MISMATCH << "✗ No coincide" << COLOR_RESET;
        }
        
        cout << "\n";
    }
    
    // Resultado final
    cout << "\n" << COLOR_HIGHLIGHT << "🎯 RESULTADO: " << COLOR_RESET;
    if(esPalindromo) {
        cout << COLOR_MATCH << "✅ Todas las comparaciones coinciden, es un palíndromo.\n" << COLOR_RESET;
    } else {
        cout << COLOR_MISMATCH << "❌ Al menos una comparación no coincide, no es un palíndromo.\n" << COLOR_RESET;
    }
}

// Función para mostrar una cadena con formato visual
void mostrarTexto(const char* texto, const char* titulo, string color) {
    cout << COLOR_HIGHLIGHT << "\n" << titulo << COLOR_RESET << endl;
    
    // Mostrar texto con formato de caja
    cout << color << "┌";
    for(int i = 0; i < strlen(texto) + 2; i++) cout << "─";
    cout << "┐\n";
    
    cout << "│ " << texto << " │\n";
    
    cout << "└";
    for(int i = 0; i < strlen(texto) + 2; i++) cout << "─";
    cout << "┘" << COLOR_RESET << "\n";
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaracion de variables
    char palabra[100];
    char palabraLimpia[100];
    bool esPalindromo = true;
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa verifica si una palabra o frase\n";
    cout << "               es un palíndromo (se lee igual en ambos sentidos).\n";
    cout << "               Ejemplos: ana, reconocer, anita lava la tina\n\n";
    
    // Solicitar la palabra
    cout << COLOR_HIGHLIGHT << "🔤 Ingrese una palabra o frase: " << COLOR_INPUT;
    cin.getline(palabra, 100);
    cout << COLOR_RESET;
    
    // Limpiar la palabra (quitar espacios y convertir a minúsculas)
    limpiarCadena(palabra, palabraLimpia);
    
    int longitud = strlen(palabraLimpia);
    
    // Verificar si es un palíndromo
    for(int i = 0; i < longitud/2; i++) {
        if(palabraLimpia[i] != palabraLimpia[longitud-1-i]) {
            esPalindromo = false;
            break;
        }
    }
    
    // Mostrar información del análisis
    cout << "\n" << COLOR_HIGHLIGHT << "📊 ANÁLISIS DE PALÍNDROMO:\n";
    cout << "========================\n" << COLOR_RESET;
    
    // Mostrar textos con formato
    mostrarTexto(palabra, "📝 TEXTO ORIGINAL:", COLOR_NORMAL);
    mostrarTexto(palabraLimpia, "🧹 TEXTO PROCESADO (sin espacios, en minúsculas):", COLOR_NORMAL);
    
    // Visualización del palíndromo
    cout << "\n" << COLOR_HIGHLIGHT << "🔄 VISUALIZACIÓN BIDIRECCIONAL:\n";
    cout << "-----------------\n" << COLOR_RESET;
    
    // Mostrar la palabra de izquierda a derecha
    cout << COLOR_NORMAL << "   Normal:  ";
    for(int i = 0; i < longitud; i++) {
        cout << palabraLimpia[i] << " ";
    }
    cout << COLOR_RESET << "\n";
    
    // Mostrar la palabra de derecha a izquierda
    cout << COLOR_INVERSE << "   Inversa: ";
    for(int i = longitud-1; i >= 0; i--) {
        cout << palabraLimpia[i] << " ";
    }
    cout << COLOR_RESET << "\n";
    
    // Mostrar verificación carácter por carácter
    mostrarAnimacionVerificacion(palabraLimpia, esPalindromo);
    
    // Mostrar el resultado final
    cout << "\n" << COLOR_HIGHLIGHT << "📌 CONCLUSIÓN: " << COLOR_RESET;
    if(esPalindromo) {
        cout << COLOR_MATCH << "✅ \"" << palabra << "\" SÍ es un palíndromo!" << COLOR_RESET << "\n\n";
    } else {
        cout << COLOR_MISMATCH << "❌ \"" << palabra << "\" NO es un palíndromo." << COLOR_RESET << "\n\n";
    }
    
    // Añadir instrucciones finales
    cout << "Presione Enter para finalizar...";
    cin.get();
    
    return 0;
} 
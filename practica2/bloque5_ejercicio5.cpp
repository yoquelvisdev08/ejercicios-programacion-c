/*
 * 🔍 MAYOR ELEMENTO DEL VECTOR 🔍
 * =============================
 *
 * Bloque 5: Ejercicio 5
 * --------------------
 * Programa que lee de la entrada estándar un vector de enteros y
 * determina el mayor elemento del vector.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <iomanip>
#include <limits>  // Para usar INT_MIN
using namespace std;

// Constantes para colores (ANSI escape codes)
const string COLOR_RESET = "\033[0m";
const string COLOR_TITLE = "\033[1;36m";  // Cyan brillante
const string COLOR_HIGHLIGHT = "\033[1;33m";  // Amarillo brillante
const string COLOR_INPUT = "\033[1;32m";  // Verde brillante
const string COLOR_VECTOR = "\033[1;34m";  // Azul brillante
const string COLOR_MAX = "\033[1;31m";  // Rojo brillante
const string COLOR_RESULT = "\033[1;35m";  // Magenta brillante

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
    cout << "║      MAYOR ELEMENTO DEL VECTOR    ║\n";
    cout << "╚═══════════════════════════════════╝\n\n" << COLOR_RESET;
}

// Función para mostrar un vector con formato mejorado
void mostrarVector(const int vector[], int tamanio, int posicionMayor) {
    cout << COLOR_HIGHLIGHT << "\n📊 Vector ingresado:" << COLOR_RESET << endl;
    
    // Línea superior del vector
    cout << COLOR_VECTOR << "┌";
    for(int i = 0; i < tamanio; i++) {
        cout << "──────";
        if(i < tamanio-1) cout << "┬";
    }
    cout << "┐\n";
    
    // Índices del vector
    cout << "│";
    for(int i = 0; i < tamanio; i++) {
        cout << " [" << setw(2) << i << "] ";
        if(i < tamanio-1) cout << "│";
    }
    cout << "│\n";
    
    // Línea separadora
    cout << "├";
    for(int i = 0; i < tamanio; i++) {
        cout << "──────";
        if(i < tamanio-1) cout << "┼";
    }
    cout << "┤\n";
    
    // Valores del vector (resaltando el mayor)
    cout << "│";
    for(int i = 0; i < tamanio; i++) {
        if(i == posicionMayor) {
            cout << COLOR_MAX; // Resaltar el valor máximo
        }
        cout << " " << setw(4) << vector[i] << " ";
        if(i == posicionMayor) {
            cout << COLOR_VECTOR; // Volver al color del vector
        }
        if(i < tamanio-1) cout << "│";
    }
    cout << "│\n";
    
    // Línea inferior del vector
    cout << "└";
    for(int i = 0; i < tamanio; i++) {
        cout << "──────";
        if(i < tamanio-1) cout << "┴";
    }
    cout << "┘" << COLOR_RESET << "\n";
    
    // Indicador del valor máximo
    for(int i = 0; i < tamanio; i++) {
        if(i == posicionMayor) {
            int espacios = i * 7 + 2; // Calcular espacios para alinear la flecha
            cout << setw(espacios) << " " << COLOR_MAX << "↑\n";
            cout << setw(espacios) << " " << "MÁXIMO" << COLOR_RESET << "\n";
            break;
        }
    }
}

// Función para mostrar el proceso de búsqueda del mayor elemento
void mostrarProcesoBusqueda(const int vector[], int tamanio, int mayor, int posicion) {
    cout << COLOR_HIGHLIGHT << "\n🔍 Análisis del vector:" << COLOR_RESET << endl;
    
    // Tabla de análisis
    cout << "┌────────┬─────────┬────────────────┐\n";
    cout << "│ Índice │  Valor  │    Estado      │\n";
    cout << "├────────┼─────────┼────────────────┤\n";
    
    for(int i = 0; i < tamanio; i++) {
        cout << "│ " << setw(6) << i << " │ " << setw(7) << vector[i] << " │ ";
        
        if(i == 0) {
            cout << "Primer valor    │\n";
        } else if(vector[i] > vector[posicion] && i != posicion) {
            cout << "Nuevo máximo    │\n";
        } else if(i == posicion) {
            cout << COLOR_MAX << "VALOR MÁXIMO    " << COLOR_RESET << "│\n";
        } else {
            cout << "Menor que máximo│\n";
        }
    }
    
    cout << "└────────┴─────────┴────────────────┘\n";
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaracion de variables
    const int MAX = 100;  // Tamaño máximo del vector
    int numeros[MAX];     // Vector de números
    int n;                // Tamaño real del vector
    int mayor = numeric_limits<int>::min(); // Inicializamos con el menor valor posible
    int posicion = 0;     // Posición del mayor elemento
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa encuentra el mayor elemento\n";
    cout << "               dentro de un vector de números enteros.\n\n";
    
    // Solicitar el tamaño del vector
    do {
        cout << COLOR_HIGHLIGHT << "📏 Ingrese el tamaño del vector (1-" << MAX << "): " << COLOR_INPUT;
        cin >> n;
        cout << COLOR_RESET;
        
        if(n <= 0 || n > MAX) {
            cout << "\n⚠️  Error: El tamaño debe estar entre 1 y " << MAX << ".\n\n";
        }
    } while(n <= 0 || n > MAX);
    
    cout << "\n"; // Salto de línea entre inputs
    
    // Solicitar los elementos del vector
    cout << COLOR_HIGHLIGHT << "🔢 Ingrese los elementos del vector:\n";
    cout << "==================================\n" << COLOR_RESET;
    
    for(int i = 0; i < n; i++) {
        cout << COLOR_HIGHLIGHT << "   Elemento [" << i << "]: " << COLOR_INPUT;
        cin >> numeros[i];
        cout << COLOR_RESET;
        
        // Verificar si el número actual es mayor
        if(numeros[i] > mayor) {
            mayor = numeros[i];
            posicion = i;
        }
    }
    
    // Mostrar el vector completo con formato mejorado, destacando el mayor
    mostrarVector(numeros, n, posicion);
    
    // Mostrar el proceso de búsqueda
    mostrarProcesoBusqueda(numeros, n, mayor, posicion);
    
    // Mostrar el resultado
    cout << "\n" << COLOR_HIGHLIGHT << "🔍 Resultado del análisis:" << COLOR_RESET << endl;
    cout << COLOR_RESULT << "✅ El mayor elemento es " << mayor << " (ubicado en la posición " << posicion << ")" << COLOR_RESET << "\n\n";
    
    // Añadir instrucciones finales
    cout << "Presione Enter para finalizar...";
    cin.ignore();
    cin.get();
    
    return 0;
} 
} 
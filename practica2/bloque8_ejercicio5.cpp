/*
 * 📚 SISTEMA DE GESTIÓN DE CALIFICACIONES 📚
 * ======================================
 * 
 * Bloque 8: Ejercicio 5
 * --------------------
 * Programa con 2 estructuras: una llamada promedio que tiene los campos nota1, nota2, nota3;
 * y otra llamada alumno que tiene los campos nombre, sexo, edad; hace que la estructura
 * promedio esté anidada en la estructura alumno, pide todos los datos para un alumno,
 * calcula su promedio, y por último imprime todos sus datos incluido el promedio.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;

// Constantes para colores (ANSI escape codes)
const string COLOR_RESET = "\033[0m";
const string COLOR_TITLE = "\033[1;36m";  // Cyan brillante
const string COLOR_HIGHLIGHT = "\033[1;33m";  // Amarillo brillante
const string COLOR_INPUT = "\033[1;32m";  // Verde brillante
const string COLOR_INFO = "\033[1;34m";  // Azul brillante
const string COLOR_ERROR = "\033[1;31m";  // Rojo brillante
const string COLOR_RESULT = "\033[1;35m";  // Magenta brillante

// Definición de la estructura Promedio
struct Promedio {
    float nota1;
    float nota2;
    float nota3;
    float promedio_final; // Para almacenar el promedio calculado
};

// Definición de la estructura Alumno con Promedio anidado
struct Alumno {
    char nombre[50];
    char sexo[10];
    int edad;
    Promedio calificaciones; // Estructura anidada
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
    cout << "║    SISTEMA DE GESTIÓN ACADÉMICA       ║\n";
    cout << "╚═══════════════════════════════════════╝\n\n" << COLOR_RESET;
}

// Función para validar una nota (0-10)
float pedirNota(const char* mensaje) {
    float nota;
    bool valido = false;
    
    do {
        cout << COLOR_HIGHLIGHT << mensaje << COLOR_INPUT;
        cin >> nota;
        cout << COLOR_RESET;
        
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << COLOR_ERROR << "⚠️ Error: Debe ingresar un número válido.\n\n" << COLOR_RESET;
        }
        else if(nota < 0 || nota > 10) {
            cout << COLOR_ERROR << "⚠️ Error: La nota debe estar entre 0 y 10.\n\n" << COLOR_RESET;
        }
        else {
            valido = true;
        }
    } while(!valido);
    
    return nota;
}

// Función para mostrar el nivel académico según el promedio
string obtenerNivelAcademico(float promedio) {
    if(promedio >= 9.0) return "Excelente 🏆";
    else if(promedio >= 8.0) return "Muy Bueno 🥇";
    else if(promedio >= 7.0) return "Bueno 🥈";
    else if(promedio >= 6.0) return "Aprobado 🥉";
    else return "Reprobado ❌";
}

// Función para mostrar un gráfico de barras para el promedio
void mostrarGraficoPromedio(float promedio) {
    int longitud = (int)(promedio * 3); // 3 caracteres por unidad
    
    cout << COLOR_INFO << "   [";
    for(int i = 0; i < 30; i++) {
        if(i < longitud) {
            if(promedio < 6) cout << COLOR_ERROR << "█";
            else if(promedio < 8) cout << COLOR_HIGHLIGHT << "█";
            else cout << COLOR_RESULT << "█";
        } else {
            cout << COLOR_INFO << "░";
        }
    }
    cout << COLOR_INFO << "] " << setprecision(2) << fixed << promedio << "/10.0" << COLOR_RESET << "\n\n";
}

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaración de variables
    Alumno alumno1;
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa registra los datos académicos de un alumno,\n";
    cout << "               calcula su promedio y muestra su nivel de desempeño.\n\n";
    
    // Pedir datos del alumno con formato mejorado
    cout << COLOR_HIGHLIGHT << "👤 DATOS PERSONALES DEL ALUMNO\n";
    cout << "===========================\n" << COLOR_RESET;
    
    cout << COLOR_HIGHLIGHT << "📝 Nombre: " << COLOR_INPUT;
    cin.getline(alumno1.nombre, 50, '\n');
    cout << COLOR_RESET;
    
    cout << "\n"; // Salto de línea entre inputs
    
    cout << COLOR_HIGHLIGHT << "⚧ Sexo (Masculino/Femenino): " << COLOR_INPUT;
    cin.getline(alumno1.sexo, 10, '\n');
    cout << COLOR_RESET;
    
    cout << "\n"; // Salto de línea entre inputs
    
    // Validar la edad
    do {
        cout << COLOR_HIGHLIGHT << "🎂 Edad: " << COLOR_INPUT;
        cin >> alumno1.edad;
        cout << COLOR_RESET;
        
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << COLOR_ERROR << "⚠️ Error: Debe ingresar un número válido.\n\n" << COLOR_RESET;
        }
        else if(alumno1.edad <= 0 || alumno1.edad > 120) {
            cout << COLOR_ERROR << "⚠️ Error: La edad debe estar entre 1 y 120 años.\n\n" << COLOR_RESET;
        }
    } while(alumno1.edad <= 0 || alumno1.edad > 120 || cin.fail());
    
    cin.ignore(); // Limpiar buffer
    
    // Pedir las notas con mejor formato y validación
    cout << "\n" << COLOR_HIGHLIGHT << "📊 CALIFICACIONES DEL ALUMNO\n";
    cout << "===========================\n" << COLOR_RESET;
    
    alumno1.calificaciones.nota1 = pedirNota("📝 Nota 1: ");
    cout << "\n"; // Salto de línea entre inputs
    
    alumno1.calificaciones.nota2 = pedirNota("📝 Nota 2: ");
    cout << "\n"; // Salto de línea entre inputs
    
    alumno1.calificaciones.nota3 = pedirNota("📝 Nota 3: ");
    
    // Calcular el promedio
    alumno1.calificaciones.promedio_final = (alumno1.calificaciones.nota1 +
                                           alumno1.calificaciones.nota2 +
                                           alumno1.calificaciones.nota3) / 3;
    
    // Limpiar pantalla y mostrar los datos con formato mejorado
    limpiarPantalla();
    mostrarBanner();
    
    // Mostrar los datos del alumno con formato mejorado
    cout << COLOR_HIGHLIGHT << "📊 FICHA ACADÉMICA DEL ALUMNO\n";
    cout << "===========================\n\n" << COLOR_RESET;
    
    cout << setfill(' ') << fixed << setprecision(2);
    cout << COLOR_INFO << "┌───────────────────────────────────────┐\n";
    cout << "│           DATOS PERSONALES             │\n";
    cout << "├───────────────────────────────────────┤\n";
    cout << "│ " << left << setw(15) << "Nombre:" << left << setw(24) << alumno1.nombre << "│\n";
    cout << "│ " << left << setw(15) << "Sexo:" << left << setw(24) << alumno1.sexo << "│\n";
    cout << "│ " << left << setw(15) << "Edad:" << left << setw(22) << (to_string(alumno1.edad) + " años") << "│\n";
    cout << "├───────────────────────────────────────┤\n";
    cout << "│           CALIFICACIONES              │\n";
    cout << "├───────────────────────────────────────┤\n";
    cout << "│ " << left << setw(15) << "Nota 1:" << left << setw(24) << alumno1.calificaciones.nota1 << "│\n";
    cout << "│ " << left << setw(15) << "Nota 2:" << left << setw(24) << alumno1.calificaciones.nota2 << "│\n";
    cout << "│ " << left << setw(15) << "Nota 3:" << left << setw(24) << alumno1.calificaciones.nota3 << "│\n";
    cout << "├───────────────────────────────────────┤\n";
    cout << "│           RESULTADO FINAL             │\n";
    cout << "├───────────────────────────────────────┤\n";
    cout << "│ " << left << setw(15) << "Promedio:" << left << setw(24) << alumno1.calificaciones.promedio_final << "│\n";
    cout << "│ " << left << setw(15) << "Nivel:" << left << setw(24) << obtenerNivelAcademico(alumno1.calificaciones.promedio_final) << "│\n";
    cout << "└───────────────────────────────────────┘" << COLOR_RESET << "\n\n";
    
    // Mostrar gráfico del promedio
    cout << COLOR_HIGHLIGHT << "📈 REPRESENTACIÓN GRÁFICA DEL PROMEDIO:\n" << COLOR_RESET;
    mostrarGraficoPromedio(alumno1.calificaciones.promedio_final);
    
    // Añadir mensaje final
    cout << COLOR_HIGHLIGHT << "✨ Registro académico completado con éxito ✨\n\n" << COLOR_RESET;
    
    // Añadir instrucciones finales
    cout << "Presione Enter para finalizar...";
    cin.get();
    
    return 0;
} 
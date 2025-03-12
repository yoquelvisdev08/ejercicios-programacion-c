/*
 * 🏆 SISTEMA DE RANKING ACADÉMICO 🏆
 * ==============================
 * 
 * Bloque 8: Ejercicio 6
 * --------------------
 * Programa que utiliza las 2 estructuras del problema 5, pero ahora pide datos
 * para N alumnos, calcula cuál de todos tiene el mejor promedio, e imprime sus datos.
 *
 * Autor: Yoquelvis Abreu
 * Fecha: Marzo 2024
 */

#include <iostream>
#include <string.h>
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
    cout << "║       SISTEMA DE RANKING ACADÉMICO    ║\n";
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

int main() {
    // Limpiar pantalla y mostrar banner
    limpiarPantalla();
    mostrarBanner();
    
    // Declaración de variables
    int n; // Cantidad de alumnos
    Alumno *alumnos; // Arreglo dinámico para almacenar los alumnos
    int pos_mejor = 0; // Posición del alumno con mejor promedio
    float mejor_promedio = 0; // Para almacenar el mejor promedio
    
    // Explicación del programa
    cout << "📋 DESCRIPCIÓN: Este programa registra los datos académicos de varios alumnos,\n";
    cout << "               calcula sus promedios y muestra el alumno con mejor desempeño.\n\n";
    
    // Pedir cantidad de alumnos con validación
    do {
        cout << COLOR_HIGHLIGHT << "👥 Ingrese el número de alumnos a registrar: " << COLOR_INPUT;
        cin >> n;
        cout << COLOR_RESET;
        
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << COLOR_ERROR << "⚠️ Error: Debe ingresar un número válido.\n\n" << COLOR_RESET;
        }
        else if(n <= 0) {
            cout << COLOR_ERROR << "⚠️ Error: Debe registrar al menos un alumno.\n\n" << COLOR_RESET;
        }
    } while(n <= 0 || cin.fail());
    
    // Crear el arreglo dinámico para los alumnos
    alumnos = new Alumno[n];
    
    // Pedir datos para cada alumno
    for(int i = 0; i < n; i++) {
        // Limpiar pantalla y mostrar banner para cada alumno
        limpiarPantalla();
        mostrarBanner();
        
        cout << COLOR_HIGHLIGHT << "👤 REGISTRO DE DATOS: ALUMNO " << (i+1) << " DE " << n << "\n";
        cout << "===================================\n" << COLOR_RESET;
        
        cin.ignore(i == 0 ? 1 : 10000, '\n'); // Limpiar buffer adecuadamente
        
        // Datos personales
        cout << COLOR_INFO << "📝 DATOS PERSONALES\n" << COLOR_RESET;
        
        cout << COLOR_HIGHLIGHT << "   Nombre: " << COLOR_INPUT;
        cin.getline(alumnos[i].nombre, 50, '\n');
        cout << COLOR_RESET;
        
        cout << "\n"; // Salto de línea entre inputs
        
        cout << COLOR_HIGHLIGHT << "   Sexo (Masculino/Femenino): " << COLOR_INPUT;
        cin.getline(alumnos[i].sexo, 10, '\n');
        cout << COLOR_RESET;
        
        cout << "\n"; // Salto de línea entre inputs
        
        // Validar la edad
        do {
            cout << COLOR_HIGHLIGHT << "   Edad: " << COLOR_INPUT;
            cin >> alumnos[i].edad;
            cout << COLOR_RESET;
            
            if(cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << COLOR_ERROR << "   ⚠️ Error: Debe ingresar un número válido.\n\n" << COLOR_RESET;
            }
            else if(alumnos[i].edad <= 0 || alumnos[i].edad > 120) {
                cout << COLOR_ERROR << "   ⚠️ Error: La edad debe estar entre 1 y 120 años.\n\n" << COLOR_RESET;
            }
        } while(alumnos[i].edad <= 0 || alumnos[i].edad > 120 || cin.fail());
        
        // Pedir las notas con mejor formato y validación
        cout << "\n" << COLOR_INFO << "📚 CALIFICACIONES\n" << COLOR_RESET;
        
        alumnos[i].calificaciones.nota1 = pedirNota("   Nota 1: ");
        cout << "\n"; // Salto de línea entre inputs
        
        alumnos[i].calificaciones.nota2 = pedirNota("   Nota 2: ");
        cout << "\n"; // Salto de línea entre inputs
        
        alumnos[i].calificaciones.nota3 = pedirNota("   Nota 3: ");
        
        // Calcular el promedio
        alumnos[i].calificaciones.promedio_final = (alumnos[i].calificaciones.nota1 +
                                                 alumnos[i].calificaciones.nota2 +
                                                 alumnos[i].calificaciones.nota3) / 3;
        
        // Verificar si este alumno tiene mejor promedio
        if(alumnos[i].calificaciones.promedio_final > mejor_promedio) {
            mejor_promedio = alumnos[i].calificaciones.promedio_final;
            pos_mejor = i;
        }
        
        // Mostrar progreso
        mostrarProgreso(i + 1, n);
        
        // Mensaje de confirmación
        cout << COLOR_SUCCESS << "✅ Datos del alumno " << (i+1) << " registrados con éxito.\n" << COLOR_RESET;
        
        if(i < n-1) {
            cout << "\nPresione Enter para continuar con el siguiente alumno...";
            cin.ignore(10000, '\n');
            cin.get();
        }
    }
    
    // Limpiar pantalla y mostrar resultados
    limpiarPantalla();
    mostrarBanner();
    
    // Mostrar los datos del alumno con mejor promedio con formato mejorado
    cout << COLOR_HIGHLIGHT << "🏆 ALUMNO CON MEJOR PROMEDIO\n";
    cout << "============================\n\n" << COLOR_RESET;
    
    cout << setfill(' ') << fixed << setprecision(2);
    cout << COLOR_INFO << "┌───────────────────────────────────────┐\n";
    cout << "│           DATOS PERSONALES             │\n";
    cout << "├───────────────────────────────────────┤\n";
    cout << "│ " << left << setw(15) << "Nombre:" << left << setw(24) << alumnos[pos_mejor].nombre << "│\n";
    cout << "│ " << left << setw(15) << "Sexo:" << left << setw(24) << alumnos[pos_mejor].sexo << "│\n";
    cout << "│ " << left << setw(15) << "Edad:" << left << setw(22) << (to_string(alumnos[pos_mejor].edad) + " años") << "│\n";
    cout << "├───────────────────────────────────────┤\n";
    cout << "│           CALIFICACIONES              │\n";
    cout << "├───────────────────────────────────────┤\n";
    cout << "│ " << left << setw(15) << "Nota 1:" << left << setw(24) << alumnos[pos_mejor].calificaciones.nota1 << "│\n";
    cout << "│ " << left << setw(15) << "Nota 2:" << left << setw(24) << alumnos[pos_mejor].calificaciones.nota2 << "│\n";
    cout << "│ " << left << setw(15) << "Nota 3:" << left << setw(24) << alumnos[pos_mejor].calificaciones.nota3 << "│\n";
    cout << "├───────────────────────────────────────┤\n";
    cout << "│           RESULTADO FINAL             │\n";
    cout << "├───────────────────────────────────────┤\n";
    cout << "│ " << left << setw(15) << "Promedio:" << left << setw(24) << alumnos[pos_mejor].calificaciones.promedio_final << "│\n";
    cout << "│ " << left << setw(15) << "Nivel:" << left << setw(24) << obtenerNivelAcademico(alumnos[pos_mejor].calificaciones.promedio_final) << "│\n";
    cout << "└───────────────────────────────────────┘" << COLOR_RESET << "\n\n";
    
    // Mostrar gráfico del promedio
    cout << COLOR_HIGHLIGHT << "📈 REPRESENTACIÓN GRÁFICA DEL PROMEDIO:\n" << COLOR_RESET;
    mostrarGraficoPromedio(alumnos[pos_mejor].calificaciones.promedio_final);
    
    // Añadir mensaje de felicitación
    cout << COLOR_SUCCESS << "🏆 ¡Felicitaciones a " << alumnos[pos_mejor].nombre << " por obtener el mejor promedio!\n\n" << COLOR_RESET;
    
    // Resumen de todos los alumnos (tabla)
    cout << COLOR_HIGHLIGHT << "📊 RESUMEN DE TODOS LOS ALUMNOS:\n";
    cout << "===============================\n\n" << COLOR_RESET;
    
    cout << COLOR_INFO << "┌───────┬─────────────────────┬───────┬──────────┬──────────┐\n";
    cout << "│ NUM   │ NOMBRE              │ EDAD  │ PROMEDIO  │ NIVEL     │\n";
    cout << "├───────┼─────────────────────┼───────┼──────────┼──────────┤" << COLOR_RESET << "\n";
    
    for(int i = 0; i < n; i++) {
        cout << "│ " << setw(5) << left << (i+1) << " │ ";
        cout << setw(19) << left << alumnos[i].nombre << " │ ";
        cout << setw(5) << left << alumnos[i].edad << " │ ";
        cout << setw(8) << left << fixed << setprecision(2) << alumnos[i].calificaciones.promedio_final << " │ ";
        
        // Destacar al mejor alumno
        if(i == pos_mejor) {
            cout << COLOR_SUCCESS << setw(8) << left << "🏆 MEJOR" << COLOR_RESET << " │\n";
        } else {
            cout << setw(10) << " " << "│\n";
        }
    }
    
    cout << COLOR_INFO << "└───────┴─────────────────────┴───────┴──────────┴──────────┘" << COLOR_RESET << "\n\n";
    
    // Liberar memoria
    delete[] alumnos;
    
    // Añadir instrucciones finales
    cout << "Presione Enter para finalizar...";
    cin.ignore(10000, '\n');
    cin.get();
    
    return 0;
} 
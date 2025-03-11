#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<iomanip>
#include<string.h>
#include<limits>

using namespace std;

struct alumno
{
    // Campos
    char nombre[20];
    char apellido[20];
    char carnet[9];
    float nota_periodo1;
    float nota_periodo2;
    float nota_periodo3;
    float nota_ciclo;

    // Funciones
    void calcular_nota_final(void) {
        // Determina nota final de la materia cursada
        // Operan a los campos de la estructura
        nota_ciclo = (nota_periodo1 * 0.3) + (nota_periodo2 * 0.35) + (nota_periodo3 * 0.35);
    } // Fin función nota_final_ciclo
}; // Fin definición del struct alumno

// Función para validar que una nota esté entre 0 y 10
float validar_nota(const char* periodo) {
    float nota;
    bool notaValida = false;
    
    while (!notaValida) {
        cout << "\nNota del periodo " << periodo << " (0-10)? ";
        
        // Verificar que la entrada sea un número
        if (cin >> nota) {
            // Verificar que la nota esté en el rango correcto
            if (nota >= 0 && nota <= 10) {
                notaValida = true;
            } else {
                cout << "Error: La nota debe estar entre 0 y 10. Intente de nuevo." << endl;
            }
        } else {
            // Limpiar el buffer de entrada en caso de error
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Debe ingresar un valor numérico. Intente de nuevo." << endl;
        }
    }
    
    return nota;
}

// Función para leer cadenas con espacios de forma segura
void leer_cadena(char* destino, int tamano, const char* prompt) {
    cout << prompt;
    cin.ignore(); // Para ignorar el salto de línea anterior si existe
    cin.getline(destino, tamano);
}

int main() {
    alumno alumno1; // Creando una variable de tipo estructura alumno
    
    cout << "\n==============================================" << endl;
    cout << "   CÁLCULO DE NOTA FINAL DE EXPRESIÓN ORAL   " << endl;
    cout << "==============================================" << endl;
    
    cout << "\nIngrese los siguientes datos del estudiante:";
    
    // Lectura segura de datos del estudiante
    leer_cadena(alumno1.nombre, 20, "\nNombre? ");
    leer_cadena(alumno1.apellido, 20, "\nApellido? ");
    leer_cadena(alumno1.carnet, 9, "\nCarnet? ");
    
    cout << "\n-> Ahora digite cada una de las 3 notas del periodo:" << endl;
    
    // Validación de notas
    alumno1.nota_periodo1 = validar_nota("1");
    alumno1.nota_periodo2 = validar_nota("2");
    alumno1.nota_periodo3 = validar_nota("3");
    
    // Llama a la función de la struct
    alumno1.calcular_nota_final();
    
    system("cls"); // Limpiar pantalla
    
    cout << "\t-----------------------------------------------------------" << endl;
    cout << "\t-             INFORME DE RESULTADOS                      -" << endl;
    cout << "\t-----------------------------------------------------------" << endl;
    cout << "\t Nombre del alumno: " << alumno1.nombre << " " << alumno1.apellido << endl;
    cout << "\t Carnet: " << alumno1.carnet << endl;
    cout << "\t Notas por periodo:" << endl;
    cout << fixed << setprecision(2);
    cout << "\t   Periodo 1 (30%): " << alumno1.nota_periodo1 << endl;
    cout << "\t   Periodo 2 (35%): " << alumno1.nota_periodo2 << endl;
    cout << "\t   Periodo 3 (35%): " << alumno1.nota_periodo3 << endl;
    cout << "\t Nota final del ciclo: " << alumno1.nota_ciclo << endl;
    
    if (alumno1.nota_ciclo >= 6)
        cout << "\t Estado: Aprobado" << endl;
    else
        cout << "\t Estado: Reprobado" << endl;
    
    cout << "\t-----------------------------------------------------------" << endl;
    
    system("PAUSE");
    return 0;
} // Fin función principal 
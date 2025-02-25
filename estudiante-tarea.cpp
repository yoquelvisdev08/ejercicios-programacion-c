#include <iostream>
#include <string.h>
using namespace std;

struct Estudiante {
    char nombre[50];
    char apellido[50];
    int edad;
    char carrera[30];
    float promedio;
    
    struct Asignatura {
        char nombre[30];
        char escuela[50];
        int creditos;
        float calificacion;
    } asignaturas[5];  // Arreglo de 5 asignaturas dentro de la estructura Estudiante
};

int main() {
    Estudiante estudiantes[10];  // Arreglo de 10 estudiantes
    int numEstudiantes;
    
    cout << "Ingrese el numero de estudiantes (max 10): ";
    cin >> numEstudiantes;
    cin.ignore();
    
    // Ingreso de datos
    for(int i = 0; i < numEstudiantes; i++) {
        cout << "\n--- Estudiante " << i + 1 << " ---\n";
        cout << "Nombre: ";
        cin.getline(estudiantes[i].nombre, 50);
        
        cout << "Apellido: ";
        cin.getline(estudiantes[i].apellido, 50);
        
        cout << "Edad: ";
        cin >> estudiantes[i].edad;
        cin.ignore();
        
        cout << "Carrera: ";
        cin.getline(estudiantes[i].carrera, 30);
        
        int numAsignaturas;
        cout << "Numero de asignaturas (max 5): ";
        cin >> numAsignaturas;
        cin.ignore();
        
        float sumaCalificaciones = 0;
        
        // Ingreso de asignaturas
        for(int j = 0; j < numAsignaturas; j++) {
            cout << "\nAsignatura " << j + 1 << ":\n";
            cout << "Nombre de la asignatura: ";
            cin.getline(estudiantes[i].asignaturas[j].nombre, 30);
            
            cout << "Escuela: ";
            cin.getline(estudiantes[i].asignaturas[j].escuela, 50);
            
            cout << "Creditos: ";
            cin >> estudiantes[i].asignaturas[j].creditos;
            
            cout << "Calificacion: ";
            cin >> estudiantes[i].asignaturas[j].calificacion;
            cin.ignore();
            
            sumaCalificaciones += estudiantes[i].asignaturas[j].calificacion;
        }
        
        estudiantes[i].promedio = sumaCalificaciones / numAsignaturas;
    }
    
    // Mostrar información
    cout << "\n=== INFORMACIÓN DE ESTUDIANTES ===\n";
    for(int i = 0; i < numEstudiantes; i++) {
        cout << "\nEstudiante " << i + 1 << ":";
        cout << "\nNombre completo: " << estudiantes[i].nombre << " " << estudiantes[i].apellido;
        cout << "\nEdad: " << estudiantes[i].edad;
        cout << "\nCarrera: " << estudiantes[i].carrera;
        cout << "\nPromedio general: " << estudiantes[i].promedio;
        cout << "\n\nAsignaturas cursadas:";
        
        for(int j = 0; j < 5; j++) {
            if(estudiantes[i].asignaturas[j].nombre[0] != '\0') {
                cout << "\n- " << estudiantes[i].asignaturas[j].nombre;
                cout << " (Escuela: " << estudiantes[i].asignaturas[j].escuela << ")";
                cout << "\n  Creditos: " << estudiantes[i].asignaturas[j].creditos;
                cout << "\n  Calificacion: " << estudiantes[i].asignaturas[j].calificacion;
            }
        }
        cout << "\n------------------------\n";
    }
    
    return 0;
} 
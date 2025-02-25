#include <iostream>
#include <string.h>
using namespace std;

struct Estudiante {
    char nombre[50];          // Límite de 50 caracteres
    char carrera[30];         // Límite de 30 caracteres
    char asignatura[20];      // Límite de 20 caracteres
    float calificacion;       // Calificación numérica
    char grado[10];          // Límite de 10 caracteres
};

int main() {
    Estudiante estudiante1;
    
    cout << "Ingrese nombre del estudiante: ";
    cin.getline(estudiante1.nombre, 50);
    
    cout << "Ingrese carrera: ";
    cin.getline(estudiante1.carrera, 30);
    
    cout << "Ingrese asignatura: ";
    cin.getline(estudiante1.asignatura, 20);
    
    cout << "Ingrese calificacion: ";
    cin >> estudiante1.calificacion;
    cin.ignore();  // Limpiar el buffer
    
    cout << "Ingrese grado: ";
    cin.getline(estudiante1.grado, 10);
    
    // Mostrar los datos
    cout << "\n--- Datos del Estudiante ---\n";
    cout << "Nombre: " << estudiante1.nombre << endl;
    cout << "Carrera: " << estudiante1.carrera << endl;
    cout << "Asignatura: " << estudiante1.asignatura << endl;
    cout << "Calificacion: " << estudiante1.calificacion << endl;
    cout << "Grado: " << estudiante1.grado << endl;
    
    return 0;
} 
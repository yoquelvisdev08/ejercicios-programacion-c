#include <iostream>
using namespace std;

// Estructura para almacenar los datos de cada alumno
struct Alumno {
    int nro;            // Número de alumno (1-12000)
    float notas[4];     // Array para las 4 notas de parciales
};

int main() {
    // Declaración de variables
    Alumno alumnos[30];  // Array para almacenar los 30 alumnos
    int NRO;             // Número de alumno a buscar
    int inf = 0;         // Límite inferior para búsqueda
    int sup = 29;        // Límite superior para búsqueda
    int med;             // Punto medio para búsqueda
    bool encontrado = false;
    
    // 1. Ingreso de datos de alumnos
    cout << "Ingrese los datos de 30 alumnos en orden creciente por número:\n";
    for(int i = 0; i < 30; i++) {
        do {
            cout << "\nAlumno " << (i+1) << ":\n";
            cout << "Número de alumno (1-12000): ";
            cin >> alumnos[i].nro;
            
            // Validación del número de alumno
            if(alumnos[i].nro < 1 || alumnos[i].nro > 12000) {
                cout << "Error: El número debe estar entre 1 y 12000.\n";
                continue;
            }
            
            // Validación del orden creciente
            if(i > 0 && alumnos[i].nro <= alumnos[i-1].nro) {
                cout << "Error: Debe ser mayor que " << alumnos[i-1].nro << ".\n";
                continue;
            }
            
            // Ingreso de las 4 notas
            for(int j = 0; j < 4; j++) {
                do {
                    cout << "Nota del parcial " << (j+1) << " (0-10): ";
                    cin >> alumnos[i].notas[j];
                    if(alumnos[i].notas[j] < 0 || alumnos[i].notas[j] > 10) {
                        cout << "Error: La nota debe estar entre 0 y 10.\n";
                    }
                } while(alumnos[i].notas[j] < 0 || alumnos[i].notas[j] > 10);
            }
            break;
            
        } while(true);
    }
    
    // 2. Búsqueda de alumno
    cout << "\nIngrese el número de alumno a buscar: ";
    cin >> NRO;
    
    // Búsqueda dicotómica
    while(inf <= sup && !encontrado) {
        med = (inf + sup) / 2;
        
        if(NRO == alumnos[med].nro) {
            encontrado = true;
        } else if(NRO < alumnos[med].nro) {
            sup = med - 1;
        } else {
            inf = med + 1;
        }
    }
    
    // 3. Mostrar resultados
    if(encontrado) {
        cout << "\nAlumno encontrado!\n";
        cout << "Número de alumno: " << alumnos[med].nro << endl;
        cout << "Notas de parciales:\n";
        for(int i = 0; i < 4; i++) {
            cout << "Parcial " << (i+1) << ": " << alumnos[med].notas[i] << endl;
        }
    } else {
        cout << "\nERROR EN NRO ALUMNO\n";
        cout << "No se encontró ningún alumno con el número " << NRO << endl;
    }
    
    return 0;
} 
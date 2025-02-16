#include <iostream>
using namespace std;

int main() {
    // Declaración de variables
    int vec[30];  // Vector para almacenar los 30 números
    int N;        // Número a buscar
    int inf = 0;  // Límite inferior del rango de búsqueda
    int sup = 29; // Límite superior del rango de búsqueda
    int med;      // Punto medio del rango actual
    bool encontrado = false;
    
    // 1. Ingreso de datos - Vector ordenado en forma creciente
    cout << "Ingrese 30 números enteros en orden creciente:\n";
    for(int i = 0; i < 30; i++) {
        do {
            cout << "Número " << (i+1) << ": ";
            cin >> vec[i];
            
            // Validación del orden creciente
            if(i > 0 && vec[i] <= vec[i-1]) {
                cout << "Error: Debe ser mayor que " << vec[i-1] << ". Intente nuevamente.\n";
            }
        } while(i > 0 && vec[i] <= vec[i-1]);
    }
    
    // 2. Ingreso del número a buscar
    cout << "\nIngrese el número N a buscar: ";
    cin >> N;
    
    // 3. Búsqueda binaria
    while(inf <= sup && !encontrado) {
        med = (inf + sup) / 2;  // Calculamos el punto medio
        
        if(N == vec[med]) {
            encontrado = true;
        } else if(N < vec[med]) {
            sup = med - 1;  // Buscamos en la mitad inferior
        } else {
            inf = med + 1;  // Buscamos en la mitad superior
        }
    }
    
    // 4. Mostrar resultado
    if(encontrado) {
        cout << "\nEl número " << N << " fue encontrado en la posición " << (med + 1) << endl;
    } else {
        cout << "\nNo se encontró el número " << N << " en el arreglo." << endl;
    }
    
    return 0;
} 
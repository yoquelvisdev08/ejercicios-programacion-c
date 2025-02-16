#include <iostream>
using namespace std;

int main() {
    // Declaración de arreglos
    int V1[10];    // Primer arreglo de 10 elementos
    int V2[13];    // Segundo arreglo de 13 elementos
    int V3[23];    // Arreglo resultado de 23 elementos
    int I = 0;     // Índice para V1
    int J = 0;     // Índice para V2
    int K = 0;     // Índice para V3
    
    // 1. Ingreso del primer arreglo (10 elementos)
    cout << "Ingrese 10 números enteros en orden creciente:\n";
    for(int i = 0; i < 10; i++) {
        do {
            cout << "V1[" << i << "]: ";
            cin >> V1[i];
            
            // Validación del orden creciente
            if(i > 0 && V1[i] <= V1[i-1]) {
                cout << "Error: Debe ser mayor que " << V1[i-1] << ". Intente nuevamente.\n";
            }
        } while(i > 0 && V1[i] <= V1[i-1]);
    }
    
    // 2. Ingreso del segundo arreglo (13 elementos)
    cout << "\nIngrese 13 números enteros en orden creciente:\n";
    for(int i = 0; i < 13; i++) {
        do {
            cout << "V2[" << i << "]: ";
            cin >> V2[i];
            
            // Validación del orden creciente
            if(i > 0 && V2[i] <= V2[i-1]) {
                cout << "Error: Debe ser mayor que " << V2[i-1] << ". Intente nuevamente.\n";
            }
        } while(i > 0 && V2[i] <= V2[i-1]);
    }
    
    // 3. Proceso de MERGE
    // Mientras haya elementos en ambos arreglos
    while(I < 10 && J < 13) {
        if(V1[I] < V2[J]) {
            V3[K] = V1[I];
            I++;
        } else if(V1[I] == V2[J]) {
            // Si los elementos son iguales, copiamos uno y avanzamos ambos índices
            V3[K] = V1[I];
            K++;
            V3[K] = V2[J];
            I++;
            J++;
        } else {
            V3[K] = V2[J];
            J++;
        }
        K++;
    }
    
    // Copiar elementos restantes de V1 si quedan
    while(I < 10) {
        V3[K] = V1[I];
        I++;
        K++;
    }
    
    // Copiar elementos restantes de V2 si quedan
    while(J < 13) {
        V3[K] = V2[J];
        J++;
        K++;
    }
    
    // 4. Mostrar el arreglo resultante
    cout << "\nArreglo resultante ordenado:\n";
    for(int i = 0; i < K; i++) {
        cout << V3[i];
        if(i < K-1) cout << ", ";
    }
    cout << endl;
    
    return 0;
} 
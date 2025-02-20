//Diga cual es la salida (Valor = 2 puntos)

#include <iostream>

int* createArray(int size) {
    int* arr = new int[size]; 
    for (int i = 0; i < size; ++i) {
        arr[i] = i * 10;
    }
    return arr; 
}

int main() {
    int size = 10;
    int* myArray = createArray(size); 
    
    for (int i = 0; i < size; ++i) {
        std::cout << myArray[i] << " ";
        if(i==2)
           break;
    }
    std::cout << std::endl;

    delete[] myArray; 
    return 0;
}
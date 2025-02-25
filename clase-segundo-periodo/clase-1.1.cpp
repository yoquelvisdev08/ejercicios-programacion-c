#include <iostream>
using namespace std;

int binarySearch(int arr[], int L, int R, int key) {
    if(R >= L){
        int mid = (L+R)/2;
        if(arr[mid] == key)
            return mid;
        
        if(arr[mid] > key)
            return binarySearch(arr, L, mid-1, key);
        return binarySearch(arr, mid+1, R, key);
    }
    return -1;  // Retorna -1 cuando no encuentra el elemento
}

int main() {
    int arr[] = {1, 2, 3, 4, 5,6,7,8,9,10};
    int n = 5;
    int key = 4;
    
    int resultado = binarySearch(arr, 0, n-1, key);
    
    if(resultado != -1)
        cout << "Elemento encontrado en posicion " << resultado << endl;
    else
        cout << "Elemento no encontrado" << endl;
        
    return 0;
}
#include <iostream>
using namespace std;

// Función recursiva que suma los números desde k hasta 0
// Por ejemplo, si k=3, calcula 3 + 2 + 1 + 0
int x(int k)
{
    // Caso base: cuando k <= 0, retornamos 0
    if(k <= 0)
        return 0;
    // Caso recursivo: sumamos k más la suma de los números menores
    return k + x(k - 1);  // Importante: decrementamos k en la llamada recursiva
}

int main(){
    // Probamos la función con el valor 10
    int result = x(10);
    // Imprimimos el resultado
    cout << result << endl;
    return 0;
}
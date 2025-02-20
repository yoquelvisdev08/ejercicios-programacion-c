//Dado el siguiente programa diga cual es la salida [Digite un valo numérico] (Valor = 2 puntos)

#include <iostream>
using namespace std;

void fun(int* ptr) { *ptr = 30; }

int main()
{
    int x = 20;
    fun(&x);
    cout <<  x;

    return 0;
}
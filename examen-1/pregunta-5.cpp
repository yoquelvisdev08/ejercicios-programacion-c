//Diga cual es la salida: (Valor = 2 puntos)


//#include <bits/stdc++.h>
#include <iostream>
using namespace std;
void func1()
{
    
    int val[3] = { 5, 10, 20 };

    int* ptr;

    ptr = val;

    cout << ptr[0] <<  " " << ptr[2];
}
// Driver program
int main() { func1(); }
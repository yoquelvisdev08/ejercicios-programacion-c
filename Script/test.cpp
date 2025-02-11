#include <iostream>
using namespace std;

int x3(int n){
    if(n==0)
    return 0;
    if(n==1 || n==2)
    return 1;
  else
    return x3(n-1) + x3(n-2) + x3(n-3);
}

int main(){
    int n;
    cout << "Ingrese un numero: ";
    cin >> n;
    cout << "El resultado es: " << x3(n) << endl;
    return 0;
}
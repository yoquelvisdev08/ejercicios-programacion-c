//Diga cual es la salida: (Valor = 2 puntos)


//#include <bits/stdc++.h>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main() {
    list<vector<int>> l = {{1, 3}, {2, 8}};
  
    for (auto v : l) {
        for (auto i : v){
             cout << i << " ";
         
        }
           
        cout << endl;
        break;
    }
    return 0;
}
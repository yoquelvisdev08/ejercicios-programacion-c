#include <iostream>

double mepow(double b, double n) {
    double p = 1;
    if(n == 0)
    return p;
    int i = 0;
    while(i < n) {
        p = p * b;
        i++;
    }
    return p;
}

int main() {
    double b, n;
    std::cout << "Ingrese la base: ";
    std::cin >> b;
    std::cout << "Ingrese el exponente: ";
    std::cin >> n;
    std::cout << "El resultado es: " << mepow(b, n) << std::endl;
    return 0;
}
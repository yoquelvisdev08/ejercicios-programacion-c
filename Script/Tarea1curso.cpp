#include <iostream>
class Operaciones {
public:
    int sum(int a, int b){
        int R;
        R = a + b;
        return R;
    }

    int res(int a, int b){
        int R;
        R = a - b;
        return R;
    }

    int mul(int a, int b){
        int R;
        R = a * b;
        return R;
    }

    int div(int a, int b){
        int R;
        R = a / b;
        return R;
    }
};

int main(){
    int a = 10;
    int b = 20;
    Operaciones m = Operaciones();
    int R1 = m.sum(a,b);
    int R2 = m.res(a,b);
    int R3 = m.mul(a,b);
    int R4 = m.div(a,b);
    std::cout << "El resultado es: " << R1 << std::endl;
    std::cout << "El resultado es: " << R2 << std::endl;
    std::cout << "El resultado es: " << R3 << std::endl;
    std::cout << "El resultado es: " << R4 << std::endl;
    return 0;
}
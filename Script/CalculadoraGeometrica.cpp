#include <iostream>
#include <cmath>

class CalculadoraGeometrica {
public:
    // Área del círculo (pi * r^2)
    double areaCirculo(double radio) {
        return M_PI * radio * radio;
    }

    // Área del cuadrado (lado^2)
    double areaCuadrado(double lado) {
        return lado * lado;
    }

    // Área del rectángulo (base * altura)
    double areaRectangulo(double base, double altura) {
        return base * altura;
    }

    // Área del pentágono ((perímetro * apotema) / 2)
    double areaPentagono(double lado) {
        double apotema = lado / (2 * tan(M_PI/5));
        return (5 * lado * apotema) / 2;
    }

    // Área del hexágono ((perímetro * apotema) / 2)
    double areaHexagono(double lado) {
        double apotema = lado * sqrt(3) / 2;
        return (6 * lado * apotema) / 2;
    }

    // Área del heptágono ((perímetro * apotema) / 2)
    double areaHeptagono(double lado) {
        double apotema = lado / (2 * tan(M_PI/7));
        return (7 * lado * apotema) / 2;
    }
};

int main() {
    CalculadoraGeometrica calc;
    
    //uso
    double radio = 5;
    double lado = 4;
    double base = 6;
    double altura = 3;

    std::cout << "Áreas de figuras geométricas:" << std::endl;
    std::cout << "Círculo (radio " << radio << "): " << calc.areaCirculo(radio) << std::endl;
    std::cout << "Cuadrado (lado " << lado << "): " << calc.areaCuadrado(lado) << std::endl;
    std::cout << "Rectángulo (base " << base << ", altura " << altura << "): " 
              << calc.areaRectangulo(base, altura) << std::endl;
    std::cout << "Pentágono (lado " << lado << "): " << calc.areaPentagono(lado) << std::endl;
    std::cout << "Hexágono (lado " << lado << "): " << calc.areaHexagono(lado) << std::endl;
    std::cout << "Heptágono (lado " << lado << "): " << calc.areaHeptagono(lado) << std::endl;

    return 0;
}

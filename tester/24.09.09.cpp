#include <iostream>

class complex{

public:
    complex(double r = 0, double i = 0): real(r), imag(i){ }

    double getReal() const { return real; }
    double getImag() const { return imag; }

private:
    double real;
    double imag;
};

int main(){
    const complex c1(2,2);
    std::cout << c1.getReal() << std::endl;
    std::cout << c1.getImag() << std::endl;
}
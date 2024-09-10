#include <iostream>
#include "mycomplex.h"
#include "template_complex.h"

//using namespace std;
int main()
{
    mycomplex x = mycomplex(2,1);
    x += mycomplex(1,2);
    std::cout << x << std::endl;

    template_complex<double> y (2,1);
    std::cout << y << std::endl;
}

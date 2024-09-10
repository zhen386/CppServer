#include <iostream>
#include "mycomplex.h"

//using namespace std;

// std::ostream& operator<< (std::ostream& os, const mycomplex& x)
// {
//     return os << '(' << getReal(x) << ',' << getImag(x) << ')';
// }


int main()
{
    mycomplex x = mycomplex(2,1);
    x = x + mycomplex(1,2);
    std::cout << x << std::endl;
    //std::cout << 1 << std::endl;
}

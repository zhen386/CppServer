#include <iostream>
#include "mycomplex.h"

//using namespace std;
int main()
{
    mycomplex x = mycomplex(2,1);
    x += mycomplex(1,2);
    std::cout << x << std::endl;
    //std::cout << 1 << std::endl;
}

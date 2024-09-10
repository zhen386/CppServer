#ifndef __TEMPLATE_COMPLEX__
#define __TEMPLATE_COMPLEX__

#include <iostream>

template <typename T>
class template_complex
{
public:
    template_complex(T r = 0, T i = 0): real(r), imag(i){ }

    T getReal() const { return real; }
    T getImag() const { return imag; }

private:
    T real, imag;
};

template <typename T>
std::ostream& operator << (std::ostream& os, template_complex<T>& x){
    return os << '(' << x.getReal() << ',' << x.getImag() << ')';
}


#endif
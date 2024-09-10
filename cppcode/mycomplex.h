#ifndef __MYCOMPLEX__       //防御性声明
#define __MYCOMPLEX__


//前置声明
#include <cmath>
#include <iostream>


class ostream;         
class mycomplex;

mycomplex& __doapl(mycomplex* ths, const mycomplex& r);   //传参和返回值：传值与传引用


//class的声明
//template <typename T>     //模板
class mycomplex{

public:
    mycomplex(double r = 0, double i = 0): real(r), imag(i) { }  //初始化列表赋值的优势

    mycomplex& operator += (const mycomplex&);      //运算符重载

    double getReal() const { return real; }     //const修饰成员函数
    double getImag() const { return imag; }     

    //friend std::ostream& operator<< (std::ostream& os, const mycomplex& x);
private:
    double real, imag;

    friend mycomplex& __doapl(mycomplex*, const mycomplex&);  //友元
    
    
    //mycomplex(double r = 0, double i = 0): real(r), imag(i) { }     //私有构造函数：单例模式singleton
};


//类外定义
inline mycomplex& __doapl(mycomplex* ths, const mycomplex& r)     //inline内联函数
{      
    ths->real += r.real;      //友元可以访问private成员
    ths->imag += r.imag;
    return *ths;
}

inline mycomplex& mycomplex::operator += (const mycomplex& r)     //类外定义的成员函数语法
{    
    return __doapl(this, r);    //this指针
}

inline double getImag(const mycomplex& x)                     //成员函数与全局函数
{        
    return x.getImag();
}

inline double getReal(const mycomplex& x)
{
    return x.getReal();
}

inline mycomplex operator + (const mycomplex& x, const mycomplex& y)        //何时可返回引用？何时应返回值？
{         
    return mycomplex(getReal(x) + getReal(y), getImag(x) + getImag(y));     //匿名对象
}

inline mycomplex operator + (const mycomplex& x, const double y)            //同一运算符的多次重载
{           
    return mycomplex(getReal(x) + y, getImag(x));
}

inline mycomplex operator + (const double x, const mycomplex& y)
{
    return mycomplex(x + getReal(y), getImag(y));
}

std::ostream& operator<< (std::ostream& os, const mycomplex& x)
{
    return os << '(' << getReal(x) << ',' << getImag(x) << ')';
}







#endif
# 函数的分文件编写

分为头文件.h（声明函数定义）、源文件.cpp（实现函数）进行编写

```cpp
//HelloWorld.h

#include <iostream>

void helloWorld();
```

```cpp
//HelloWorld.cpp

#include "HelloWorld.h" //自编写头文件，以双引号引入

void helloWorld(){
  std::cout << "Hello,World!" << std::endl;
}
```

在使用函数的时候，再次引入头文件即可

```cpp
//main.cpp

#include "HelloWorld.h"

int main(){
  helloWorld();
  return 0;
}
```

# 指针

1、空指针

空指针即指向NULL的指针。

注意，NULL为一个具体的位置，而不是不存在的地址，一般定义NULL = 0；而0至255地址区间的内存为操作系统所占用，不允许访问和修改，否则抛出空指针异常（NullPointerException）

2、野指针

野指针即指向非法内存位置的指针。

```cpp
int *p = (int *) 0x1100;
```

以此为例，指向了未申请的内存空间！如果访问，会报错访问权限冲突。

3、const修饰指针

```cpp
//常量指针，指针的指向可以修改，指向的值不可以修改
const int *p = &a;

//指针常量，指针的指向不可以修改，指向的值可以修改
int *const p = &a;

//const同时修饰，指针的指向和指向的值都不可以修改
const int *const p = &a;
```

值得注意的是，以上三种情况中const仅修饰了指针变量，而并不对a变量本身做修饰。也就是说，仅限制了对指针变量的操作以及通过指针变量控制内存的操作，而并未限制任何针对变量本身的操作。**我仍然可以随意更改变量a的数值。**

# 内存模型

内存分区模型：

- 代码区：存放函数题的二进制代码，由操作系统管理
- 全局区：存放全局变量、静态变量和常量
- 栈区：由编译器自动分配和释放，存放函数的参数值、局部变量
- 堆区：由程序员分配和释放

不同分区具有不同的生命周期。

new运算符

```cpp
//在堆区申请1个int型数据的内存空间，该变量值为10
int *p = new int (10);
//在堆区申请10个int型数据的连续内存空间
int *q = new int [10];

//释放堆区内存
delete p；
delete[] q;
```

new运算符返回的是所申请数据类型的指针。由于是在堆区申请内存，在程序中若程序员不主动释放，则不会自动释放。

# 引用

引用的本质：给一个变量起一个别名

```cpp
int a = 10;
int &b = a; //a的一个引用
```

**引用必须要初始化，且初始化后不可再更改。**与指针对比，指针不必须初始化（NULL），也可以改变其指向的内存位置。

函数传引用：传指针的简化形式，既能做到函数中联结形参与实参（形参修饰实参），也能避免指针误操作，只需要在函数定义中写明参数为引用传递即可。

```cpp
void swap1(int num1, int num2);		//传值
void swap2(int *num1, int *num2);	//传指针
void swap3(int &num1, int &num2);	//传引用

int a = 10, b = 20;
swap1(a, b);		//形参不修饰实参
swap2(&a, &b);	//形参修饰实参
swap3(a, b);		//形参修饰实参
```

tips：为什么不需要额外创建指针对象或引用对象？

```cpp
void swap1(int num1, int num2);		//传值
void swap2(int *num1, int *num2);	//传指针
void swap3(int &num1, int &num2);	//传引用

int a = 10, b = 20;
//int *p = a, int *q = b;
//int &c = a, int &d = b;
swap1(a, b);		//形参不修饰实参
swap2(&p, &q);	//形参修饰实参
swap3(c, d);		//形参修饰实参
```

思考函数实现时的逻辑，首先根据定义创建形参对象！在创建形参对象的同时即完成了创建指针/引用的操作。

引用作函数返回值：不要返回局部变量的引用

```cpp
int& test01(){
	int a = 10;
  return a;
}
int &ref1 = test01();	//ref1所指的内存位置已被释放，可能出现问题
```

```cpp
int& test02(){
	static int a = 10;	//静态变量，存放于内存中的全局区
  return a;
}
int &ref2 = test02();	//ref2所指的内存位置不会被释放
```

另：返回引用的函数，其调用可以作为表达式左值

```cpp
int& test03(){
	static int a = 10;
  return a;
}
int &ref3 = test03();
std::cout << ref3 << std::endl; //ref3 = 10
test03() = 1000;	//对返回的引用进行的赋值操作
std::cout << ref3 << std::endl; //ref3 = 1000
```

**引用的本质：指针常量**

常量引用：修饰形参，防止误修改

```cpp
void test04(const int &val){
  //val = 0;
}
```

# 函数

## 函数默认参数

```cpp
int func(int a, int b = 5, int c = 10){
  //默认参数从左至右，不能混叠
  return a + b + c;
}
//带有默认值的参数可以缺省
func(a, b, c);
func(a, b);
func(a);
```

注意，如果函数声明已经带有默认参数，其实现就不能再次带有默认参数。反之同理。

```cpp
//在函数声明时指定默认参数
int func(int a, int b = 5, int c = 10);

int func(int a, int b, int c){
  return a + b + c;
}

//在函数实现时指定默认参数
int func(int a, int b, int c);

int func(int a, int b = 5, int c = 10){
  return a + b + c;
}
```

## 函数占位参数

```cpp
int func(int a, int){
  return a;
}

func(10, 10);	//占位参数必须传入，不能缺省
```

占位参数也可以设置默认参数

```cpp
int func(int a, int = 10){
  return a;
}

func(10);		//此时占位参数具有默认参数，可以缺省
```

## 函数的重载

同名函数，具有不同的参数列表和不同的实现，称为函数的重载

```cpp
//重载的发生条件:参数类型、个数、顺序不同
void func(){
  std::cout << "func()" << std::endl;
}

void func(int a){
  std::cout << "func(int a)" << std::endl;
}

void func(double a){
  std::cout << "func(double a)" << std::endl;
}

void func(int a, double b){
	std::cout << "func(int a, double b)" << std::endl;
}

void func(double a, int b){
  std::cout << "func(double a, int b)" << std::endl;
}
```

一句话总结，判断函数是否可以进行重载，只需要考察他在调用的时候是否存在二义性。

值得注意的是，很多情况下函数理论上不可以发生重载，但由于未被调用或调用时不会存在二义性，编译仍然可以通过。

```cpp
void func(int a){
  std::cout << "func(int a)" << std::endl;
}

void func(int a, int b = 10){
  std::cout << "func(int a, int b = 10)" << std::endl;
}

int main(){
	void func(1, 2);		//不存在调用时的二义性，可以运行
  void func(1);				//存在调用时的二义性，运行报错
  return 0;
}
```

一些特殊的函数重载：

```cpp
//返回类型重载
void func(){
  std::cout << "void func()" << std::endl;
}

int func(){
  std::cout << "int func()" << std::endl;
  return 0;
}

int func(int a){
  std::cout << "int func(int a)" << std::endl;
  return 0;
}

int main(){
  func();		//不可以发生重载
  func(1);	//可以发生重载
}
```

注意函数重载的依据不能仅为返回类型。

```cpp
//引用重载
void func(int &a){	
  std::cout << "void func(int &a)" << std::endl;
}

void func(const int &a){
  std::cout << "void func(const int &a)" << std::endl;
}

int main(){
  int a = 10;
  func(a);		//调用int &a
  func(10);		//int &a = 10 不合法， 故调用const int &a
  return 0;
}
```

以上例子是可以发生重载的，原因在于引用所指向的必须是一个变量，而常量引用所指向的必须是一个常量，这就在参数类型上对他们作出了区分，不存在二义性，满足函数重载发生的条件。

一言以蔽之，函数是否可以发生重载是由编译器来判断的，编译时不存在二义性即可通过。

# 类和对象

## 访问权限

cpp中有三种访问权限，public，protected，private。

```cpp
class Access{
//public权限，任意位置均可访问
public:
  int num1;
//protected权限，类外不可直接访问
protected:
  int num2;
  int getNum2();
  void setNum2(num);
//private权限，类外与继承类均不可直接访问
private:
  int num3
  int getNum3();
  void setNum3(num);
}
```

使用Getter和Setter精准控制私有变量的访问权限，以及实现边界检测等额外功能。

struct与class区别？在cpp中，**唯一的区别在于默认的访问权限不同。**class默认private，struct默认public。

## 构造函数与析构函数

对象的生成与销毁，对应构造函数与析构函数，**这两种函数由编译器自动调用。**如果不提供具体的实现，编译器会提供空实现的构造与析构函数。

```cpp
class Person{
  int age;
  
public:
  //构造函数，没有返回值，可以接受参数并发生重载
  Person(){
    std::cout << "构造函数的无参调用" << std::endl;
	}
  
  Person(int a){
    std::cout << "构造函数的有参调用" << std::endl;
	}
  
  //拷贝构造函数
  Person(const Person &p){
    age = p.age;
    std::cout << "拷贝构造函数的调用" << std::endl;
  }
  
  //析构函数，没有返回值，不可以接受参数
  ~Person(){
    std::cout << "析构函数的调用" << std::endl;
  }
};

int main(){
  Person p;	//执行构造函数
  return 0;	//由于对象创建在栈上，函数退出时释放栈，调用析构函数
}
```

构造函数主要分为有参构造与无参构造（默认构造）、普通构造与拷贝构造函数。而构造函数的调用分为括号法、显示法、隐式法。

```cpp
int main(){
  //默认构造函数的调用，注意不加括号
  Person p1;
  
  //有参构造函数的调用
  Person p2(10);
  Person p2 = Person(10); //完整版
  Person p2 = 10;
  
  //拷贝构造函数的调用
  Person p3(p2);
  Person p3 = Person(p2);
  Person p3 = p2;
  
  Person p1();	//一个名称为p1，返回类型为Person类的函数声明
  
  Person(10);		//一个匿名对象，在执行当前行代码完毕后，系统会回收该对象。
}
```

注意，调用默认构造函数时，不要加空的小括号。**如果加入了小括号，编译器会将其定义为一个函数的声明！**

同时注意，**不要利用拷贝构造函数来初始化一个匿名对象。**编译器会去除小括号，并认为此语句为一个对象的声明，从而产生重定义错误。

拷贝构造函数的调用时机：

```cpp
//函数传参
void test1(Person p){
  return;
}

Person p1;
test1(p1);		//此时会发生拷贝构造函数的调用

//函数返回局部对象
Person test2(){
	Person p2;
  return p2;
}

Person p3 = test2();		//此时会发生拷贝构造函数的调用
```

**cpp编译器提供默认无参构造函数、默认拷贝构造函数以及默认析构函数。**其中无参构造函数和析构函数均为空实现，拷贝构造函数仅进行值拷贝。

**当用户定义有参构造函数时，编译器将不再提供默认无参构造函数，但仍会提供默认拷贝构造函数；当用户定义拷贝构造函数时，编译器将不再提供任何默认构造函数。**

```cpp
//用户定义有参构造函数
class Person{
  int age;

public:
  Person(int a){
    std::cout << "构造函数的有参调用" << std::endl;
	}
};

int main(){
  Person p;								//报错，无法再使用无参构造函数来来生成对象
  Person p1 = Person(10);	//正常运行
  Person p2 = Person(p1);	//正常运行，进行值传递并构造p2对象
  return 0;	
}

```

```cpp
//用户定义拷贝构造函数
class Person{
  int age;

public:
  Person(const Person &p){
    age = p.age;
    std::cout << "拷贝构造函数的调用" << std::endl;
  }
};

int main(){
  Person p;								//报错，无法使用无参构造函数
  Person p1 = Person(10);	//报错，传入参数类型不匹配 
  Person p2 = Person(p2);	//特殊的构造方式
  return 0;
}
```

## 深拷贝与浅拷贝

编译器提供的默认拷贝构造函数，仅进行简单的值传递，可能会引起问题。

```cpp
class Person{
  int age;
  int* height;
 
public:
  Person(int m_age, int* m_height){
		age = m_age;
    height = m_height;
  }
  
  ~Person(){
    if(height != NULL){
      delete height;
    }
  }
};

int main(){
  Person p1 = Person(18, new int(160)); //开辟堆区内存，传入指向此块内存的指针
  Person p2 = Person(p1); //使用默认拷贝构造函数
  return 0;
}
```

以上代码会出现问题，原因在于使用默认拷贝构造函数构造p2时，仅进行了简单的值传递，即浅拷贝。**此时，p1和p2的height指针指向了同一块堆区内存！**在释放p1和p2时，由于存在两个相同指向的指针，堆区内存将会被二次释放，产生错误。此即为浅拷贝可能产生的问题：内存块的二次释放。

为了解决以上问题，我们需要自行实现拷贝构造函数，实现指针的深拷贝。

```cpp
class Person{
  int age;
  int* height;
 
public:
  Person(int m_age, int* m_height){
		age = m_age;
    height = m_height;
  }
  
  Person(const Person &p){
    age = p.age;
    height = new int(*p.height);	// 重新开辟一块新的堆区内存，让其具有相同的值
  }
  
  ~Person(){
    if(height != NULL){
      delete height;
    }
  }
};

int main(){
  Person p1 = Person(18, new int(160)); // 开辟堆区内存，传入指向此块内存的指针
  Person p2 = Person(p1); // 使用自实现拷贝构造函数
  return 0;
}
```

**此时，两个Person对象的身高变量为两个指向不同堆区内存块的指针变量，而这两个内存块存放的值相同。**

不难发现，浅拷贝和深拷贝具有本质上的不同，且会产生一些使用上的不同特性：例如在进行深拷贝后，使用p1的指针操纵内存，由于两个指针所指向的是不同的内存块，p2指针所指的值并不会发生改变，而浅拷贝则相反。当然，在实际编写代码的时候要尽量避免对指针变量的浅拷贝的出现。


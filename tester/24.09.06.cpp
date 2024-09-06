#include <iostream>
#include <string>

class Person{
public:
  int age;
  Person& ageIncrease(){
    age = age + 1;
    return *this;			//对this指针进行解引用，即得到调用的对象
  }
};

int main(){
  Person p;
  p.age = 1;
  p.ageIncrease().ageIncrease();
  p.ageIncrease();		//实现链式编程
  std::cout << p.age << std::endl;
  return 0;
}
#include <iostream>


class Person{

public:
  int age;
  int* height;
 
  Person(int m_age, int* m_height){
	age = m_age;
    height = m_height;
  }
  
  ~Person(){
    if(height != NULL){
      delete height;
      height = NULL;
    }
  }
    
};

int main(){
  Person p1 = Person(18, new int(160));
  Person p2 = Person(p1);
  std::cout << "p1的年龄是: " << p1.age << std::endl;
  std::cout << "p1的身高是: " << *p1.height << std::endl;
  return 0;
}

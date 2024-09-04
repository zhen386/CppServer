#include <iostream>


int& test03(){
	static int a = 10;
    return a;
}

int main(){

    int &ref3 = test03();
    std::cout << ref3 << std::endl; //ref3 = 10

    test03() = 1000;	//对返回的引用进行的赋值操作
    std::cout << ref3 << std::endl; //ref3 = 1000 

    return 0;

}

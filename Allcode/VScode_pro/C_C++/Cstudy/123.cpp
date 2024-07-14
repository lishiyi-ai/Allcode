 
#include <iostream>
#include <thread>
#include <string>
 
class A
{
public:
    A() {}
    static void fun(std::string& str) { std::cout << str << std::endl; }
};
 
int main()
{   
    A t;
    std::string str = "Good,work!";
    std::thread a(&A::fun,std::ref(str));
    a.join();
    std::cout << "Hello World!\n";
}
 
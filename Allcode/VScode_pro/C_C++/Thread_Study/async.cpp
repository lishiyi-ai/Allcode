// Compiler: MSVC 19.29.30038.1
// C++ Standard: C++17
// 异步
#include <iostream>
#include <thread>
#include <future>
using namespace std;
int main() {
	future i =  async(launch::async, [](const char *message){
		cout << message << flush;
	}, "Hello, ");
	cout << "World!" << endl;
    system("pause");
	return 0;
}
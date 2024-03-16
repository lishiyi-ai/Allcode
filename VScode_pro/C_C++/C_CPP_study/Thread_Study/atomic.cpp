// Compiler: MSVC 19.29.30038.1
// C++ Standard: C++17
// 原子操作
#include <iostream>
#include <thread>
// #include <mutex> //这个例子不需要mutex了
#include <atomic>
using namespace std;
// 无法引用已消除副本所需的 "std::atomic<int>::atomic(const std::atomic<int> &)"
// 报这个错误的主要原因是原子变量不能使用拷贝构造。
// 这个限制只在原子变量初始时生效，初始之后时可以使用赋值操作符的。
atomic_int n;
void count10000() {
	for (int i = 1; i <= 10000; i++) {
		n++;
	}
}
int main() {
	n = 0;
	thread th[100];
	for (thread &x : th)
		x = thread(count10000);
	for (thread &x : th)
		x.join();
	cout << n << endl;
	system("pause");
	return 0;
}
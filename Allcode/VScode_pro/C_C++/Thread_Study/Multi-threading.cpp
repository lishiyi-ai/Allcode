// Compiler: MSVC 19.29.30038.1
// C++ Standard: C++17
#include <iostream>
#include <thread>
using namespace std;
void doit() { cout << "World!" << endl; }
// thread的基本使用
int main01() {
	// 这里的线程a使用了 C++11标准新增的lambda函数
	// 有关lambda的语法，请参考我之前的一篇博客
	// https://blog.csdn.net/sjc_0910/article/details/109230162
	thread a([]{
		cout << "Hello, " << flush;
	}), b(doit);
	a.join();
	b.join();
    system("pause");
	return 0;
}
// thread的带有参数的寒素
void countnumber(int id, unsigned int n) {
	for (unsigned int i = 1; i <= n; i++);
	cout << "Thread " << id << " finished!" << endl;
}
int main03() {
	thread th[10];
	for (int i = 0; i < 10; i++)
		th[i] = thread(countnumber, i, 100000000);
	for (int i = 0; i < 10; i++)
		th[i].join();
	return 0;
}
// thread执行带有引用参数的函数
template<class T> void changevalue(T &x, T val) {
	x = val;
}
int main() {
	thread th[100];
	int nums[100];
	for (int i = 0; i < 100; i++)
		th[i] = thread(changevalue<int>, ref(nums[i]), i+1);
	//错误写法
	// for (int i = 0; i < 100; i++)
		// th[i] = thread(changevalue<int>, nums[i], i+1);
	// thread在传递参数时，是以右值传递。
	for (int i = 0; i < 100; i++) {
		th[i].join();
		cout << nums[i] << endl;
	}
	cout<< "主程序结束" << endl;
	system("pause");
	return 0;
}
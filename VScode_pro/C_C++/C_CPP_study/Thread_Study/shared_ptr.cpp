#include <memory>
#include <iostream>

using namespace std;
// 无论何时我们拷贝一个shared_ptr，计数器都会递增。
// 例如，当用一个shared_ptr初始化另一个shared_ptr，
// 或将它作为参数传递给一个函数以及作为函数的返回值时，它所关联的计数器就会递增，
// 当我们给shared_ptr赋予一个新值或者是shared_ptr被销毁（例如一个局部的shared_ptr离开作用域）时，计数器就会递减。

//一旦一个shared_ptr的计数器变为0，他就会自动释放自己所管理的对象。



int main(){
	// 最好使用make_shared创建共享指针，
	shared_ptr<int> p1 = make_shared<int>();//make_shared 创建空对象，
	cout << "p1 count = " << p1.use_count() << endl;
    *p1 = 10;
	cout << "p1 count = " << p1.use_count() << endl;
    cout << "p1 = " << *p1 << endl; // 输出10

	// 打印引用个数：1
	cout << "p1 count = " << p1.use_count() << endl;
	
	// 第2个 shared_ptr 对象指向同一个指针
	std::shared_ptr<int> p2(p1);
    // 不要使用shared_ptr的get()初始化另一个shared_ptr
    // std::shared_ptr<int> p2(p1.get());

    *p1 = 15;
	// 输出2
	cout << "p2 count = " << p2.use_count() << endl;
	cout << "p1 count = " << p1.use_count() << endl;

	// 比较智能指针，p1 等于 p2
	if (p1 == p2) {
		std::cout<< "p1 and p2 are pointing to same pointer\n";
	}
	
	p1.reset();// 无参数调用reset，无关联指针，引用个数为0
	cout << "p1 Count = " << p1.use_count() << endl;
	
	p1.reset(new int(11));// 带参数调用reset，引用个数为1
	cout << "p1 Count = " << p1.use_count() << endl;

	p1 = nullptr;// 把对象重置为NULL，引用计数为0
	cout << "p1  Reference Count = " << p1.use_count() << endl;
    cout << "p2  Reference Count = " << p2.use_count() << endl;
	if (!p1) {
		cout << "p1 is NULL" << endl; // 输出
	}
    system("pause");
	return  0;
}
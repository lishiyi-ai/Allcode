// Compiler: MSVC 19.29.30038.1
// C++ Standard: C++17
#include <iostream>
#include <future> // std::async std::future
using namespace std;

template<class ... Args> decltype(auto) sum(Args&&... args) {
	// C++17折叠表达式
	// "0 +"避免空参数包错误
	return (0 + ... + args);
}
// 使用std::future获取线程的返回值
int main01() {
	// 注：这里不能只写函数名sum，必须带模板参数
	future<int> val = async(launch::async, sum<int, int, int>, 1, 10, 100);
	// future::get() 阻塞等待线程结束并获得返回值
	cout << val.get() << endl;
	cout << 1 << endl;
    system("pause");
    return 0;
}


// void特化std::future
void count_big_number() {
	// C++14标准中，可以在数字中间加上单
	// 引号 ' 来分隔数字，使其可读性更强
	for (int i = 0; i <= 10'0000'0000; i++);
}
int main() {
	//future<void> fut = async(launch::async, count_big_number);
	future<int> fut01 = async(launch::async, main01);
	cout << "Please wait" << flush;
	// 每次等待1秒
	// while (fut.wait_for(chrono::seconds(1)) != future_status::ready){
    //     cout << '.' << flush;
    // }
	while(fut01.wait_for(chrono::seconds(1)) == future_status::ready){
		cout << "#" << flush;
	}
	cout << endl << "Finished!" << endl;
    system("pause");
	return 0;
}
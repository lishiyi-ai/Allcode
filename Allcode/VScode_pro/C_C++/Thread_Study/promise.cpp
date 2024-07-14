// Compiler: MSVC 19.29.30038.1
// C++ Standard: C++17
#include <iostream>
#include <thread>
#include <future> // std::promise std::future
using namespace std;

template<class ... Args> decltype(auto) sum(Args&&... args) {
	return (0 + ... + args);
}

template<class ... Args> void sum_thread(promise<long long> &val, Args&&... args) {
	val.set_value(sum(args...));
}

int main() {
	promise<long long> sum_value;
	thread get_sum(sum_thread<int, int, int>, ref(sum_value), 1, 10, 100);
	cout << sum_value.get_future().get() << endl;
	get_sum.join(); // 感谢评论区 未来想做游戏 的提醒
	system("pause");
    return 0;
}

#include <coroutine>
#include <iostream>
#include <thread>
// 只要协程处于暂停状态，就可以调用协程句柄的 destroy() 函数来释放它，
// 不一定要求协程结束。对于通过无限循环来实现的协程，手动释放是必需的。

// 与 final_suspend() 相对应的是 initial_suspend() ，在协程刚开始执行的时候，
// 会调用这个函数来决定是否暂停。我们可以将这个函数的返回类型改成 std::suspend_always 来让协程一执行即暂停。
// 这对于一些需要延迟执行的场景是有用的，例如，我们想先获取一批协程句柄，
// 像数据那样对它们进行管理，在稍后的时机再挑选合适的协程来执行。
class Task {
public:
    class promise_type {
    public:
        Task get_return_object() {
            return Task{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }

        void return_value(int value) {
            value_ = value;
        }

        int GetValue() const {
            return value_;
        }

        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() {}

    private:
        int value_{};
    };

public:
    Task(std::coroutine_handle<promise_type> handle) : coroutine_handle_(handle) {

    }
    ~Task(){
        coroutine_handle_.destroy();
    }

    int GetValue() const {
        return coroutine_handle_.promise().GetValue();
    }

private:
    std::coroutine_handle<promise_type> coroutine_handle_;
};

Task GetInt() {

    co_return 1024;
}

int main() {

    auto task = GetInt();

    std::string line;
    while (std::cin >> line) {
        std::cout << task.GetValue() << std::endl;
    }
    return 0;
}
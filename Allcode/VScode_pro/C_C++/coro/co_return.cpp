#include <coroutine>
#include <iostream>
#include <thread>
#include <memory>

class IntReader {
public:
    bool await_ready() {
        return false;
    }

    void await_suspend(std::coroutine_handle<> handle) {

        std::thread thread([this, handle]() {

            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            value_ = 451;

            handle.resume();
        });

        thread.detach();
    }

    int await_resume() {
        return value_;
    }

private:
    int value_{};
};

class Task {
public:
    class promise_type {
    public:
        promise_type() : value_(std::make_shared<int>()) {

        }

        Task get_return_object() { 
            return Task{ value_ };
        }

        void return_value(int value) {
            *value_ = value;
        }

        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() {}

    private:
        std::shared_ptr<int> value_;
    };

public:
    Task(const std::shared_ptr<int>& value) : value_(value) {

    }

    int GetValue() const {
        return *value_;
    }

private:
    std::shared_ptr<int> value_;
};

Task GetInt() {

    IntReader reader1;
    int total = co_await reader1;

    IntReader reader2;
    total += co_await reader2;

    IntReader reader3;
    total += co_await reader3;

    co_return total;
}

int main() {

    auto task = GetInt();

    std::string line;
    while (std::cin >> line) {
        std::cout << task.GetValue() << std::endl;
    }
    return 0;
}
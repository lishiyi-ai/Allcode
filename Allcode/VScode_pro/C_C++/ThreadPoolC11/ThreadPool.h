#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <list>
class ThreadPool{
public:
    ThreadPool(size_t threads);
    template<typename T, typename... Args>
    auto enqueue(T&& t, Args&&... args)->
    std::future<typename std::result_of<T(Args...)>::type>; 
    virtual ~ThreadPool();
private:
    // need to keep track of threads so we ca join them
    std::vector< std::thread > workers;
    // the task queue
    std::queue<std::function<void()>> tasks;
    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads):stop(false){
    for(size_t i = 0; i < threads; ++i){
        workers.emplace_back(
            [this]{
                for(;;){
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, 
                            [this]{return this->stop || !this->tasks.empty();});
                        if(this->stop && this->tasks.empty()){
                            return ;
                        }
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    task();
                }
            }
        );
    }
}

// add new work item to the pool
template<typename T, typename... Args>
auto ThreadPool::enqueue(T&& t, Args&&... args)
    ->std::future<typename std::result_of<T(Args...)>::type>
{
    using return_type = typename std::result_of<T(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()> >(
        std::bind(std::forward<T>(t), std::forward<Args>(args)...)
    );
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if(stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task](){ (*task)(); });
    }
    condition.notify_one();
    return res;
}



// the destructor joins all threads
inline ThreadPool::~ThreadPool(){
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std:: thread &worker : workers)
        worker.join();
}
#endif
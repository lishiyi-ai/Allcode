// thread_pool.h

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <mutex>
#include <queue>
#include <functional>
#include <future>
#include <thread>
#include <utility>
#include <vector>

// Thread safe implementation of a Queue using a std::queue
template <typename T>
class SafeQueue{
    private:
        std::queue<T> m_queue;
        
        std::mutex m_mutex;
    
    public:
        SafeQueue() {}
        SafeQueue(SafeQueue &&other) {}
        ~SafeQueue(){}

        // 返回队列是否为空
        bool empty(){
            std::unique_lock<std::mutex> lock(m_mutex); //互斥信号变量加锁，防止m_queue被改变

            return m_queue.empty();
        }

        int size(){
            std::unique_lock<std::mutex> lock(m_mutex); //互斥信号变量枷锁，防止m_queue被改变
        
            return m_queue.size();
        }

        // 队列添加元素
        void enqueue(T &t){
            std::unique_lock<std::mutex> lock(m_mutex);
            m_queue.emplace(t);
        }

        // 队列取出元素
        bool dequeue(T &t){
            std::unique_lock<std::mutex> lock(m_mutex);
            
            if(m_queue.empty()) return false;

            // 取出队首元素，返回对手元素值，并进行右值引用
            t = std::move(m_queue.front()); 

            // 弹出入队的第一个元素
            m_queue.pop();

            return true;
        }
};

class ThreadPool{
    private:
        // 内置线程工作类
        class ThreadWorker{
            private:
                // 工作id
                int m_id;

                // 所属线程池
                ThreadPool *m_pool;
            public:
                // 构造函数
                ThreadWorker(ThreadPool *pool, const int id) : m_pool(pool), m_id(id){}

                // 重载()操作
                void operator() (){
                    // 定义基础函数类func
                    std::function<void()> func;

                    // 是否正在取出队列中元素
                    bool dequeued;

                    while(!m_pool->m_shutdown){
                        {
                            // 为线程环境枷锁，互访问工作线程的休眠和唤醒
                            std::unique_lock<std::mutex> lock(m_pool->m_conditional_mutex);

                            // 如果任务队列为空，阻塞当前线程
                            if(m_pool->m_queue.empty()){
                                // 等待条件变量通知，开启线程
                                m_pool->m_conditional_lock.wait(lock);
                            }

                            // 取出任务队列中的元素
                            dequeued = m_pool->m_queue.dequeue(func);
                        }

                        // 如果成功取出，执行工作函数
                        if(dequeued) func();
                    }
                }
        };

        
        // 线程池是否关闭
        bool m_shutdown;

        // 执行函数安全队列，即任务队列
        SafeQueue<std::function<void()>> m_queue;
        
        // 工作线程队列
        std::vector<std::thread> m_threads;
        
        // 线程休眠锁互斥变量
        std::mutex m_conditional_mutex;

        // 线程环境锁，可以让线程处于休眠或唤醒状态
        std::condition_variable m_conditional_lock;
    public:
        // 线程池构造函数
        ThreadPool(const int n_threads = 4):
            m_threads(std::vector<std::thread>(n_threads)), m_shutdown(false){}
        
        ThreadPool(const ThreadPool &)  = delete;

        ThreadPool(ThreadPool &&) = delete;

        ThreadPool &operator=(const ThreadPool &) = delete;

        ThreadPool &operator=(ThreadPool &&) = delete;


        // Inits thread pool
        void init(){
            for(int i = 0; i < m_threads.size(); ++i){
                // 分成工作线程
                m_threads.at(i) = std::thread(ThreadWorker(this, i));
            }
        }

        // waits until threads finish their current task and shutdowns the pool
        void shutdown(){
            m_shutdown = true;
            // 通知，唤醒所有工作线程
            m_conditional_lock.notify_all();

            for(int i = 0; i < m_threads.size(); ++i){
                // 判断线程是否在等待
                if(m_threads.at(i).joinable()){
                    // 将线程降入到等待队列
                    m_threads.at(i).join();
                }
            }
        }

        // Submit a function to be executed asynchronously by the pool
        template<typename F, typename... Args>
        // std::forward()将会完整保留参数的引用类型进行转发。
        // 如果参数是左值引用（lvalue），该方法会将参数保留左值引用的形式进行转发，
        // 如果参数是右值引用（rvalue），该方法会将参数保留右值引用的形式进行转发。
        auto submit(F &&f, Args &&... args) -> std::future<decltype(f(args...))>{
            // Create a function with bounded parameter ready to execute 连接函数和参数定义，特殊函数类型，避免左右值错误
            std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        
            // encapsulate it into a shared pointer in order to be able to copy construct
            auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

             // Warp packaged task into void function
            std::function<void()> warpper_func = [task_ptr]()
            {
                (*task_ptr)();
            };

            // 队列通用安全封包函数，并压入安全队列
            m_queue.enqueue(warpper_func);

            // 唤醒一个等待中的线程
            m_conditional_lock.notify_one();
            
            // 返回先前注册的任务指针
            return task_ptr->get_future();
        }

};

#endif

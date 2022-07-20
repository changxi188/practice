#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

template <typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue()
    {
    }

    ~ThreadSafeQueue()
    {
    }

    void Push(T new_value)
    {
        std::lock_guard<std::mutex> lk(mut_);
        data_queue_.push(std::move(new_value));
        std::cout << "data_queue size " << data_queue_.size() << std::endl;
        data_cond_.notify_one();
    }

    void WaitAndPop(T& value)
    {
        std::unique_lock<std::mutex> lk(mut_);
        data_cond_.wait(lk, [this] { return !data_queue_.empty(); });
        value = std::move(data_queue_.front());
        data_queue_.pop();
    }

    std::shared_ptr<T> WaitAndPop()
    {
        std::unique_lock<std::mutex> lk(mut_);
        data_cond_.wait(lk, [this] { return !data_queue_.empty(); });
        std::shared_ptr<T> res{std::make_shared<T>(std::move(data_queue_.front()))};
        data_queue_.pop();
        return res;
    }

    bool TryPop(T& value)
    {
        std::lock_guard<std::mutex> lk(mut_);
        if (data_queue_.emptry())
        {
            return false;
        }
        value = std::move(data_queue_.front());
        data_queue_.pop();
        return true;
    }

    std::shared_ptr<T> TryPop()
    {
        std::lock_guard<std::mutex> lk(mut_);
        if (data_queue_.empty())
        {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue_.front())));
        data_queue_.pop();
        return res;
    }

    bool Empty() const
    {
        std::lock_guard<std::mutex> lk(mut_);
        return data_queue_.empty();
    }

private:
    mutable std::mutex mut_;
    std::queue<T>           data_queue_;
    std::condition_variable data_cond_;
};

ThreadSafeQueue<int> thread_safe_queue;

void Th1()
{
    int i = 0;

    while (true)
    {
        thread_safe_queue.Push(++i);
        std::cout << " eTh1 push data : " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Th2()
{
    while (true)
    {
        /*
        std::cout << " bTh2 pop data failed " << std::endl;
        if (thread_safe_queue.TryPop())
        {
            std::cout << " Th2 pop data success : " << *thread_safe_queue.TryPop() << std::endl;
            continue;
        }
        std::cout << " eTh2 pop data failed " << std::endl;
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        */

        std::cout << " Th2 pop : " << *thread_safe_queue.WaitAndPop() << std::endl;
    }
}

int main()
{
    std::thread th1(Th1);
    std::thread th2(Th2);

    th1.join();
    th2.join();

    return 0;
}


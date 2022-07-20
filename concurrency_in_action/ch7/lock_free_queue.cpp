#include <atomic>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

using namespace std;

template <typename T>
class LockFreeQueue
{
private:
    struct Node
    {
        std::shared_ptr<T> data;
        Node*              next;

        Node() : next(nullptr)
        {
        }
  };

  std::atomic<Node*> head_;
  std::atomic<Node*> tail_;

  Node* popHead()
  {
      Node* const old_head = head_.load();
      if (old_head == tail_.load())  // 1
      {
          return nullptr;
    }
    head_.store(old_head->next);
    return old_head;
  }

public:
    LockFreeQueue() : head_(new Node), tail_(head_.load())
    {
    }

    LockFreeQueue(const LockFreeQueue& other) = delete;
    LockFreeQueue& operator=(const LockFreeQueue& other) = delete;

    ~LockFreeQueue()
    {
        while (Node* const old_head = head_.load())
        {
            head_.store(old_head->next);
            delete old_head;
        }
    }

    std::shared_ptr<T> Pop()
    {
        Node* old_head = popHead();
        if (!old_head)
        {
            return std::shared_ptr<T>();
        }

        std::shared_ptr<T> const res(old_head->data);  // 2
        delete old_head;
        return res;
    }

    void Push(T new_value)
    {
        std::shared_ptr<T> new_data(std::make_shared<T>(new_value));
        Node*              p        = new Node;      // 3
        Node* const        old_tail = tail_.load();  // 4
        old_tail->data.swap(new_data);               // 5
        old_tail->next = p;                          // 6
        tail_.store(p);                              // 7
    }
};

LockFreeQueue<int> lock_free_queue;

void Th1()
{
    int i = 0;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        lock_free_queue.Push(i++);
    }
}

void Th2()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        const auto res = lock_free_queue.Pop();
        if (res)
        {
            std::cout << " Pop result : " << *res << std::endl;
            continue;
        }
        std::cout << " Pop fail " << std::endl;
    }
}

int main()
{
    std::thread t1(Th1);
    std::thread t2(Th2);

    t1.join();
    t2.join();
    return 0;
}

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

template <typename T>
class LockFreeStack
{
public:
    struct Node
    {
        std::shared_ptr<T> data;
        Node* next;

        Node(const T& _data) : data(std::make_shared<T>(_data))
        {
        }
    };

    LockFreeStack()
    {
    }

    ~LockFreeStack()
    {
    }

    void Push(const T& data)
    {
        Node* const new_node = new Node(data);
        new_node->next       = head_.load();
        while (!head_.compare_exchange_weak(new_node->next, new_node))
        {
        }
    }

    std::shared_ptr<T> Pop()
    {
        ++threads_in_pop_;
        Node* old_head = head_.load();
        while (old_head && !head_.compare_exchange_weak(old_head, old_head->next))
        {
        }
        std::shared_ptr<T> res;
        if (old_head)
        {
            res.swap(old_head->data);
        }
        try_reclaim(old_head);
        return res;
    }

private:
    void try_reclaim(Node* old_head)
    {
    }

    static void delete_nodes(Node* nodes);

private:
    std::atomic<Node*> head_;
    std::atomic<unsigned> threads_in_pop_;
};

LockFreeStack<int> lock_free_stack;

void th1()
{
    for (size_t i = 0; i < 5; ++i)
    {
        lock_free_stack.Push(i);
        std::cout << " th1 push value : " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void th2()
{
    while (true)
    {
        lock_free_stack.Pop();
        std::cout << " th2 pop " << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void th3()
{
}

int main()
{
    std::thread t1(th1);
    std::thread t2(th2);

    t1.join();
    t2.join();

    return 0;
}

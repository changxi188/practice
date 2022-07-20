#include <atomic>
#include <iostream>

using namespace std;

template <typename T>
class LockFreeStack
{
public:
    struct Node
    {
        T     data;
        Node* next;

        Node(const T& _data)
        {
        }
    };

    LockFreeStack() : head_(nullptr)
    {
    }

    void Push(const T& data)
    {
        Node* const new_node = new node(data);
        new_node->next       = head_.load();
    }

private:
    std::atomic<Node*> head_;
};

int main()
{
    LockFreeStack<int> lock_free_stack;

    return 0;
}

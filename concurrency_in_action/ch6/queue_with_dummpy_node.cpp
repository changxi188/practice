#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

using namespace std;

template <typename T>
class QueueWithDummpy
{
public:
    struct Node
    {
        std::shared_ptr<T>    data;
        std::unique_ptr<Node> next;
    };

    QueueWithDummpy() : head_(std::make_unique<Node>()), tail_(head_.get())
    {
    }

    std::shared_ptr<T> TryPop()
    {
        if (head_.get() == tail_)
        {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> const res(head_->data);
        std::unique_ptr<Node>    old_head = std::move(head_);
        head_                             = std::move(old_head->next);
        return res;
    }

    void Push(T& new_value)
    {
        std::shared_ptr<T> new_data = std::make_shared<T>(std::move(new_value));
        std::unique_ptr<Node> p(new Node);
        tail_->data = new_data;
        Node* const new_tail = p.get();
        tail_->next          = std::move(p);
        tail_                = new_tail;
    }

private:
    std::unique_ptr<Node> head_;
    Node*                 tail_;
};

QueueWithDummpy<int> queue_with_dummpy;

int main()
{
    std::cout << queue_with_dummpy.TryPop() << std::endl;

    for (int i = 1; i < 5; ++i)
    {
        queue_with_dummpy.Push(i);
    }

    for (int i = 1; i < 5; ++i)
    {
        std::cout << *queue_with_dummpy.TryPop() << std::endl;
    }

    return 0;
}

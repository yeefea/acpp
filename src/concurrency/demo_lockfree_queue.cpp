
#include <atomic>
#include <memory>

template <typename T>
class LockFreeQueue
{
public:
  LockFreeQueue()
  {
    node *newNode = new node;
    head.store(newNode);
    tail.store(newNode);
  }

  void push(const T &value)
  {
    std::unique_ptr<node> newNode(new node(value));
    node *prevTail = tail.exchange(newNode.get());
    prevTail->next.store(newNode.release());
  }

  bool pop(T &value)
  {
    node *oldHead = head.load();
    node *next = oldHead->next.load();
    if (next == nullptr)
    {
      return false;
    }
    value = next->value;
    head.store(next);
    delete oldHead;
    return true;
  }

private:
  struct node
  {
    T value;
    std::atomic<node *> next;

    node() : next(nullptr) {}
    node(const T &value) : value(value), next(nullptr) {}
  };

  std::atomic<node *> head;
  std::atomic<node *> tail;
};

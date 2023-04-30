#include "ch2.h"
#include <string>
#include <iterator>
#include <memory>
#include <cstdlib>

#include "utils.h"

std::new_handler X::current_handler;

void X::outofmemory()
{
  std::cerr << "X outofmemory" << std::endl;
  abort(); // 一定要abort，否则这个函数会被反复调用
}

std::new_handler X::set_new_handler(std::new_handler p)
{
  std::new_handler old_hdl = current_handler;
  current_handler = p;
  return old_hdl;
}

void *X::operator new(size_t size)
{
  std::cout << "try allocate X[" << size << "]" << std::endl;
  std::new_handler g_hdl = std::set_new_handler(current_handler);
  void *memory;
  try
  {
    memory = ::operator new(size);
  }
  catch (std::bad_alloc &e)
  {
    std::set_new_handler(g_hdl);
    throw;
  }

  std::set_new_handler(g_hdl);
  return memory;
}
void *X::operator new[](size_t size)
{
  std::cout << "try allocate X[" << size << "]" << std::endl;
  // set global handler to custom handler
  std::new_handler g_hdl = std::set_new_handler(current_handler);
  void *memory;
  try
  {
    // call global new
    memory = ::operator new(size);
  }
  catch (std::bad_alloc &e)
  {
    // recover global handler
    std::set_new_handler(g_hdl);
    throw;
  }
  // recover global handler
  std::set_new_handler(g_hdl);
  return memory;
}

void *Base::operator new(size_t size)
{
  if (size != sizeof(Base))
  {
    // Base的子类会走到这里
    return ::operator new(size);
  }

  // Base会走到这里

  std::cout << "allocate Base" << std::endl;
  return ::operator new(size);
}

void Base::operator delete(void *raw, size_t size)
{
  if (size == 0)
  {
    return;
  }
  if (size != sizeof(Base))
  {
    ::operator delete(raw);
    return;
  }
  std::cout << "release Base" << std::endl;
  ::operator delete(raw);
}

void *ObjWithOverloadedNew::operator new(size_t size, std::new_handler p)
{
  if (p == nullptr)
  {
    return ::operator new(size);
  }
  if (size == 0)
  {
    size = 1;
  }

  auto old_hdl = std::set_new_handler(p);
  void *raw;
  try
  {
    raw = ::operator new(size);
  }
  catch (std::bad_alloc &)
  {
    std::set_new_handler(old_hdl);
    throw;
  }
  std::cout << "new obj with oom handler" << std::endl;
  std::set_new_handler(old_hdl);
  return raw;
}

const int Airplane::block_size = 4;           // 一块内存容纳的Airplane对象数量
Airplane *Airplane::head_free_list = nullptr; // 空闲链表头

void *Airplane::operator new(size_t size)
{
  if (size != sizeof(Airplane))
  {
    // 子类new
    return ::operator new(size);
  }

  Airplane *p = head_free_list;
  if (p) // likely
  {
    head_free_list = p->next;
  }
  else
  {
    // 第一次new，分配一块内存
    std::cout << "Airplane: new memory block of " << block_size << " objects" << std::endl;
    Airplane *new_blk = static_cast<Airplane *>(::operator new(block_size * sizeof(Airplane)));

    // 做成单向链表
    for (int i = 0; i < block_size; ++i)
    {
      new_blk[i].next = &new_blk[i + 1];
    }
    // sentinal节点next=0
    new_blk[block_size - 1].next = nullptr;
    // 拿走链表的第一个节点，返回该对象
    p = new_blk;
    head_free_list = &new_blk[1];
  }
  std::cout << "Airplane: take memory from block" << std::endl;
  return p;
}

void Airplane::operator delete(void *raw, size_t size)
{

  if (raw == nullptr)
  {
    return;
  }
  if (size != sizeof(Airplane))
  {
    ::operator delete(raw);
    return;
  }
  std::cout << "Airplane: return memory to free list" << std::endl;
  Airplane *carcass = static_cast<Airplane *>(raw);
  // 归还的内存放到链表头部
  carcass->next = head_free_list;
  head_free_list = carcass;
}
void demo_new_delete()
{
  constexpr int sz = 100;
  std::string *sarr = new std::string[sz];

  describe_array(sarr, sarr + sz);

  delete[] sarr;

  typedef std::string addresslines[4];
  std::string *pal = new addresslines; // 这里看不出是数组了
  delete[] pal;                        // 依然要[]不然就内存泄露，很迷，所以千万不要typedef数组!!!
}

// global_oom_handler new-handler函数 void (*)()
void global_oom_handler()
{
  std::cerr << "oops, oom! (global scope)" << std::endl;
  abort();
}

// demo_new_handler 自定义new handler
void demo_new_handler()
{
  constexpr size_t sz = 922337203685477;
  // std::set_new_handler(global_oom_handler);
  // int *pi = new int[sz];  // oom global scope
  // delete[] pi;

  X::set_new_handler(X::outofmemory);
  X *p = new X;
  delete p;
  // class specific

  Y::set_new_handler([]() -> void
                     { std::cout << "allocate Y error" << std::endl;
                     // 一定要abort
                    abort(); });
  Y *py = new Y[sz];
  delete[] py;
}

void demo_derived_class()
{
  std::cout << "Base:" << std::endl;
  Base *pb = new Base;
  delete pb;

  std::cout << "Derived: no output" << std::endl;
  Derived *pd = new Derived;
  delete pd;

  std::cout << "EasyDerived:" << std::endl;
  EasyDerived *pe = new EasyDerived;
  delete pe;

  ObjWithOverloadedNew *obj = new (
      []() -> void
      {
        std::cout << "ooooom!" << std::endl;
      }) ObjWithOverloadedNew;
  delete obj;

  obj = new ObjWithOverloadedNew;
  delete obj;
}

void demo_memory_pool()
{

  Airplane *p1 = new Airplane;
  Airplane *p2 = new Airplane;
  Airplane *p3 = new Airplane;
  Airplane *p4 = new Airplane;
  Airplane *p5 = new Airplane;

  delete p1;
  delete p2;
  delete p3;
  delete p4;
  delete p5;
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_new_delete);
  RUN_DEMO(demo_derived_class);
  RUN_DEMO(demo_memory_pool);
  // 这个放最后执行，因为要演示panic
  RUN_DEMO(demo_new_handler);
  return EXIT_SUCCESS;
}
#pragma once
#include <new>
#include <cstddef>
#include <iostream>
class X
{

public:
  static void outofmemory();
  static std::new_handler set_new_handler(std::new_handler p);
  static void *operator new(size_t size);
  static void *operator new[](size_t size);
  static void operator delete(void *p)
  {
    std::cout << "delete X at " << p << std::endl;
    // 调用全局的delete运算符
    ::operator delete(p);
  };
  static void operator delete[](void *p)
  {
    std::cout << "delete X[] at " << p << std::endl;
    ::operator delete[](p);
  };

private:
  static std::new_handler current_handler;
};

// template

template <typename T>
class NewHandlerSupport
{
public:
  static std::new_handler set_new_handler(std::new_handler p);
  static void *operator new(size_t size);
  static void *operator new[](size_t size);

private:
  static std::new_handler current_handler;
};

template <typename T>
std::new_handler NewHandlerSupport<T>::current_handler;

template <typename T>
std::new_handler NewHandlerSupport<T>::set_new_handler(std::new_handler p)
{
  std::new_handler old_hdl = current_handler;
  current_handler = p;
  return old_hdl;
}

template <typename T>
void *NewHandlerSupport<T>::operator new(size_t size)
{
  std::cout << "try allocate [" << size << "]" << std::endl;
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

template <typename T>
void *NewHandlerSupport<T>::operator new[](size_t size)
{
  std::cout << "try allocate [" << size << "]" << std::endl;
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

class Y : public NewHandlerSupport<Y>
{
public:
  int field1;
};

// global new operator
// void *operator new(size_t size){
//   if (size == 0){
//     size = 1;
//   }
//   // todo
// }


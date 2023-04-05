#pragma once

#include <string>
#include <cstddef>
#include "utils.h"

// final 关键字
class NoDerived final // final类不能作为基类，和Java一样
{
};

class Base
{
public:
  int m_pub;

protected:
  int m_prot;

private:
  int m_priv;
};

class Last final : Base
{
};

// class Bad : Last  // 错误，last是final类，不能被继承
// {
// };

class B
{
public:
  virtual B &get_ptr(int i = 1)
  {
    std::cout << OUTPUT_VAL(i) << std::endl;
    return *this;
  }

  virtual int final_func() final
  {
    return 10;
  }
};

class D : public B
{
public:
  // 运行时使用的实参由静态类型决定！！！不是动态类型！！！
  D &get_ptr(int i = 2) override final // 参数必须完全一致，但是返回类型可以是子类，override关键字是为了防止写错，让编译器检查
  {
    std::cout << OUTPUT_VAL(i) << std::endl;
    return *this;
  }
};

class E : public B
{
public:
  // int final_func() override // 错误，无法重写final函数
  // {
  // }
};

class PubDeriv : public Base
{

  void some_func()
  {
    m_prot = 1;
    m_pub = 2;
    // m_priv = 3; inaccessable
  }
};

class ProtDeriv : protected Base
{
  void some_func()
  {
    m_prot = 1;
    m_pub = 2;
    // m_priv = 3;
  }
};

class PrivDeriv : private Base
{
  void some_func()
  {
    m_prot = 1;
    m_pub = 2;
    // m_priv = 3;

    Base &br = *this; // ok
  }
};

class PrivDeriv2 : private Base
{

protected:
  using Base::m_pub; // using可以改变可访问性，子类又能访问了
};

class DerivePubDerive : public PubDeriv
{
  void some_func()
  {
    m_prot = 1;
    m_pub = 2;
    // m_priv = 3;
  }
};

class DeriveProtDerive : public ProtDeriv
{
  void some_func()
  {
    m_prot = 1; // protected
    m_pub = 2;  // protected
    // m_priv = 3;
    Base &br = *this; // ok
  }
};

class DerivePrivDerive : public PrivDeriv
{
  void some_func()
  {
    // 啥都访问不了
    // m_prot = 1;
    // m_pub = 2;
    // m_priv = 3;

    // Base &br = *this; // 父类是private继承，不能把上转型为Base了
    PrivDeriv &pr = *this; // 这是可以的
  }
};

class DerivePriveDerive2 : public PrivDeriv2
{
  void some_func()
  {
    // m_prot = 1;
    m_pub = 2; // 虽然父类是private继承，但是父类指定了m_pub为protected，这里可以访问
    // m_priv = 3;

    // Base &br = *this; // 父类是private继承，不能把上转型为Base了
  }
};

class DefaultDeriveClass : Base
{
  // <=> : private Base
};

struct DefaultDeriveStruct : Base
{
  // <=> : public Base
};

// 虚函数与作用域
class Base1
{
public:
  virtual int fcn()
  {
    std::cout << "Base1::fcn()" << std::endl;
    return 0;
  }
};

class D1 : public Base1
{
public:
  int fcn()
  {
    std::cout << "D1::fcn()" << std::endl;
    return 0;
  }
  int fcn(int)
  {
    std::cout << "D1::fcn(int)" << std::endl;
    return 0;
  }
  virtual void f2()
  {
    std::cout << "D1::f2()" << std::endl;
  }
};

class D2 : public D1
{
public:
  // using D1::fcn;
  int fcn(int)
  {
    std::cout << "D2::fcn(int)" << std::endl;
    return 0;
  }
  int fcn()
  {
    std::cout << "D2::fcn()" << std::endl;
    return 0;
  }
  void f2()
  {
    std::cout << "D2::f2()" << std::endl;
  }
};

class D3 : public D2
{

public:
  using D2::fcn; // 用using导入fcn的所有重载版本，只覆盖其中一个，如果不用using，则需要覆盖所有重载版本，很麻烦
  int fcn(int)
  {
    std::cout << "D3::fcn()" << std::endl;
    return 0;
  }
};

class ObjVirtualDestructor
{

public:
  ObjVirtualDestructor() : sp1(new std::string()) {}
  virtual ~ObjVirtualDestructor() // 虚析构函数
  {
    delete sp1;
    std::cout << "ObjVirtualDestructor.sp1 is deleted." << std::endl;
  };
  virtual void some_func()
  {
    std::cout << "ObjVirtualDestructor::some_func()" << std::endl;
  }

private:
  std::string *sp1;
};

class DerivedObjVirtualDestructor : public ObjVirtualDestructor
{
public:
  DerivedObjVirtualDestructor() : ObjVirtualDestructor(), ip1(new int{42}) {}
  ~DerivedObjVirtualDestructor()
  {
    std::cout << "DerivedObjVirtualDestructor.ip1 is deleted." << std::endl;
    delete ip1;
  }
  void some_func()
  {
    std::cout << "DerivedObjVirtualDestructor::some_func()" << std::endl;
  }

private:
  int *ip1;
};

class ObjConstructor
{
public:
  ObjConstructor(int i, std::string s) : i(i), s(s) {}
  virtual void describe(std::ostream &os)
  {
    os << OUTPUT_VAL(i) << ", " << OUTPUT_VAL(s);
  }

private:
  int i;
  std::string s;
};

class DerivedObjConstructor : public ObjConstructor
{
public:
  // 构造函数的using不管在哪，都不会改变构造函数的访问级别，基类public的constructor就算在子类private里面using，也还是public
  // 构造函数的默认参数不会被继承，using会得到多个构造函数，每个构造函数省略几个默认参数
  using ObjConstructor::ObjConstructor;

  DerivedObjConstructor(int i, std::string s, int d) : ObjConstructor(i, s), derived_i(d) {}
  void describe(std::ostream &os)
  {
    ObjConstructor::describe(os);
    os << ", " << OUTPUT_VAL(derived_i);
  }

private:
  int derived_i;
};

struct NonVirtualBase
{
  void some_func() // 这个是non-virtual method，编译期绑定
  {
    std::cout << "NonVirtualBase::some_func()" << std::endl;
  }
  void another_func() // 这个是non-virtual method，编译期绑定
  {
    std::cout << "NonVirtualBase::another_func()" << std::endl;
  }
};

struct VirtualDerived : public NonVirtualBase
{

  virtual void some_func() // 子类虽然可以覆盖父类的non-virtual method，但是这样写会迷糊
  {
    std::cout << "VirtualDerived::some_func()" << std::endl;
  }
  virtual void another_func(int i)
  {
    std::cout << "VirtualDerived::another_func(" << i << ")" << std::endl;
  }
};

struct VirtualDerived2 : public VirtualDerived
{
  void some_func() override
  {
    std::cout << "VirtualDerived2::some_func()" << std::endl;
  }
  void another_func(int i) override
  {
    std::cout << "VirtualDerived2::another_func(" << i << ")" << std::endl;
  }
};

struct NoDefaultConstructorBase
{
public:
  NoDefaultConstructorBase() = delete;
  NoDefaultConstructorBase(int ii) : i(ii)
  {
    std::cout << "NoDefaultConstructorBase::constructor" << std::endl;
  }

private:
  int i;
};

struct NoDefaultConstructorDerived : public NoDefaultConstructorBase
{
public:
  NoDefaultConstructorDerived(int ii, double dd) : NoDefaultConstructorBase(ii), d(dd)
  {
    std::cout << "NoDefaultConstructorDerived::constructor" << std::endl;
  }

private:
  double d;
};

struct DemoObjDestructorBase
{
  virtual ~DemoObjDestructorBase()
  {
    // 析构的时候会固定调用DemoObjDestructorBase::print
    print();
  }
  virtual void print()
  {
    std::cout << "DemoObjDestructorBase destructor" << std::endl;
  }
};

struct DemoObjDestructorDerived1 : public DemoObjDestructorBase
{
  virtual ~DemoObjDestructorDerived1()
  {
    // 析构的时候会固定调用DemoObjDestructorDerived1::print
    print();
  }
  void print() override
  {
    std::cout << "DemoObjDestructorDerived1 destructor" << std::endl;
  }
};

struct DemoObjDestructorDerived2 : public DemoObjDestructorDerived1
{
  virtual ~DemoObjDestructorDerived2()
  {
    // 析构的时候会固定调用DemoObjDestructorDerived2::print
    print();
  }
  void print() override
  {
    std::cout << "DemoObjDestructorDerived2 destructor" << std::endl;
  }
};
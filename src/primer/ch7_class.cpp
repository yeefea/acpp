#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include "sales_data.h"
#include "screen.h"
#include "account.h"
#include "utils.h"

/*
class
struct

constructor
destructor

3/5 rule

typedef
using

friend
friend class
public
protected
private

const
default
delete
inline
explicit，出现在构造函数的声明处，在类外定义时不能用
mutable
constexpr
static

*/
void demo_sales_data()
{
    std::string input_txt = "bk001 10 123.0";
    std::stringstream ss(input_txt);

    Sales_data total;
    if (read(ss, total))
    {
        print(std::cout, total);
        // Sales_data trans;
    }
}

void demo_screen()
{
}

void demo_account()
{
}

// DataPackage是一个aggregate class
// 可以用{...}初始化，和C语言一样
struct DataPackage
{
    int version;
    std::string key;
    std::string value;
};
std::ostream &operator<<(std::ostream &os, const DataPackage &dp)
{
    os << "DataPackage{" << dp.version << ", \"" << dp.key << "\", \"" << dp.value << "\"}";
    return os;
}
void demo_agg_class()
{
    DataPackage data1{1, "k1", "v1"};
    DataPackage data2{2, "k22", "v222"};

    std::cout << OUTPUT_VAL(data1) << std::endl;
    std::cout << OUTPUT_VAL(data2) << std::endl;
}

class Debug
{
public:
    constexpr Debug(bool b = true)
        : hw(b), io(b), other(b) {}
    constexpr Debug(bool h, bool i, bool o)
        : hw(h), io(i), other(o) {}
    constexpr bool any() const // 书上这里没有const后缀，导致无法编译
    {
        return hw || io || other;
    }

private:
    bool hw;
    bool io;
    bool other;
};

struct ConstData
{
    int f1;
    int f2;
    double f3;
};

std::ostream &operator<<(std::ostream &os, const ConstData &dp)
{
    os << "ConstData{" << dp.f1 << ", " << dp.f2 << ", " << dp.f3 << "}";
    return os;
}

constexpr int get_size()
{
    return 42;
}
void demo_constexpr_class()
{
    // 1. 聚合类，数据成员都是字面值常量
    constexpr int c1 = get_size();
    constexpr ConstData const_data{c1, 2, 3.0f};
    std::cout << const_data << std::endl;

    // 2. 非聚合类
    constexpr Debug io_sub(false, true, false);
    if (io_sub.any())
    {
        std::cerr << "print approriate error msg" << std::endl;
    }
}

void demo_static_member(){
    
}

int main(int argc, char **argv)
{
    RUN_DEMO(demo_sales_data);
    RUN_DEMO(demo_screen);
    RUN_DEMO(demo_account);

    RUN_DEMO(demo_agg_class);
    RUN_DEMO(demo_constexpr_class);
    return EXIT_SUCCESS;
}
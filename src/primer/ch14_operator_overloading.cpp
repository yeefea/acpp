#include <iostream>
#include <cstdint>

using namespace std;

class MyInt
{

public:
    int i;
    explicit MyInt(int i) : i(i) {}
};

MyInt operator+(const MyInt &lhs, const MyInt &rhs)
{
    MyInt ret(lhs.i + rhs.i);
    return ret;
}

ostream &operator<<(ostream &os, const MyInt &rhs)
{
    os << rhs.i;
    return os;
}

MyInt operator<<(const MyInt &lhs, const MyInt &rhs)
{
    return MyInt(lhs.i << rhs.i);
}

class SalesData
{

public:
    string isbn;
    int units_sold;
    double revenue;
    // 所有单参数的构造函数都必须是显示的，只有极少数情况下拷贝构造函数可以不声明称explicit。例如作为其他类的透明包装器的类。
    explicit SalesData(string isbn) : isbn(isbn) {}
    SalesData(string isbn, int units_sold, double revenue) : isbn(isbn), units_sold(units_sold), revenue(revenue) {}
    double average_price() const { return revenue / units_sold; }
};

ostream &operator<<(ostream &os, const SalesData &item)
{
    os << item.isbn << " " << item.units_sold << " " << item.average_price();
    return os;
}

SalesData operator+(const SalesData &lhs, const SalesData &rhs)
{
    return SalesData(lhs.isbn, lhs.units_sold + rhs.units_sold, lhs.revenue + rhs.revenue);
}

bool operator==(const SalesData &lhs, const SalesData &rhs)
{
    return lhs.isbn == rhs.isbn && lhs.units_sold == rhs.units_sold && lhs.revenue == rhs.revenue;
}

int main(int argc, char **argv)
{
    string s = "123";
    SalesData item0(s);
    SalesData item{"123123-111", 10, 20.3};
    cout << item << endl;

    MyInt i(10);
    cout << (i << MyInt(3)) << endl;
    return 0;
}
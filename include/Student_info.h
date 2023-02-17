#ifndef GUARD_Student_info
#define GUARD_Student_info

#include <iostream>
#include <string>
#include <vector>

// public private
class Student_info
{
private:
    std::string n;

public:
    // constructors

    /*
    初始化过程
    1. 分配内存
    2. 用初始化列表初始化对象
    3. 执行构造函数

    */
    Student_info() : midterm(0), final(0){}; // 默认constructor，初始化列表
    Student_info(std::istream &is) { read(is); };
    std::string name;
    std::string get_name() const;
    bool valid() const;
    double midterm, final;
    std::vector<double> homework;
    std::istream &read(std::istream &); // 成员函数
    double grade() const;               // const成员函数，保证不修改对象内部状态，可以在const对象上调用
    std::string describe() const;
    // 可以认为const基本就是read-only函数
};
bool compare(const Student_info &, const Student_info &);
std::istream &read(std::istream &, Student_info &);
std::istream &read_hw(std::istream &, std::vector<double> &);

#endif
#include <iostream>

void demo_io()
{

    std::cout << "Please enter your first name: ";
    std::string name;
    std::cin >> name;
    // build the message that we intend to write
    const std::string greeting = "Hello, " + name + "!";

    // build the second and fourth lines of the output
    const std::string spaces(greeting.size(), ' ');
    const std::string second = "* " + spaces + " *";

    // build the first and fifth lines of the output
    const std::string first(second.size(), '*');

    // write it all
    std::cout << std::endl;
    std::cout << first << std::endl;
    std::cout << second << std::endl;
    std::cout << "* " << greeting << " *" << std::endl;
    std::cout << second << std::endl;
    std::cout << first << std::endl;
}

void demo_types()
{

    // string

    std::string s1 = "s1";
    std::string s2(10, '*');
    std::string s3; // implicit init

    std::cout << s1 << ' ' << s2 << ' ' << s3 << std::endl;

    // const
    const std::string hello = "hello";
    const std::string msg = hello + " world!";

    std::cout << hello << ' ' << msg << std::endl;

    const std::string exclam = "!";
    const std::string message = exclam + "Hello" + ", world"; // ok
    // 错误，两个string literal不能+
    // const std::string message = "Hello" + ", world" + exclam;
}

int ex_1_3()
{
    {
        const std::string s = "a string";
        std::cout << s << std::endl;
    }

    {
        const std::string s = "another string";
        std::cout << s << std::endl;
    }
    return 0;
}

int ex_1_4()
{
    {
        const std::string s = "a string";
        std::cout << s << std::endl;
        {
            const std::string s = "another string";
            std::cout << s << std::endl;
        }
    }
    return 0;
}
int ex_1_5()
{
    {
        std::string s = "a string";
        {
            std::string x = s + ", really";
            std::cout << s << std::endl;
        }
        // 这里已经在x的作用域外了，报错
        // std::cout << x << std::endl;
    }
    return 0;
}

int main()
{
    // demo_io();
    // demo_types();
    ex_1_3();
    ex_1_4();
    ex_1_5();
}

#include <iostream>

void demo_while_loop()
{
    std::cout << "enter your first name: ";
    std::string name;
    std::cin >> name;
    const std::string greeting = "hello, " + name + "!";

    const int pad = 1;
    const int rows = pad * 2 + 3;

    std::cout << std::endl;

    const std::string::size_type cols = greeting.size() + pad * 2 + 2;
    int r = 0;
    while (r != rows)
    {

        std::cout << std::endl;
        ++r;
    }

    std::string::size_type c = 0;
    while (c != cols)
    {
        if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1)
        {
            std::cout << "*";
        }
        else
        {
            if (r == pad + 1 && c == pad + 1)
            {
                std::cout << greeting;
                c += greeting.size();
            }
            else
            {
                std::cout << " ";
            }
        }
    }
}

void demo_if()
{
}

void demo_for_loop()
{

    
}

int main()
{
    demo_while_loop();
    demo_if();
    return 0;
}

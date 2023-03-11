#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include "sales_data.h"
#include "screen.h"
#include "account.h"
#include "utils.h"

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

int main(int argc, char **argv)
{
    RUN_DEMO(demo_sales_data);
    RUN_DEMO(demo_screen);
    RUN_DEMO(demo_account);
    return EXIT_SUCCESS;
}
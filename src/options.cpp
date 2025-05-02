#include "options.h"
#include <iostream>

void oddOrEven(int number)
{
    if (number == -1)
    {
        return;
    }
    std::string ooe = number % 2 == 0 ? "Even" : "Odd";
    std::cout << "Number is " << ooe << "." << std::endl;
}

void greeting(std::string name)
{
    if (name == "")
    {
        return;
    }
    std::cout << "Hello " << name << "!" << std::endl;
}
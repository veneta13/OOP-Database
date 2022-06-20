#include "executor.hpp"
#include <iostream>

int main()
{
    Executor executor;
    while (executor.enter(std::cout, std::cin)) ;
}
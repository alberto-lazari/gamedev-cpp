#include <iostream>

// Empty class
class C {};

int main()
{
    // At least 1 byte allocated
    std::cout << sizeof(C) << std::endl;
}

#include <iostream>

// error: ua is not at the end
// struct S
// {
//     int ua[];
//     int x;
// };
// S s{};

// struct S
// {
//     // error: array bound cannot be deduced from a default member initializer
//     int ua[] { 0, 1, 2 };
//     int x;
// };

// This is legal, to ensure variable length arrays are possible
struct S
{
    int x;
    int ua[];
};

int main()
{
    std::cout << std::format("# Integer types\n"
        "bool: {}\nchar: {}, short: {}, unsigned: {}, int: {}, long: {}, long long: {}\n",
        sizeof(bool),
        sizeof(char),
        sizeof(short),
        sizeof(unsigned),
        sizeof(int),
        sizeof(long),
        sizeof(long long)
    );

    std::cout << "size_t: " << sizeof(size_t) << std::endl;

    int array_identifier[10] {};
    int* array_ptr = array_identifier;
    std::cout << std::format("# Composite types\n"
        "array identifier [10]: {}, array ptr: {}\n",
        sizeof(array_identifier),
        sizeof(array_ptr)
    );

    // error: definition of variable with array type needs an explicit size or an initializer (list)
    // int unsized_array_identifier[];
    // error: invalid application of 'sizeof' to an incomplete type 'int[]'
    // sizeof(unsized_array_identifier)

    // This is nullptr
    int unsized_array_identifier[] {};
    std::cout << "unsized array identifier: " << sizeof(unsized_array_identifier) << std::endl;
}

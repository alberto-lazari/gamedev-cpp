#include <iostream>

// Field order is not completely standardized.
// Fields are only ordered within the same access visibility:
// - a < b
// - c < d
//
// This allows many possible orderings:
// - a b c d
// - c d a b
// - a c b d
// - ...
class C
{
public:
    int a;
    int b;

protected:
    int c;
    int d;

public:
    void print_alignment()
    {
        long addr = (long)this;
        std::cout << std::format("C: {}\nC.a: {}\nC.b: {}\nC.c: {}\nC.d: {}",
            addr,
            (long)&a - addr,
            (long)&b - addr,
            (long)&c - addr,
            (long)&d - addr
        ) << std::endl;
    }
};

int main()
{
    std::cout << "sizeof(C): " << sizeof(C) << std::endl;
    std::cout << "alignof(C): " << alignof(C) << std::endl;
    C().print_alignment();
}

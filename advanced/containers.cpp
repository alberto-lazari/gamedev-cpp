#include <set>
#include <vector>
#include <iostream>

class C
{
};

class LessC
{
public:
    bool operator()(const C& left, const C& right) const
    {
        return &left < &right;
    }
};

int main()
{
    std::set<C> cset;
    // Does not compile, requires std::less<C>
    // cset.insert(C());
    
    std::set<C, LessC> cposet;
    cposet.insert(C());

    std::vector<int> iv;
    iv.push_back(1);
    int* iptr = &iv[0];

    std::vector<bool> bv;
    bv.push_back(true);
    // Does not compile, since std::vector<bool> is a bitset under the hood
    // and it's not possible to address the exact value via native pointer.
    // bool* bptr = &bv[0];
}

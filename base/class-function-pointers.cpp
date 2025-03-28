#include <iostream>

class A {
public:
  A() {
    std::cout << "A()\n";
  }

  int fun(char, float) {
    std::cout << "A::fun()\n";
    return 0;
  }
};

int main() {
  int (A::* fun_ptr)(char, float) = &A::fun;

  A a;
  // error: reference to non-static member function must be called
  // int (* ptr)(char, float) = a.*fun_ptr;
  (a.*fun_ptr)('a', .0f);

  A* a_ptr { new A };
  (a_ptr->*fun_ptr)('a', .0f);
}

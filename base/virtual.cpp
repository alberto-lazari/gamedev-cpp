#include <iostream>

class A {
public:
  virtual void fun() {
    std::cout << "A::fun()\n";
  }

  virtual ~A() {
    std::cout << "~A()\n";
  }
};

class B : public A {
public:
  void fun() override {
    std::cout << "B::fun()\n";
  }

  virtual ~B() {
    std::cout << "~B()\n";
  }
};

int main() {
  B* b = new B;
  A* a = b;
  a->fun();
  delete a;
}

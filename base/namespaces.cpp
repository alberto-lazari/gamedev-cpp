#include <iostream>

namespace A {
  int x = 0;
  int z = 1;

  namespace B {
    // Shadowing on A::x;
    int x = 1;
  }
}

// Since C++17
namespace A::B::C {
  int x = 2;
}

// Namespaces are merged on multiple definitions
// Warning: chance of adding definitions to already defined namespaces
namespace A::B {
  // Sees A::B::x, because it's in the same namespace;
  int y = -x;

  namespace C {
    int y = A::x;
  }
}

int main() {
  // Error: undeclared identifier 'x'
  // std::cout << "x = " << x << std::endl;
  using namespace A::B::C;
  std::cout << "A::B::C::x = " << x << std::endl;
  // Error: undeclared identifier 'z'
  // std::cout << "A::z = " << z << std::endl;
  std::cout << "A::B::y = " << A::B::y << std::endl;
  std::cout << "A::B::C::y = " << A::B::C::y << std::endl;
}

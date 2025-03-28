#include <iostream>
#include <memory>

class Obj {
public:
  int x {};

  Obj() {}
  Obj(int x) : x(x) {
    std::cout << "Obj(" << x << ")\n";
  }

  ~Obj() {
    std::cout << "~Obj()\n";
  }
};

int main() {
  // Unique pointer
  {
    std::unique_ptr a = std::make_unique<Obj>();

    // Cannot copy a unique pointer directly (has to be unique)
    // std::unique_ptr<int> b = a;

    // This makes a = nullptr
    std::unique_ptr b = std::move(a);

    std::cout << "End of the scope, destroying b\n";
  }

  // Shared pointer
  {
    std::shared_ptr shared = std::make_shared<Obj>();
    {
      std::shared_ptr copy = shared;
      std::cout << "End of the scope, destroying copy, but shared is still allocated\n";
    }
    std::cout << "End of the scope, destroying shared\n";
  }

  // Weak pointer
  {
    auto shared = std::make_shared<Obj>(2);
    std::weak_ptr weak = shared;
    std::cout << "weak_ptr = " << weak.lock()->x << std::endl;
  }
}

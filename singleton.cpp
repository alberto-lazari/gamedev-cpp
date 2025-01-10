#include <iostream>

class Singleton {
public:
  static Singleton& get() {
    static Singleton* const INSTANCE = new Singleton();
    return *INSTANCE;
  }

private:
  Singleton() {
    std::cout << "new Singleton()" << std::endl;
  }
};

int main() {
  // `new Singleton()` gets called only once
  Singleton::get();
  Singleton::get();
  Singleton::get();
}

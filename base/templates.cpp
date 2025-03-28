#include <iostream>

template <class T1, typename T2> T1 Add(const T1& x, const T2& y) {
  // Type variables can be instantiated
  T1* ptr = new T1;
  T2 uninit;
  return x + y + *ptr + uninit;
}

template <int x = 1, class T = int> T Add(const T& y) {
  return x + y;
}

int main() {
  std::cout << "x + y = " << Add(1, 2) << std::endl;
  std::cout << "x + y = " << Add(1., 2.f) << std::endl;
  std::cout << "x + y = " << Add<2>(1l) << std::endl;
  std::cout << "x + y = " << Add(2.f) << std::endl;
}

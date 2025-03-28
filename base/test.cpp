#include <iostream>
#include <format>

void fun() {
  std::cout << "fun()" << std::endl;
}

int main(const int argc, const char* argv[]) {
  auto string = "hi";
  std::cout << string << std::endl;
  const int const_x {};
  std::cout << "# Before const cast:\nconst_x = " << const_x << std::endl;
  int* mut_x = const_cast<int*>(&const_x);
  // UB
  *mut_x = 1;
  std::cout << std::format(
      "# After const cast:\n"
      "const_x = {}\n"
      "mut_x = {}\n"
      "*(&const_x) = {} (UB!!!)",
      const_x, *mut_x, *(&const_x)
  ) << std::endl;
  void* n = nullptr;
  for (int i = 1; i < argc; i++) {
    auto arg = argv[i];
    std::cout << arg << std::endl;
  }

  // Always double
  auto div = 1.0 / 2;
  auto quot = 1 / 2.0;
}

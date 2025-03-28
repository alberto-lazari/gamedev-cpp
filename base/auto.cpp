const int& ref() {
  return *(new int {1});
}

int* ptr() {
  return new int {1};
}

int main() {
  // x is `int`
  // const and reference is lost with auto
  auto x = ref();
  const int& y = ref();
  // pointers are preserved
  auto z = ptr();
}

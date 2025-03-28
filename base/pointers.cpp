void f(int x) {}
void f(float* f) {}

int* fun() {
  int x {};
  // warning: address of stack memory associated with local variable
  return &x;
}

int id(int x) {
  return x;
}

int call(int (* function)(int), int arg) {
  return function(arg);
}

int main() {
  int x = 1;
  void* v = &x;
  // Initialized to nullptr
  int* null {};
  int** d {};
  // sizeof pointers is always 8 (in 64-bit architectures)
  auto size = sizeof(v);
  // error: arithmetic on a pointer to void
  // This is not possible because `sizeof(void)` is not valid
  // ++v;

  // Ambiguous call: 0L is NULL, could be confused with pointer
  // f(0L);

  // f(int)
  f(0);
  // f(float*)
  f(nullptr);

  // UB
  int garbage = *fun();

  x = id(x);
  x = call(id, x);
  // Equivalent to the above
  x = call(&id, x);

  int (* function)(int) = id;
  // Return type is optional in lambdas
  // int (* lambda)(int) = [](int x) -> int { return x; };
  int (* lambda)(int) = [](int x) { return x; };

  int array[] { 1, 2, 3 };
  int matrix[][2] { { 1, 2 }, { 3, 4 } };
  // Could also be flat.
  // Need to manage the rows logically
  int flat_matrix[4] { 1, 2, 3, 4 };
  int cube[][2][2] { { { 1, 2 }, { 3, 4 } }, { { 4, 6 }, { 7, 8 } } };

  // This initializes the array
  char string[] = "hello";
  // This only resturns the pointer to the literal (not modifiable)
  const char* string_ptr = "hello";
}

#include <iostream>
#include <string>

void print(const int* array, int size) {
  for (int i = 0; i < size; ++i) {
    std::cout << array[i] << " ";
  }
  std::cout << std::endl;
}

int bell_jagged(int n) {
  if (n < 0) {
    // B_0 is 1. Return -1 as error code
    return n == 0 ? 1 : -1;
  }
  int* previous = new int[1] { 1 };
  // print(previous, 1);
  for (int row = 1; row < n; ++row) {
    int* current = new int[row + 1];
    current[0] = previous[row - 1];
    for (int col = 1; col < row + 1; ++col) {
      current[col] = current[col - 1] + previous[col - 1];
    }
    delete[] previous;
    previous = current;
    // print(current, row + 1);
  }
  int B = previous[n - 1];
  delete[] previous;
  return B;
}

/**
 * @param n n-th Bell number to find. Should be > 0
 * @return B_n, where B_i is the i-th Bell number, or -1 if n < 0
 */
int bell(int n) {
  return bell_jagged(n);
}

int main(const int argc, const char* argv[]) {
  if (argc < 2) {
    return 1;
  }
  const int n = std::stoi(argv[1]);
  if (n < 0) {
    std::cout << "B_{" << n << "} = undefined\n";
    return 1;
  }
  const int Bn = bell(n);
  std::cout << "B_" << n << " = " << Bn << std::endl;
}

#include <iostream>
#include <string>

void print(const int* array, unsigned size) {
  for (unsigned i = 0; i < size; ++i) {
    std::cout << array[i] << " ";
  }
  std::cout << std::endl;
}

unsigned bell_jagged(unsigned n) {
  if (n < 2) {
    // B_0 = B_1 = 1
    return 1;
  }
  unsigned* previous = new unsigned[1] { 1 };
  unsigned* current;

  // Original algorithm
  for (unsigned row = 1; row < n; ++row, previous = current) {
    current = new unsigned[row + 1];
    current[0] = previous[row - 1];
    for (unsigned col = 0; col < row; ++col) {
      current[col + 1] = current[col] + previous[col];
    }
    delete[] previous;
  }
  const unsigned B_n = current[n - 1];
  delete[] current;
  return B_n;
}

/**
 * Index of B_n in the flat representation of the triangle
 * 1  (1)
 * 2  (1) (2)
 * 3  (2)  3 (5)
 * 4  (5)  7  10 (15)
 * 5  (15) 20 27  37 (52)
 * ...
 *
 *     1   2       3           4               5
 *    [0] [1] +1  [2] +1  +2  [3] +1  +2  +3  [4]
 * => (1) (2)  3  (5)  7   10 (15) 20  27  37 (52) ...
 *
 * => n - 1 + sum^(n - 2) i,  where sum^n i = ( n * (n + 1) ) / 2
 *  = n - 1 + ( (n - 2) * (n - 1) ) / 2
 *  = ( 2n - 2 + n^2 - 2n - n + 2 ) / 2
 *  = ( n^2 - n ) / 2
 *  = ( n * (n - 1) ) / 2
 *
 * Note that this is even true for n in {0, 1, 2}:
 * case n = 0 -> ( 0 * -1 ) / 2 = 0
 * case n = 1 -> ( 1 *  0 ) / 2 = 0
 * case n = 2 -> ( 2 *  1 ) / 2 = 1
 */
unsigned B_index(unsigned n) {
  return ( n * (n - 1) ) / 2;
}

unsigned bell_flat(unsigned n) {
  if (n < 2) {
    // B_0 = B_1 = 1
    return 1;
  }
  unsigned* const flat_t = new unsigned[B_index(n) + 1];
  // Initializations are ok, because n >= 2 (early return)
  flat_t[0] = 1;
  flat_t[1] = 2;

  unsigned* previous = flat_t;
  unsigned* current = flat_t + 1;
  for (unsigned i = 2; i < n;
       current = i++ + (previous = current)
  ) {
    for (unsigned col = 0; col < i; ++col) {
      current[col + 1] = previous[col] + current[col];
    }
  }

  const unsigned B_n = *current;
  delete[] flat_t;
  return B_n;
}

/**
 * @param n n-th Bell number to find.
 * @return B_n, where B_i is the i-th Bell number
 */
unsigned bell(unsigned n) {
  return bell_flat(n);
}

int main(int argc, const char* argv[]) {
  if (argc < 2) {
    return 1;
  }
  const int n = std::stoi(argv[1]);
  if (n < 0) {
    std::cerr << "B_(" << n << ") = undefined\n";
    return 1;
  }
  const unsigned Bn = bell(n);
  std::cout << "B_" << n << " = " << Bn << std::endl;
}

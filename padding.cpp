#include <stdio.h>

struct A {
  bool a;
  bool b;
  bool c;
  bool d;
};

struct B {
  bool a;
  bool b;
  bool c;
  bool d;
  bool e;
};

// Int always performs padding to 4 bytes, whatever the actual size of variables
struct C {
  int i00 : 1;
  int i01 : 1;
  int i02 : 1;
  int i03 : 1;
  int i04 : 1;
  int i05 : 1;
  int i06 : 1;
  int i07 : 1;
};

struct bit {
  bool b : 1;
};

// Bool performs padding to 1 byte
struct D {
  bool b00 : 1;
  bool b01 : 1;
  bool b02 : 1;
  bool b03 : 1;
  bool b04 : 1;
  bool b05 : 1;
  bool b06 : 1;
  bool b07 : 1;
  bool b08 : 1;
  bool b09 : 1;
  bool b10 : 1;
  bool b11 : 1;
  bool b12 : 1;
  bool b13 : 1;
  bool b14 : 1;
  bool b15 : 1;
};

struct large {
  bool b : 1;
  int x;
};

struct little {
  bool b : 1;
  short x;
};

struct larger {
  bool b : 1;
  long x;
};

struct super {
  bool b : 1;
  long long x;
};

struct composed {
  bool b : 1;
  larger l;
};

int main() {
  printf("Alignment is based on the largest type in the struct.\n");
  printf("Can be: alignment = b bytes,\nwith b in {1, 2, 4, 8}\n");
  printf("Sizes:\n");
  printf("A: %zu, B: %zu, C: %zu, D: %zu, bit: %zu, little: %zu, large: %zu, larger: %zu, super: %zu, composed: %zu\n",
      sizeof(A), sizeof(B), sizeof(C), sizeof(D), sizeof(bit), sizeof(little), sizeof(large), sizeof(larger), sizeof(super), sizeof(composed));
}

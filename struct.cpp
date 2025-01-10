#include <iostream>

// C-style struct declaration
typedef struct c_struct {
  int x;
  void (*set)(c_struct*, int) =
    (void (*)(c_struct*, int)) [](c_struct* self, int x) { self->x = x; };
} c_struct;

// C++-style struct declaration (similar to class)
struct CppStruct {
  int x;
};

// Class-like struct
struct cl {
  int x;
  void set(int x) {
    // `this` pointer is accessible in all structs styles in C++
    this->x = x;
  }
};

struct BitFieldStruct {
  // Specify bit lenght of fields
  bool b1 : 1;
  bool b2 : 1;
  int s : 8;
};

int main() {
  c_struct cs = { 1 };
  cs.set(&cs, 0);
  std::cout << "c_struct.x = " << cs.x << std::endl;

  CppStruct cpps = { 2 };
  std::cout << "CppStruct.x = " << cpps.x << std::endl;

  cl* obj = new cl;
  obj->set(3);
  std::cout << "cl.x = " << obj->x << std::endl;
}

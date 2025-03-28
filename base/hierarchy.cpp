#include <iostream>

struct cPoint2D {
  int x, y;
};

struct cPoint3D {
  cPoint2D super;
  int z;
};

class Point2D {
protected:
  int x, y;
};

class Point3D : public Point2D {
  int z;

  // `super` is not a keyword in C++, since pointers get converted automatically
  Point2D super() {
    // `this` gets converted to Point2D
    return *this;
  }

  int get_x() {
    return Point2D::x;
  }
};

class A {
public:
  int a = 1;

  ~A() {
    std::cout << "Destroying A\n";
  }
};

class B {
public:
  int b = 2;

  ~B() {
    std::cout << "Destroying B\n";
  }
};

class Multi : public A, public B {
public:
  ~Multi() {
    std::cout << "Destroying Multi\n";
  }
};

class VirtualA {
public:
  int a = 1;

  // This always destroys the dynamic type (possibly calls the subclass destroyer)
  virtual ~VirtualA() {
    std::cout << "Destroying VirtualA\n";
  }
};

class VirtualB {
public:
  int b = 2;

  // This always destroys the dynamic type (possibly calls the subclass destroyer)
  virtual ~VirtualB() {
    std::cout << "Destroying VirtualB\n";
  }
};

class VirtualObj : public VirtualA, public VirtualB {
public:
  ~VirtualObj() {
    std::cout << "Destroying VirtualObj\n";
  }
};

int main() {
  Multi* obj = new Multi;
  std::cout << "(B*).b = " << ((B*) obj)->b << std::endl;
  // This highlights the fact that Multi's structure is something like:
  // class Multi {
  //   A {
  //     int a;
  //   };
  //   B {
  //     int b;
  //   };
  // }
  //
  // When just reinterpreting the cast, the first integer is actually A's one.
  std::cout << "reinterpret_cast<B*>.b = " << reinterpret_cast<B*>(obj)->b << std::endl;

  A* A_obj = obj;
  // Memory leak!!
  // Only A's part of obj is destroyed
  delete A_obj;

  VirtualA* virtual_A_obj = new VirtualObj;
  delete virtual_A_obj;

  // The virtual table probably messes up the object structure
  std::cout << "(B*).b = " << ((B*) virtual_A_obj)->b << std::endl;
}

# My C++ Repo

Exercises for the C++ introduction course.


## Lectures

### Base Course

1. [`true`](base/true.cpp), [`test`](base/test.cpp), compiler, syntax, variables, const
2. [`inside`](base/inside.cpp), bool, operators, functions
3. preprocessor, pointers
4. [`pointers`](base/pointers.cpp), function pointers, arrays, [`libstring.h`](base/libstring.h), [`bell`](base/bell.cpp)
5. [`enum`](base/enum.cpp),
  [`struct`](base/struct.cpp),
  [`auto`](base/auto.cpp),
  const,
  [`namespaces`](base/namespaces.cpp),
  [`check-sentence-automata`](base/check-sentence.cpp)
6. classes (OOP)
7. [`hierarchy`](base/hierarchy.cpp), [`virtual`](base/virtual.cpp), [`class-function-pointers`](base/class-function-pointers.cpp)
8. [`templates`](base/templates.cpp), [`smart-pointers`](base/smart-ptr.cpp)

### Advanced Course

1. Allocation
2. `new` operator vs `operator new`, custom allocation strategies, in-place allocation
3. [`sizeof`](advanced/sizeof.cpp), [`alignment`](advanced/alignment.cpp)
4. [`class-alignment`](advanced/class-alignment.cpp), fixed allocator

## Usage

The [util/](util) directory contains wrappers to compile, run, and debug individual `.cpp` files as scripts, on a Clang environment.

For example,
the following compiles and runs the `test.cpp` file, passing `arg` and `val` as arguments:

```sh
util/run test.cpp [arg1 arg2 ...]
```

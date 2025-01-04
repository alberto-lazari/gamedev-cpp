# My C++ Repo

Exercises for the C++ introduction course.


## Lectures

- Lecture 1: [`true`](true.cpp), [`test`](test.cpp), compiler, syntax, variables, const
- Lecture 2: [`inside`](inside.cpp), bool, operators, functions
- Lecture 3: preprocessor, pointers
- Lecture 4: [`pointers`](pointers.cpp), function pointers, arrays, [`libstring.h`](libstring.h), [`bell`](bell.cpp)


## Usage

The [util/](util) directory contains wrappers to compile, run, and debug individual `.cpp` files as scripts, on a Clang environment.

For example the following compiles and runs the `test.cpp` file, passing `arg` and `val` as arguments:
```sh
util/run test.cpp arg val
```

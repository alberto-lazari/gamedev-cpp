#include <cstdarg>
#include <cmath>
#include <iostream>
#include "libstring.h"

unsigned string::strlen(const char* string) {
  const char* c;
  for (c = string; *c != '\0'; ++c);
  return c - string;
}

unsigned string::count(const char* string, char sym) {
  unsigned count = 0;
  for (const char* c = string; *c != '\0'; ++c) {
    if (*c == sym) {
      ++count;
    }
  }
  return count;
}

char* string::join(const char* s1, const char* s2) {
  char* const joined = new char[strlen(s1) + strlen(s2) + 1];
  char* j = joined;
  // Copy s1
  for (const char* c = s1; *c != '\0'; ++c, ++j) {
    *j = *c;
  }
  // Copy s2
  for (const char* c = s2; *c != '\0'; ++c, ++j) {
    *j = *c;
  }
  // Add trailing '\0'
  *j = '\0';
  return joined;
}

char* string::substr_until(const char* string, char end_c) {
  unsigned len = 0;
  for (const char* c = string; *c != '\0' && *c != end_c; ++c, ++len);

  char* const substr = new char[len + 1];
  char* s = substr;
  for (const char* c = string; c - string < len; ++c, ++s) {
    *s = *c;
  }
  *s = '\0';
  return substr;
}

int string::split(const char* string, char split_c, char*** _parts) {
  const unsigned parts_n = count(string, split_c) + 1;
  char** const parts = new char*[parts_n];
  const char* c = string;
  for (unsigned part = 0; part < parts_n; ++part) {
    char* part_s = substr_until(c, split_c);
    parts[part] = part_s;
    c += strlen(part_s) + 1;
  }
  *_parts = parts;
  return parts_n;
}

// TODO
bool string::matches(const char* string, const char* pattern) {
  return false;
}

char* string::sprintf(const char* fmt, ...) {
  const unsigned argc = count(fmt, '%');
  if (argc == 0) {
    return join("", fmt);
  }
  std::va_list args;
  va_start(args, fmt);
  const char** args_s = new const char*[argc];
  unsigned args_len = 0;
  unsigned i;
  for (i = 0; i < argc; ++i) {
    const int arg = va_arg(args, int);
    const char* s = to_string(arg);
    args_s[i] = s;
    args_len += strlen(s);
  }

  char* const string = new char[strlen(fmt) - argc + args_len];
  char* c;
  for (i = 0, c = string; *fmt != '\0'; ++fmt) {
    if (*fmt != '%') {
      *c = *fmt;
      ++c;
      continue;
    }
    for (const char* arg = args_s[i]; *arg != '\0'; ++arg, ++c) {
      *c = *arg;
    }
    delete[] args_s[i++];
  }
  delete[] args_s;

  *c = '\0';
  return string;
}

char* string::to_string(int n) {
  char* string;
  const unsigned n_len = n < 0 ? std::log10(-n) + 1
    : n == 0 ? 1
    : std::log10(n) + 1;
  const unsigned len = n_len + (n < 0 ? 2 : 1);
  string = new char[len];

  char* s = string;
  if (n < 0) {
    n *= -1;
    *(s++) = '-';
  }
  for (int i = n_len; i > 0; --i, ++s) {
    const int number = (n % (int) std::pow(10, i)) / (int) std::pow(10, i - 1);
    *s = '0' + number;
  }

  *s = '\0';
  return string;
}

// TODO
void string::flog(const char* file_path, const char* string) {
}

int main() {
  std::cout << string::join("hel", "lo") << std::endl;
  std::cout << string::to_string(0) << std::endl;
  std::cout << string::to_string(2) << std::endl;
  std::cout << string::to_string(-102) << std::endl;
  std::cout << string::sprintf("x = %, y = %", 1, -2) << std::endl;
  const char* split = "1,2,3,4";
  char** parts;
  const unsigned parts_n = string::split(split, ',', &parts);
  std::cout << "Splits of " << split << ":\n";
  for (int i = 0; i < parts_n; ++i) {
    std::cout << "- " << parts[i] << std::endl;
  }
}

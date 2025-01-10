#include <iostream>

bool is_upper(char c) {
  return c >= 'A' && c <= 'Z';
}

bool is_lower(char c) {
  return c >= 'a' && c <= 'z';
}

bool is_period(char c) {
  switch (c) {
    case '.':
    case '!':
    case '?':
      return true;
    default:
      return false;
  }
}

void* init(char);
void* upper(char);
void* lower(char);
void* space(char);
void* comma(char);
void* period(char);
void* period_space(char);
void* error(char);

void* error(char input) {
  return (void*) (error);
}

void* init(char input) {
  return (void*) (is_upper(input) ? upper : error);
}

void* upper(char input) {
  return (void*) (
      is_upper(input) ? upper
      : is_lower(input) ? lower
      : input == ' ' ? space
      : input == ',' ? comma
      : is_period(input) ? period
      : error
  );
}

void* lower(char input) {
  return (void*) (
      is_lower(input) ? lower
      : input == ' ' ? space
      : input == ',' ? comma
      : is_period(input) ? period
      : error
  );
}

void* space(char input) {
  return (void*) (
      is_upper(input) ? upper
      : is_lower(input) ? lower
      : error
  );
}

void* comma(char input) {
  return (void*) (input == ' ' ? space : error);
}

void* period(char input) {
  return (void*) (input == ' ' ? init : error);
}


bool is_sentence_valid(const char* sentence) {
  if (*sentence == '\0') {
    return true;
  }
  void* state = (void*) init;
  for (const char* c = sentence; *c != '\0'; ++c) {
    void* (*step)(char) = (void* (*)(char)) state;
    char input = *c;
    state = step(input);
  }
  return state == period;
}

int main(int argc, const char* argv[]) {
  if (argc < 2) {
    return 1;
  }
  return is_sentence_valid(argv[1]) ? 0 : 1;
}

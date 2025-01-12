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

struct state {
  state* (* const transition)(char);
};

// Transitions
state* t_error(char);
state* t_init(char);
state* t_upper(char);
state* t_lower(char);
state* t_space(char);
state* t_comma(char);
state* t_period(char);

state* error = new state { t_error };
state* init = new state { t_init };
state* upper = new state { t_upper };
state* lower = new state { t_lower };
state* space = new state { t_space };
state* comma = new state { t_comma };
state* period = new state { t_period };

state* t_error(char input) {
  return error;
}

state* t_init(char input) {
  return is_upper(input) ? upper : error;
}

state* t_upper(char input) {
  return is_upper(input) ? upper
    : is_lower(input) ? lower
    : input == ' ' ? space
    : input == ',' ? comma
    : is_period(input) ? period
    : error;
}

state* t_lower(char input) {
  return is_lower(input) ? lower
    : input == ' ' ? space
    : input == ',' ? comma
    : is_period(input) ? period
    : error;
}

state* t_space(char input) {
  return is_upper(input) ? upper
    : is_lower(input) ? lower
    : error;
}

state* t_comma(char input) {
  return input == ' ' ? space : error;
}

state* t_period(char input) {
  return input == ' ' ? init : error;
}


bool is_sentence_valid(const char* sentence) {
  if (*sentence == '\0') {
    return true;
  }
  state* s = init;
  for (const char* c = sentence; *c != '\0'; ++c) {
    char input = *c;
    s = s->transition(input);
  }
  return s == period;
}

int main(int argc, const char* argv[]) {
  if (argc < 2) {
    return 0;
  }
  return is_sentence_valid(argv[1]) ? 0 : 1;
}

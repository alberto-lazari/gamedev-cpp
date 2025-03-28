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

// Wrap state transitions (the states themselves in a purely functional manner) as pointers,
// in order to allow indirect recursive typing.
// See OCaml implementation in `state_machine.ml` for a purely functional implementation,
// i.e. states are fully represented by fuctions.
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

// States
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


bool check(const char* sentence) {
  if (*sentence == '\0') {
    return true;
  }
  state* s = init;
  for (const char* c = sentence; *c != '\0'; ++c) {
    const char input = *c;
    // Perform transition and update the current state
    s = s->transition(input);
  }
  // Sentence is correct if it ends with a period
  return s == period;
}

int main(int argc, const char* argv[]) {
  if (argc > 1) {
    return check(argv[1]) ? 0 : 1;
  }
}

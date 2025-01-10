#include <iostream>

enum PodiumPlace {
  FIRST,
  SECOND,
  THIRD,
  // If enum has N significant values an additional COUNT one has value = N
  COUNT,
};

enum Visibility {
  VISIBLE,
  INVISIBLE,
  COLLAPSE_GEOMETRY,
};

// Does not compile: redefinition of enumerator 'VISIBLE|INVISIBLE'
// enum LabelVisibility {
//   VISIBLE,
//   INVISIBLE,
// };

// Scoped enum (C++ only)
// Always requires the use of `::` operator to disambiguate
enum class LabelVisibility {
  VISIBLE,
  INVISIBLE,
  COUNT,
};

enum Flags {
  FULLSCREEN_ENABLED  = 0b0001,
  AUDIO_ENABLED       = 0b0010,
  INVERT_X_AXIS       = 0b0100,
  INVERT_Y_AXIS       = 0b1000,
};

void setVisibility(Visibility v) {
  switch (v) {
    // Resolves to Visibility::VISIBLE, because LabelVisibility::Visibility is an enum class and
    // always requires :: operator to disambiguate
    case VISIBLE:
      std::cout << "[hello]" << std::endl;
      break;
    case Visibility::COLLAPSE_GEOMETRY:
      std::cout << "[]" << std::endl;
      break;
  default:
    std::cerr << "Undefined visibility of value " << v << std::endl;
  }
}

int main() {
  std::cout << "Numer of possible podium places (enum values): "
    << PodiumPlace::COUNT << std::endl;

  setVisibility(Visibility::VISIBLE);
  std::cout << "Possible label visibilities: "
    // Error: enum class needs explicit cast to int
    // << LabelVisibility::COUNT
    << (int) LabelVisibility::COUNT
    << std::endl;

  int settingsFlags = Flags::FULLSCREEN_ENABLED
    | Flags::INVERT_Y_AXIS
    | Flags::AUDIO_ENABLED;
  std::cout << "Audio: " << (settingsFlags & Flags::AUDIO_ENABLED
      ? "[x]" : "[ ]") << std::endl;
}

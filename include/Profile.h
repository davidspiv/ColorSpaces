#include "Color.h"

#include <array>
#include <string>

using namespace Color_Space;


struct Profile {
  std::string name;
  Xyz illuminant;

  std::array<Xyz, 3> primaries;
};

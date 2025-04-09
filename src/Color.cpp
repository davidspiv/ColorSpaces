#include "../include/Color.h"

using namespace Color_Space;


bool Color::operator==(const Color &other) const {
  auto [x, y, z] = m_values;
  auto [other_x, other_y, other_z] = other.get_values();
  return (x == other_x) && (y == other_y) && (z == other_z);
}

// Inequality comparison
bool Color::operator!=(const Color &other) const { return !(*this == other); }

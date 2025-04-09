#include "../include/Color.h"

#include <array>

using namespace Color_Space;


std::array<float, 3> Color::get_values() const { return m_values; }


Matrix Color::to_column() const {
  return Matrix({{m_values[0]}, {m_values[1]}, {m_values[2]}});
};


bool Color::operator==(const Color &other) const {
  auto [x, y, z] = m_values;
  auto [other_x, other_y, other_z] = other.get_values();
  return (x == other_x) && (y == other_y) && (z == other_z);
}


bool Color::operator!=(const Color &other) const { return !(*this == other); }

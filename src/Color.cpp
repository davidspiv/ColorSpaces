#include "../include/Color.h"

#include <array>

namespace Color_Space {


std::array<float, 3> Color::get_values() const { return m_values; }


Matrix Color::to_column() const {
  return Matrix({{m_values[0]}, {m_values[1]}, {m_values[2]}});
};


bool Color::operator==(const Color &other) const {
  auto [x, y, z] = m_values;
  float error = 1;
  auto [other_x, other_y, other_z] = other.get_values();
  return (std::abs(x - other_x) < error) && (std::abs(y - other_y) < error) &&
         (std::abs(z - other_z) < error);
}


bool Color::operator!=(const Color &other) const { return !(*this == other); }

}; // namespace Color_Space

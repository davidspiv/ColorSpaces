#include "../include/Color.h"

#include <iostream>

namespace Color_Space {


Xyy::Xyy(float x, float y, float Y, Illuminant_Label illuminant)
    : Color(x, y, Y, illuminant) {}


Xyz Xyy::to_xyz() const {
  const auto [x, y, Y] = m_values;

  const float X = (x * Y) / y;
  const float Z = ((1.0f - x - y) * Y) / y;

  return Xyz(X, Y, Z, m_illuminant);
}


void Xyy::print() const {
  std::cout << "[xyY]" << "\nx: " << m_values[0] << "\ny: " << m_values[1]
            << "\nY: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

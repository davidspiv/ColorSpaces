#include "../include/Color.h"

#include <iostream>

namespace Color_Space {


Xyy::Xyy(float x, float y, float Y, Illuminant_Label illuminant)
    : Color(x, y, Y, illuminant) {}


Xyz Xyy::to_xyz() const {
  auto [x, y, Y] = m_values;
  const double r_X = (x * Y) / y;
  const double r_Y = Y;
  const double r_Z = ((1 - x - y) * Y) / y;

  return Xyz(r_X, r_Y, r_Z);
};


void Xyy::print() const {
  std::cout << "[xyY]" << "\nx: " << m_values[0] << "\ny: " << m_values[1]
            << "\nY: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

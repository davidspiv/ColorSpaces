#include "../include/Color.h"

#include <iostream>

namespace Color_Space {


Xyy::Xyy(float x, float y, float Y, Illuminant_Label illuminant)
    : Color(x, y, Y, illuminant) {}


void Xyy::print() const {
  std::cout << "[xyY]" << "\nx: " << m_values[0] << "\ny: " << m_values[1]
            << "\nY: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

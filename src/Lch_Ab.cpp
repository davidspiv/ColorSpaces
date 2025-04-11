#include "../include/Color.h"
#include "../include/util.h"

#include <array>
#include <cmath>
#include <iostream>

namespace Color_Space {


Lch_Ab::Lch_Ab(float l, float c, float h, Illuminant_Label illuminant)
    : Color(l, c, h, illuminant) {}


Lab Lch_Ab::to_lab() const {
  auto [l, c, h] = m_values;

  const float a = c * std::cos(to_radians(h));
  const float b = c * std::sin(to_radians(h));

  return Lab(l, a, b);
}


void Lch_Ab::print() const {
  std::cout << "[LCHab]" << "\nL: " << m_values[0] << "\nc: " << m_values[1]
            << "\nh: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

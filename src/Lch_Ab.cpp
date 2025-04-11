#include "../include/Color.h"
#include "../include/util.h"

#include <array>
#include <cmath>
#include <iostream>

namespace Color_Space {


Lch_Ab::Lch_Ab(float l, float c, float h, Illuminant_Label illuminant)
    : Color(l, c, h, illuminant) {}


Lab Lch_Ab::to_lab() const {
  auto [l, c, h_deg] = m_values;
  const float h_rad = to_radians(h_deg);

  const float a = c * std::cos(h_rad);
  const float b = c * std::sin(h_rad);

  return Lab(l, a, b, m_illuminant);
}


void Lch_Ab::print() const {
  std::cout << "[LCHab]" << "\nL: " << m_values[0] << "\nc: " << m_values[1]
            << "\nh: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

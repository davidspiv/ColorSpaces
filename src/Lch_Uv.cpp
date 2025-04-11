#include "../include/Color.h"
#include "../include/util.h"

#include <cmath>

namespace Color_Space {


Lch_Uv::Lch_Uv(float l, float c, float h, Illuminant_Label illuminant)
    : Color(l, c, h, illuminant) {}


Luv Lch_Uv::to_luv() const {
  auto [l, c, h] = m_values;

  const float a = c * std::cos(to_radians(h));
  const float b = c * std::sin(to_radians(h));

  return Luv(l, a, b);
}


void Lch_Uv::print() const {
  std::cout << "[LCHuv]" << "\nL: " << m_values[0] << "\nc: " << m_values[1]
            << "\nh: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

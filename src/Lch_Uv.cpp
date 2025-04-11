#include "../include/Color.h"
#include "../include/util.h"

#include <cmath>

namespace Color_Space {


Lch_Uv::Lch_Uv(float l, float c, float h, Illuminant_Label illuminant)
    : Color(l, c, h, illuminant) {}


Luv Lch_Uv::to_luv() const {
  auto [l, c, h_deg] = m_values;
  const float h_rad = to_radians(h_deg);

  const float u = c * std::cos(h_rad);
  const float v = c * std::sin(h_rad);

  return Luv(l, u, v, m_illuminant);
}


void Lch_Uv::print() const {
  std::cout << "[LCHuv]" << "\nL: " << m_values[0] << "\nc: " << m_values[1]
            << "\nh: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

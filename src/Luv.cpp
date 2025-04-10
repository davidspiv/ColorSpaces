#include "../include/Color.h"
#include "../include/util.h"

#include <array>
#include <iostream>

namespace Color_Space {


Luv::Luv(float l, float u, float v, Illuminant_Label illuminant)
    : Color(l, u, v, illuminant) {}


Lch_Uv Luv::to_lch_uv() const {
  const auto [l, u, v] = to_polar_color_space(m_values);

  return Lch_Uv(l, u, v, m_illuminant);
};


void Luv::print() const {
  std::cout << "[Luv]" << "\nL: " << m_values[0] << "\nu: " << m_values[1]
            << "\nv: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

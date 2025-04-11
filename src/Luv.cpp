#include "../include/Color.h"
#include "../include/util.h"

#include <array>
#include <cmath>
#include <iostream>

namespace Color_Space {


Luv::Luv(float l, float u, float v, Illuminant_Label illuminant)
    : Color(l, u, v, illuminant) {}


Lch_Uv Luv::to_lch_uv() const {
  const auto [l, u, v] = to_polar_color_space(m_values);

  return Lch_Uv(l, u, v, m_illuminant);
};


Xyz Luv::to_xyz() const {
  const auto [l, u, v] = m_values;
  const auto [w_X, w_Y, w_Z] = illuminants.at(m_illuminant).get_values();

  if (l == 0.0f)
    return Xyz(0.0f, 0.0f, 0.0f);

  const float chromaticity_denom = w_X + 15 * w_Y + 3 * w_Z;
  const float u0 = 4 * w_X / chromaticity_denom;
  const float v0 = 9 * w_Y / chromaticity_denom;

  const float Y =
      (l > kappa * epsilon) ? std::pow((l + 16.0f) / 116.0f, 3.0f) : l / kappa;

  const float ref_u_component = u + 13.0f * l * u0;
  const float ref_v_component = v + 13.0f * l * v0;

  if (ref_u_component == 0.0f || ref_v_component == 0.0f)
    return Xyz(0.0f, Y, 0.0f);

  constexpr float one_third = 1.0f / 3.0f;

  const float a = one_third * (52.0f * l / ref_u_component - 1.0f);
  const float b = -5.0f * Y;
  const float c = -one_third;
  const float d = Y * (39.0f * l / ref_v_component - 5.0f);

  const float X = (d - b) / (a - c);
  const float Z = X * a + b;

  return Xyz(X, Y, Z, m_illuminant);
}

void Luv::print() const {
  std::cout << "[Luv]" << "\nL: " << m_values[0] << "\nu: " << m_values[1]
            << "\nv: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

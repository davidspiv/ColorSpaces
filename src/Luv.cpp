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

  const float u0 = 4 * w_X / (w_X + 15 * w_Y + 3 * w_Z);
  const float v0 = 9 * w_Y / (w_X + 15 * w_Y + 3 * w_Z);

  const float y =
      l > (kappa * epsilon) ? std::pow((l + 16.0f) / 116.0f, 3) : l / kappa;

  const float denom_u = (u + 13.0f * l * u0);
  const float denom_v = (v + 13.0f * l * v0);

  if (denom_u == 0.0f || denom_v == 0.0f)
    return Xyz(0.0f, y, 0.0f);

  const float a = (1.0f / 3.0f) * (52.0f * l / denom_u - 1.0f);
  const float b = -5.0f * y;
  const float c = -1.0f / 3.0f;
  const float d = y * (39.0f * l / denom_v - 5.0f);

  const float x = (d - b) / (a - c);
  const float z = x * a + b;

  return Xyz(x, y, z, m_illuminant);
}


void Luv::print() const {
  std::cout << "[Luv]" << "\nL: " << m_values[0] << "\nu: " << m_values[1]
            << "\nv: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

#include "../include/Color.h"
#include "../include/Profile.h"
#include "../include/util.h"

#include <cmath>
#include <iostream>

namespace Color_Space {


Lab::Lab(float l, float a, float b, Illuminant_Label illuminant)
    : Color(l, a, b, illuminant) {}


Lch_Ab Lab::to_lch_ab() const {
  const auto [l, c, h] = to_polar_color_space(m_values);

  return Lch_Ab(l, c, h);
};


Xyz Lab::to_xyz() const {
  const float fX = (m_values[0] + 16.0f) / 116.0f;
  const float fY = fX + (m_values[1] / 500.0f);
  const float fZ = fX - (m_values[2] / 200.0f);

  const float rX = (std::pow(fY, 3.0f) > epsilon)
                       ? std::pow(fY, 3)
                       : (116.0f * fY - 16.0f) / kappa;
  const float rY =
      (m_values[0] > (kappa * epsilon)) ? std::pow(fX, 3) : m_values[0] / kappa;
  const float rZ = (std::pow(fZ, 3.0f) > epsilon)
                       ? std::pow(fZ, 3)
                       : (116.0f * fZ - 16.0f) / kappa;

  auto [ref_x, ref_y, ref_z] = illuminants.at(m_illuminant).get_values();

  const float x = rX * ref_x;
  const float y = rY * ref_y;
  const float z = rZ * ref_z;

  return Xyz(x, y, z, m_illuminant);
}


void Lab::print() const {
  std::cout << "[Lab]" << "\nL: " << m_values[0] << "\na: " << m_values[1]
            << "\nb: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

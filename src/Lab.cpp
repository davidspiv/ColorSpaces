#include "../include/Color.h"
#include "../include/util.h"

#include <cmath>
#include <iostream>

using namespace Color_Space;


Lab::Lab(float l, float a, float b) { m_values = {l, a, b}; }


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

  auto [wX, wY, wZ] = illuminants.at("d65").get_values();

  const float x = rX * wX;
  const float y = rY * wY;
  const float z = rZ * wZ;

  return Xyz(x, y, z);
}


void Lab::print() const {
  std::cout << "L: " << m_values[0] << "\na: " << m_values[1]
            << "\nb: " << m_values[2] << "\n\n";
}

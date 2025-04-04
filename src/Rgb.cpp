#include "../include/colorDefinitions.h"
#include "../include/util.h"

#include <algorithm>
#include <array>
#include <iostream>

namespace Color_Space {


Rgb::Rgb(float r, float g, float b) : m_values({r, g, b}) {
  auto validate = [](float c) {
    if (std::min<float>(1.0, std::max<float>(0.0, c)) != c) {
      throw std::domain_error("Channel initalized outside of range [0, 1].");
    }
  };

  validate(r);
  validate(g);
  validate(b);
};


float Rgb::apply_gamma(const float c) {
  float corrected =
      (c <= 0.0031308) ? (c * 12.92) : 1.055 * pow(c, 1.0 / 2.4) - 0.055;
  return std::clamp(corrected * 255.0, 0.0, 255.0);
};


Srgb Rgb::to_srgb() const {

  const float r = this->apply_gamma(m_values[0]);
  const float g = this->apply_gamma(m_values[1]);
  const float b = this->apply_gamma(m_values[2]);

  return Srgb(r, g, b);
};


Xyz Rgb::to_xyz() const {
  auto [x, y, z] = multiply_matrix(this->rgbTo_xyzMatrix, m_values);

  return Xyz(x, y, z);
}


void Rgb::print() const {
  std::cout << "R: " << m_values[0] << "\nG: " << m_values[1]
            << "\nB: " << m_values[2] << std::endl;
}


} // namespace Color_Space

#include "../include/colorDefinitions.h"
#include "../include/util.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

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

  std::vector<float> values_as_vector(m_values.begin(), m_values.end());

  Matrix resultMatrix = create_rgb_to_xyz_transformation_matrix().multiply(
      Matrix({values_as_vector}));

  return Xyz(resultMatrix(0, 0), resultMatrix(0, 1), resultMatrix(0, 2));
}


void Rgb::print() const {
  std::cout << "R: " << m_values[0] << "\nG: " << m_values[1]
            << "\nB: " << m_values[2] << std::endl;
}


} // namespace Color_Space

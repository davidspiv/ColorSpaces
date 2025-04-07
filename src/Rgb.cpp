#include "../include/Color.h"
#include "../include/Matrix.h"
#include "../include/util_internal.h"

#include <algorithm>
#include <array>
#include <iostream>

using namespace Color_Space;


Rgb::Rgb(float r, float g, float b) {
  auto validate = [](float c) {
    if (std::min<float>(1.0, std::max<float>(0.0, c)) != c) {
      throw std::domain_error("Channel initalized outside of range [0, 1].");
    }
  };

  validate(r);
  validate(g);
  validate(b);

  m_values = {r, g, b};
};


float Rgb::apply_gamma(const float c) {
  float corrected =
      (c <= 0.0031308) ? (c * 12.92) : 1.055 * pow(c, 1.0 / 2.4) - 0.055;
  return std::clamp(corrected * 255.0, 0.0, 255.0);
};


S_Rgb Rgb::to_s_rgb() const {

  const float r = this->apply_gamma(m_values[0]);
  const float g = this->apply_gamma(m_values[1]);
  const float b = this->apply_gamma(m_values[2]);

  return S_Rgb(r, g, b);
};


Xyz Rgb::to_xyz() const {
  Matrix M_matrix = create_rgb_to_xyz_transformation_matrix();

  Matrix xyz_as_matrix = M_matrix.multiply(this->to_column());

  const float x = std::clamp<float>(xyz_as_matrix(0, 0), 0.0, 1.0);
  const float y = std::clamp<float>(xyz_as_matrix(1, 0), 0.0, 1.0);
  const float z = std::clamp<float>(xyz_as_matrix(2, 0), 0.0, 1.0);

  return Xyz(x, y, z);
}


void Rgb::print() const {
  std::cout << "R: " << m_values[0] << "\nG: " << m_values[1]
            << "\nB: " << m_values[2] << std::endl;
}

#include "../include/Color.h"
#include "../include/Matrix.h"
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


S_Rgb Rgb::to_s_rgb() const {

  const float r = this->apply_gamma(m_values[0]);
  const float g = this->apply_gamma(m_values[1]);
  const float b = this->apply_gamma(m_values[2]);

  return S_Rgb(r, g, b);
};


Xyz Rgb::to_xyz() const {
  Matrix M_matrix = create_rgb_to_xyz_transformation_matrix();

  const std::array<std::array<float, 3>, 3> M_matrix_as_array = {
      {{M_matrix(0, 0), M_matrix(0, 1), M_matrix(0, 2)},
       {M_matrix(1, 0), M_matrix(1, 1), M_matrix(1, 2)},
       {M_matrix(2, 0), M_matrix(2, 1), M_matrix(2, 2)}}};

  auto [x, y, z] = multiply_matrix(M_matrix_as_array, m_values);

  return Xyz(x, y, z);
}


void Rgb::print() const {
  std::cout << "R: " << m_values[0] << "\nG: " << m_values[1]
            << "\nB: " << m_values[2] << std::endl;
}


} // namespace Color_Space

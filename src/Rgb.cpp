#include "../include/Matrix.h"
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

std::array<std::array<float, 3>, 3> create_rgb_to_xyz_transformation_matrix() {
  Matrix d65_matrix = Matrix({{0.95047}, {1.00000}, {1.08883}});

  // sRGB
  float x_r = 0.6400;
  float x_g = 0.3000;
  float x_b = 0.1500;
  float y_r = 0.3300;
  float y_g = 0.6000;
  float y_b = 0.0600;

  const float X_r = x_r / y_r;
  const float Y_r = 1;
  const float Z_r = (1 - x_r - y_r) / y_r;

  const float X_g = x_g / y_g;
  const float Y_g = 1;
  const float Z_g = (1 - x_g - y_g) / y_g;

  const float X_b = x_b / y_b;
  const float Y_b = 1;
  const float Z_b = (1 - x_b - y_b) / y_b;


  const std::vector<std::vector<float>> XYZ = {
      {X_r, X_g, X_b}, {Y_r, Y_g, Y_b}, {Z_r, Z_g, Z_b}};

  const Matrix XYZ_matrix(XYZ);
  const Matrix XYZ_matrix_inverted = XYZ_matrix.invert();
  const Matrix S_matrix = XYZ_matrix_inverted.multiply(d65_matrix);
  const Matrix M_matrix = XYZ_matrix.column_wise_scaling(S_matrix);

  const std::array<std::array<float, 3>, 3> M_matrix_as_array = {
      {{M_matrix(0, 0), M_matrix(0, 1), M_matrix(0, 2)},
       {M_matrix(1, 0), M_matrix(1, 1), M_matrix(1, 2)},
       {M_matrix(2, 0), M_matrix(2, 1), M_matrix(2, 2)}}};

  return M_matrix_as_array;
}


Xyz Rgb::to_xyz() const {
  auto [x, y, z] =
      multiply_matrix(create_rgb_to_xyz_transformation_matrix(), m_values);

  return Xyz(x, y, z);
}


void Rgb::print() const {
  std::cout << "R: " << m_values[0] << "\nG: " << m_values[1]
            << "\nB: " << m_values[2] << std::endl;
}


} // namespace Color_Space

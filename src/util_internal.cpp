#include "../include/util_internal.h"
#include "../include/Matrix.h"

#include <array>
#include <cmath>
#include <iostream>

using namespace Color_Space;

double to_degrees(const double radians) { return radians * (180.0 / M_PI); }


double to_radians(const double degrees) { return degrees * (M_PI / 180.0); }


std::array<float, 3>
to_polar_color_space(const std::array<float, 3> &cartesianColor_Space) {
  const auto [l, a, b] = cartesianColor_Space; // LchAb equivalents: a=u and b=v
  const float c = std::sqrt(a * a + b * b);
  const float h_component = to_degrees(std::atan2(b, a));
  const float h = (h_component >= 0) ? h_component : h_component + 360.0;

  return {l, c, h};
}


std::array<float, 3>
multiply_matrix(const std::array<std::array<float, 3>, 3> &matrix,
                const std::array<float, 3> &vector) {

  std::array<float, 3> result = {0.0, 0.0, 0.0};

  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      result[i] += matrix[i][j] * vector[j];
    }
  }

  return result;
}


Matrix create_rgb_to_xyz_transformation_matrix() {
  Matrix d65_matrix = color_to_column(reference_white_d60);

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

  return XYZ_matrix.column_wise_scaling(S_matrix);
}


Matrix create_xyz_to_rgb_transformation_matrix() {
  return create_rgb_to_xyz_transformation_matrix().invert();
}

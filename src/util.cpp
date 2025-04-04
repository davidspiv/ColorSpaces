#include "../include/util.h"
#include "../include/Matrix.h"

#include <array>
#include <cmath>
#include <iostream>

namespace Color_Space {


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


Matrix create_rgb_to_xyz_transformation_matrix() {
  // Adobe RGB (1998)
  //   float x_r = 0.6400;
  //   float x_g = 0.2100;
  //   float x_b = 0.1500;
  //   float y_r = 0.3300;
  //   float y_g = 0.7100;
  //   float y_b = 0.0600;

  const static Matrix d65_matrix = Matrix({{0.95047}, {1.00000}, {1.08883}});

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

  Matrix XYZ_matrix({{X_r, X_g, X_b}, {Y_r, Y_g, Y_b}, {Z_r, Z_g, Z_b}});

  Matrix S_matrix = XYZ_matrix.invert().multiply(d65_matrix);
  Matrix M_matrix(3, 3);

  return XYZ_matrix.column_wise_scaling(S_matrix);
}

Matrix create_xyz_to_rgb_transformation_matrix() {
  return create_rgb_to_xyz_transformation_matrix().invert();
}


} // namespace Color_Space

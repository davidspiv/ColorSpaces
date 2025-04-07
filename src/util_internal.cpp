#include "../include/util_internal.h"
#include "../include/Color.h"
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


Matrix create_to_xyz_transformation_matrix(const Xyy &primary_r,
                                           const Xyy &primary_g,
                                           const Xyy &primary_b) {
  Matrix d65_matrix = color_to_column(reference_white_d60);

  auto [r_x, r_y, r_z] = primary_r.get_values();
  auto [g_x, g_y, g_z] = primary_g.get_values();
  auto [b_x, b_y, b_z] = primary_b.get_values();

  const float r_X = r_x / r_y;
  const float r_Y = 1;
  const float r_Z = (1 - r_x - r_y) / r_y;

  const float g_X = g_x / g_y;
  const float g_Y = 1;
  const float g_Z = (1 - g_x - g_y) / g_y;

  const float b_X = b_x / b_y;
  const float b_Y = 1;
  const float b_Z = (1 - b_x - b_y) / b_y;


  const std::vector<std::vector<float>> XYZ = {
      {r_X, g_X, b_X}, {r_Y, g_Y, b_Y}, {r_Z, g_Z, b_Z}};

  const Matrix XYZ_matrix(XYZ);
  const Matrix XYZ_matrix_inverted = XYZ_matrix.invert();
  const Matrix S_matrix = XYZ_matrix_inverted.multiply(d65_matrix);

  return XYZ_matrix.column_wise_scaling(S_matrix);
}

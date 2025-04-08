#include "../include/util.h"
#include "../include/Color.h"
#include "../include/Matrix.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <string>

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


// tone-response curve
float apply_gamma(const float c) {
  float corrected =
      (c <= 0.0031308) ? (c * 12.92) : 1.055 * pow(c, 1.0 / 2.4) - 0.055;
  return std::clamp(corrected * 255.0, 0.0, 255.0);
};


Matrix create_to_xyz_transformation_matrix(const Xyz &reference_illuminant,
                                           const Xyz &r_xyz, const Xyz &g_xyz,
                                           const Xyz &b_xyz) {
  Matrix illuminant_matrix = color_to_column(reference_illuminant);

  auto [r_x, r_y, r_z] = r_xyz.get_values();
  auto [g_x, g_y, g_z] = g_xyz.get_values();
  auto [b_x, b_y, b_z] = b_xyz.get_values();

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
  const Matrix S_matrix = XYZ_matrix_inverted.multiply(illuminant_matrix);

  return XYZ_matrix.column_wise_scaling(S_matrix);
}


Matrix compute_chromatic_adaptation_matrix(const Xyz &src_illuminant,
                                           const Xyz &dest_illuminant) {
  const Matrix bradford_matrix({{0.8951000, 0.2664000, -0.1614000},
                                {-0.7502000, 1.7135000, 0.0367000},
                                {0.0389000, -0.0685000, 1.0296000}});

  // Transform from XYZ into a cone response domain
  Matrix src_cone_response =
      bradford_matrix.multiply(src_illuminant.to_column());
  Matrix dest_cone_response =
      bradford_matrix.multiply(dest_illuminant.to_column());

  // Create diagonal scaling matrix
  Matrix S_matrix(3, 3);
  for (int i = 0; i < 3; ++i) {
    const float scale = dest_cone_response(i, 0) / src_cone_response(i, 0);
    S_matrix(i, i) = scale;
  }

  Matrix M_matrix =
      bradford_matrix.invert().multiply(S_matrix).multiply(bradford_matrix);

  return M_matrix;
}


Xyz Xyz::adapt_to_white_point(const Xyz &src_illuminant,
                              const Xyz &dest_illuminant) const {
  //   if (src_illuminant == dest_illuminant) {
  //     return *this;
  //   }

  const Matrix new_primary_matrix =
      compute_chromatic_adaptation_matrix(src_illuminant, dest_illuminant)
          .multiply(this->to_column());

  return Xyz(new_primary_matrix(0, 0), new_primary_matrix(1, 0),
             new_primary_matrix(2, 0));
};

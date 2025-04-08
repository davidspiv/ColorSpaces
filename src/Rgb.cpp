#include "../include/Color.h"
#include "../include/Profile.h"
#include "../include/util.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace Color_Space;


Rgb::Rgb(float r, float g, float b) {
  auto validate = [](float c) {
    if (std::min(255.0f, std::max(0.0f, c)) != c) {
      throw std::domain_error("Channel initalized outside of range [0, 255].");
    }
  };

  validate(r);
  validate(g);
  validate(b);

  m_values = {r, g, b};
};


Xyz Rgb::to_xyz(const Rgb_Working_space working_space) const {
  const Profile profile =
      working_space == none ? profiles.at(0) : get_profile(working_space);

  auto [r, g, b] = m_values;

  // Step 1: Normalize input RGB [0–255] -> [0.0–1.0]
  const float r_lin = remove_gamma(r / 255.0f, profile.gamma);
  const float g_lin = remove_gamma(g / 255.0f, profile.gamma);
  const float b_lin = remove_gamma(b / 255.0f, profile.gamma);

  // Step 2: Convert to XYZ using matrix
  const Matrix M_matrix = create_to_xyz_transformation_matrix(profile);
  const Matrix rgb_lin({{r_lin}, {g_lin}, {b_lin}});
  const Matrix xyz_matrix = M_matrix.multiply(rgb_lin);

  return Xyz(xyz_matrix(0, 0), xyz_matrix(1, 0), xyz_matrix(2, 0));
}


void Rgb::print() const {
  std::cout << "r: " << m_values[0] << "\ng: " << m_values[1]
            << "\nb: " << m_values[2] << std::endl;
}

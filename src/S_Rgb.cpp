#include "../include/Color.h"
#include "../include/util.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace Color_Space;


S_Rgb::S_Rgb(float r, float g, float b) {
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


float S_Rgb::remove_gamma(int c) {
  float normalized_channel = static_cast<double>(c) / 255.0;

  const float breakpoint = 0.04045f;

  return (normalized_channel <= breakpoint)
             ? (normalized_channel / 12.92f)
             : std::pow((normalized_channel + 0.055f) / 1.055f, 2.4f);
};


Xyz S_Rgb::to_xyz(const std::string &reference_white_label,
                  const std::string &primaries_label) const {
  auto [primary_r, primary_g, primary_b] = primaries_label.size()
                                               ? primaries.at(primaries_label)
                                               : primaries.at("srgb");

  const Xyz reference_white = primaries_label.size()
                                  ? illuminants.at(reference_white_label)
                                  : illuminants.at("d65");

  const Matrix M_matrix = create_to_xyz_transformation_matrix(
      reference_white, primary_r, primary_g, primary_b);

  auto [r, g, b] = m_values;

  const Lin_Rgb lin_rgb(remove_gamma(r), remove_gamma(g), remove_gamma(b));

  const Matrix xyz_as_matrix = M_matrix.multiply(lin_rgb.to_column());

  // Absolute colorimetric - probably don't need to clamp here?
  const float x = xyz_as_matrix(0, 0);
  const float y = xyz_as_matrix(1, 0);
  const float z = xyz_as_matrix(2, 0);

  return Xyz(x, y, z);
}


void S_Rgb::print() const {
  std::cout << "r: " << m_values[0] << "\ng: " << m_values[1]
            << "\nb: " << m_values[2] << std::endl;
}

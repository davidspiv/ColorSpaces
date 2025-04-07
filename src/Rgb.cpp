#include "../include/Color.h"
#include "../include/Matrix.h"
#include "../include/util.h"

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

// tone-response curve
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
  Xyz r(0.6400, 0.3300, 0.212656);
  Xyz g(0.3000, 0.6000, 0.715158);
  Xyz b(0.1500, 0.0600, 0.072186);

  Matrix M_matrix = compute_rgb_to_xyz_matrix(r, g, b, illuminants.at("d65"));

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

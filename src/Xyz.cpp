#include "../include/Color.h"
#include "../include/Profile.h"
#include "../include/util.h"

#include <algorithm>
#include <array>
#include <cmath>

using namespace Color_Space;


Xyz::Xyz(float x, float y, float z, Illuminant_Label ref_white) {
  m_values = {x, y, z};
  m_ref_white = ref_white;
}


Rgb Xyz::to_rgb(const Rgb_Working_Space working_space) const {

  const Profile profile = (working_space == UNSPECIFIED)
                              ? profiles.at(0)
                              : get_profile(working_space);

  const Matrix color_as_column =
      (profile.illuminant == illuminants.at(m_ref_white))
          ? to_column()
          : adapt_to_white_point(D65).to_column();

  const Matrix M_matrix = create_to_xyz_transformation_matrix(profile).invert();

  Matrix xyz_as_matrix = M_matrix.multiply(color_as_column);

  // Absolute colorimetric
  const float r_corr = apply_gamma(xyz_as_matrix(0, 0), profile.gamma);
  const float g_corr = apply_gamma(xyz_as_matrix(1, 0), profile.gamma);
  const float b_corr = apply_gamma(xyz_as_matrix(2, 0), profile.gamma);

  const float r_norm = std::clamp(r_corr, 0.0f, 1.0f) * 255.0f;
  const float g_norm = std::clamp(g_corr, 0.0f, 1.0f) * 255.0f;
  const float b_norm = std::clamp(b_corr, 0.0f, 1.0f) * 255.0f;

  return Rgb(r_norm, g_norm, b_norm, m_ref_white);
}


Lab Xyz::to_lab() const {
  auto [ref_x, ref_y, ref_z] = illuminants.at(m_ref_white).get_values();

  const float xR = m_values[0] / ref_x;
  const float yR = m_values[1] / ref_y;
  const float zR = m_values[2] / ref_z;

  const float fX = (xR > epsilon) ? std::cbrt(xR) : (kappa * xR + 16) / 116.0f;
  const float fY = (yR > epsilon) ? std::cbrt(yR) : (kappa * yR + 16) / 116.0f;
  const float fZ = (zR > epsilon) ? std::cbrt(zR) : (kappa * zR + 16) / 116.0f;

  const float l = 116.0f * fY - 16;
  const float a = 500.0f * (fX - fY);
  const float b = 200.0f * (fY - fZ);

  return Lab(l, a, b, m_ref_white);
}


Luv Xyz::to_luv() const {
  auto [ref_x, ref_y, ref_z] = illuminants.at(m_ref_white).get_values();
  auto [x, y, z] = m_values;

  const float yR = y / ref_y;

  const float denominator = x + 15.0 * y + 3 * z;
  if (denominator == 0.0) {
    return Luv(0.0, 0.0, 0.0);
  }

  const float uPrime = (4.0 * x) / denominator;
  const float vPrime = (9.0 * y) / denominator;

  const float refDenominator = ref_x + 15.0 * ref_y + 3.0 * ref_z;
  const float refUPrime = (4.0 * ref_x) / refDenominator;
  const float refVPrime = (9.0 * ref_y) / refDenominator;

  constexpr double accError = 1e-7;
  const float uDiff = uPrime - refUPrime;
  const float vDiff = vPrime - refVPrime;

  const float l =
      (yR > epsilon) ? (116.0 * std::cbrt(yR) - 16.0) : (kappa * yR);
  const float u = (std::abs(uDiff) > accError) ? 13.0 * l * uDiff : 0;
  const float v = (std::abs(vDiff) > accError) ? 13.0 * l * vDiff : 0;

  return Luv(l, u, v, m_ref_white);
}


Xyy Xyz::to_xyy() const {
  auto [X, Y, Z] = m_values;
  const float sum = X + Y + Z;

  if (sum == 0.0f) {
    const Xyy white_chromaticity = illuminants.at(m_ref_white).to_xyy();
    auto [x_white, y_white, _] = white_chromaticity.get_values();

    return Xyy(x_white, y_white, Y);
  }

  const float x_chromaticity = X / sum;
  const float y_chromaticity = Y / sum;

  return Xyy(x_chromaticity, y_chromaticity, Y, m_ref_white);
}


Xyz Xyz::adapt_to_white_point(const Illuminant_Label illuminant_label) const {
  if (m_ref_white == illuminant_label) {
    return *this;
  }

  const Xyz white_point = illuminants.at(illuminant_label);

  const Matrix new_primary_matrix =
      compute_chromatic_adaptation_matrix(illuminants.at(m_ref_white),
                                          white_point)
          .multiply(to_column());

  return Xyz(new_primary_matrix(0, 0), new_primary_matrix(1, 0),
             new_primary_matrix(2, 0), illuminant_label);
};


void Xyz::print() const {
  std::cout << "[XYZ]" << "\nX: " << m_values[0] << "\nY: " << m_values[1]
            << "\nZ: " << m_values[2] << "\n\n";
}

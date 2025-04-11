#include "../include/Color.h"
#include "../include/Profile.h"
#include "../include/util.h"

#include <algorithm>
#include <array>
#include <cmath>

namespace Color_Space {


Xyz::Xyz(float x, float y, float z, Illuminant_Label illuminant)
    : Color(x, y, z, illuminant) {}


Rgb Xyz::to_rgb(const Rgb_Profile_Label profile_label) const {

  const Profile profile = get_profile(profile_label);

  const Matrix color_as_column =
      (profile.illuminant_label == m_illuminant)
          ? to_column()
          : adapt_to_white_point(profile.illuminant_label).to_column();

  const Matrix M_matrix = create_to_xyz_transformation_matrix(profile).invert();

  Matrix xyz_as_matrix = M_matrix.multiply(color_as_column);

  // Absolute colorimetric
  const float r_corr = apply_gamma(xyz_as_matrix(0, 0), profile.gamma);
  const float g_corr = apply_gamma(xyz_as_matrix(1, 0), profile.gamma);
  const float b_corr = apply_gamma(xyz_as_matrix(2, 0), profile.gamma);

  const float r_norm = std::clamp(r_corr, 0.0f, 1.0f) * 255.0f;
  const float g_norm = std::clamp(g_corr, 0.0f, 1.0f) * 255.0f;
  const float b_norm = std::clamp(b_corr, 0.0f, 1.0f) * 255.0f;

  return Rgb(r_norm, g_norm, b_norm, m_illuminant);
}


Lab Xyz::to_lab() const {
  auto [w_X, w_Y, w_Z] = illuminants.at(m_illuminant).get_values();

  const float xR = m_values[0] / w_X;
  const float yR = m_values[1] / w_Y;
  const float zR = m_values[2] / w_Z;

  const float fX = (xR > epsilon) ? std::cbrt(xR) : (kappa * xR + 16) / 116.0f;
  const float fY = (yR > epsilon) ? std::cbrt(yR) : (kappa * yR + 16) / 116.0f;
  const float fZ = (zR > epsilon) ? std::cbrt(zR) : (kappa * zR + 16) / 116.0f;

  const float l = 116.0f * fY - 16;
  const float a = 500.0f * (fX - fY);
  const float b = 200.0f * (fY - fZ);

  return Lab(l, a, b, m_illuminant);
}


Luv Xyz::to_luv() const {
  const auto [w_X, w_Y, w_Z] = illuminants.at(m_illuminant).get_values();
  const auto [X, Y, Z] = m_values;

  const float Y_r = Y / w_Y;

  const float denom = X + 15.0f * Y + 3.0f * Z;
  if (denom == 0.0f)
    return Luv(0.0f, 0.0f, 0.0f);

  const float u_prime = (4.0f * X) / denom;
  const float v_prime = (9.0f * Y) / denom;

  const float ref_denom = w_X + 15.0f * w_Y + 3.0f * w_Z;
  const float u0 = (4.0f * w_X) / ref_denom;
  const float v0 = (9.0f * w_Y) / ref_denom;

  const float delta_u = u_prime - u0;
  const float delta_v = v_prime - v0;

  const float l =
      (Y_r > epsilon) ? (116.0f * std::cbrt(Y_r) - 16.0f) : (kappa * Y_r);
  const float u = 13.0f * l * delta_u;
  const float v = 13.0f * l * delta_v;

  //   constexpr float acc_error = 1e-7f;
  //   const float u = (std::abs(delta_u) > acc_error) ? 13.0f * l * delta_u :
  //   0.0f; const float v = (std::abs(delta_v) > acc_error) ? 13.0f * l *
  //   delta_v : 0.0f;

  return Luv(l, u, v, m_illuminant);
}


Xyy Xyz::to_xyy() const {
  const auto [X, Y, Z] = m_values;
  const float sum = X + Y + Z;

  if (sum == 0.0f) {
    const Xyy white_point = illuminants.at(m_illuminant).to_xyy();
    const auto [x_white, y_white, _] = white_point.get_values();
    return Xyy(x_white, y_white, Y);
  }

  const float x = X / sum;
  const float y = Y / sum;

  return Xyy(x, y, Y, m_illuminant);
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


Xyz Xyz::adapt_to_white_point(const Illuminant_Label illuminant_label) const {
  if (m_illuminant == illuminant_label) {
    return *this;
  }

  const Xyz white_point = illuminants.at(illuminant_label);

  const Matrix new_primary_matrix =
      compute_chromatic_adaptation_matrix(illuminants.at(m_illuminant),
                                          white_point)
          .multiply(to_column());

  return Xyz(new_primary_matrix(0, 0), new_primary_matrix(1, 0),
             new_primary_matrix(2, 0), illuminant_label);
};


void Xyz::print() const {
  std::cout << "[XYZ]" << "\nX: " << m_values[0] << "\nY: " << m_values[1]
            << "\nZ: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

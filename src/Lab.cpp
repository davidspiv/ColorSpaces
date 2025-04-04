#include "../include/colorDefinitions.h"
#include "../include/util.h"

#include <array>
#include <cmath>
#include <iostream>

namespace Color_Space {


Lab::Lab(float l, float a, float b) : m_values({l, a, b}) {};


Xyz Lab::to_xyz() const {
  const float fY = (m_values[0] + 16.0f) / 116.0f;
  const float fX = fY + (m_values[1] / 500.0f);
  const float fZ = fY - (m_values[2] / 200.0f);

  const float xR = (std::pow(fX, 3.0f) > epsilon)
                       ? std::pow(fX, 3)
                       : (116.0f * fX - 16.0f) / kappa;
  const float yR =
      (m_values[0] > (kappa * epsilon)) ? std::pow(fY, 3) : m_values[0] / kappa;
  const float zR = (std::pow(fZ, 3.0f) > epsilon)
                       ? std::pow(fZ, 3)
                       : (116.0f * fZ - 16.0f) / kappa;

  const float x = xR * reference_white_d60[0];
  const float y = yR * reference_white_d60[1];
  const float z = zR * reference_white_d60[2];

  return Xyz(x, y, z);
}


Lch_Ab Lab::to_lch_ab() const {
  const auto [l, c, h] = to_polar_color_space(m_values);

  return Lch_Ab(l, c, h);
};


float Lab::diff_cie_76(const Lab &other) const {
  return diff_euclidean(*this, other);
}


float Lab::diff_cie_94(const Lab &other, Mode mode) const {
  auto [L1, a1, b1] = m_values;
  auto [L2, a2, b2] = other.get_values();

  const float C1 = euclidean_norm(a1, b1);
  const float C2 = euclidean_norm(a2, b2);

  const float deltaL = L1 - L2;
  const float deltaC = C1 - C2;

  const float deltaA = a1 - a2;
  const float deltaB = b1 - b2;

  // In the calculation of ΔH, the value inside the radical is, in theory,
  // always greater than or equal to zero. However in an actual implementation,
  // it may become a very slightly negative value, due to limited arithmetic
  // precision.
  const float deltaH_sq =
      std::max(0.0f, deltaA * deltaA + deltaB * deltaB - deltaC * deltaC);
  const float deltaH = std::sqrt(deltaH_sq);

  // Parametric factors
  const float kL = (mode == GRAPHICS) ? 1.0f : 2.0f;
  const float k1 = (mode == GRAPHICS) ? 0.045f : 0.048f;
  const float k2 = (mode == GRAPHICS) ? 0.015f : 0.014f;

  const float sL = 1.0f;
  const float sC = 1.0f + k1 * C1;
  const float sH = 1.0f + k2 * C1;

  const float xMag = deltaL / (kL * sL);
  const float yMag = deltaC / sC;
  const float zMag = deltaH / sH;

  return std::sqrt(xMag * xMag + yMag * yMag + zMag * zMag);
}


float Lab::diff_cie_2000(const Lab &other) const {
  auto [L1, a1, b1] = m_values;
  auto [L2, a2, b2] = other.get_values();

  const float C1 = euclidean_norm(a1, b1);
  const float C2 = euclidean_norm(a2, b2);
  const float C_mean = (C1 + C2) / 2.0f;

  const float G_component_a = std::pow(25.0f, 7);
  const float G_component_b = std::pow(C_mean, 7);
  const float G =
      0.5f *
      (1.0f - std::sqrt(G_component_b / (G_component_b + G_component_a)));

  const float a1_prime = a1 * (1 + G);
  const float a2_prime = a2 * (1 + G);

  const float C1_prime = euclidean_norm(a1_prime, b1);
  const float C2_prime = euclidean_norm(a2_prime, b2);
  const float C_prime_mean = (C1_prime + C2_prime) / 2.0f;

  const float h1_prime = to_degrees(std::atan2(b1, a1_prime));
  const float h2_prime = to_degrees(std::atan2(b2, a2_prime));

  const float h1_corrected = (h1_prime >= 0.0f) ? h1_prime : h1_prime + 360.0f;
  const float h2_corrected = (h2_prime >= 0.0f) ? h2_prime : h2_prime + 360.0f;

  float delta_h_prime;
  if (std::abs(h1_corrected - h2_corrected) <= 180.0f) {
    delta_h_prime = h2_corrected - h1_corrected;
  } else if (h2_corrected <= h1_corrected) {
    delta_h_prime = h2_corrected - h1_corrected + 360.0f;
  } else {
    delta_h_prime = h2_corrected - h1_corrected - 360.0f;
  }

  const float delta_H_prime = 2.0f * std::sqrt(C1_prime * C2_prime) *
                              sin(to_radians(delta_h_prime / 2.0f));

  const float H_prime_mean = (std::abs(h1_corrected - h2_corrected) > 180.0f)
                                 ? (h1_corrected + h2_corrected + 360.0f) / 2.0f
                                 : (h1_corrected + h2_corrected) / 2.0f;

  const float T = 1.0f - 0.17f * cos(to_radians(H_prime_mean - 30.0f)) +
                  0.24f * cos(to_radians(2.0f * H_prime_mean)) +
                  0.32f * cos(to_radians(3.0f * H_prime_mean + 6.0f)) -
                  0.20f * cos(to_radians(4.0f * H_prime_mean - 63.0f));

  const float delta_L_prime = L2 - L1;
  const float delta_C_prime = C2_prime - C1_prime;

  const float L_prime_mean = (L1 + L2) / 2.0f;

  const float S_L =
      1.0f + (0.015f * std::pow(L_prime_mean - 50.0f, 2)) /
                 std::sqrt(20.0f + std::pow(L_prime_mean - 50.0f, 2));
  const float S_C = 1.0f + 0.045f * C_prime_mean;
  const float S_H = 1.0f + 0.015f * C_prime_mean * T;

  const float delta_theta =
      30.0f * std::exp(-1.0f * std::pow((H_prime_mean - 275.0f) / 25.0f, 2));

  const float R_C =
      2.0f * std::sqrt(std::pow(C_prime_mean, 7) /
                       (std::pow(C_prime_mean, 7) + G_component_a));

  const float R_T = -R_C * sin(to_radians(2.0f * delta_theta));

  const float k_L = 1.0f;
  const float k_C = 1.0f;
  const float k_H = 1.0f;

  const float delta_E = std::sqrt(std::pow(delta_L_prime / (k_L * S_L), 2) +
                                  std::pow(delta_C_prime / (k_C * S_C), 2) +
                                  std::pow(delta_H_prime / (k_H * S_H), 2) +
                                  R_T * (delta_C_prime / (k_C * S_C)) *
                                      (delta_H_prime / (k_H * S_H)));

  return delta_E;
}


void Lab::print() const {
  std::cout << "L: " << m_values[0] << "\na: " << m_values[1]
            << "\nb: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

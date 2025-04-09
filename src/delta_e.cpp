#include "../include/Color.h"
#include "../include/util.h"

#include <array>
#include <cmath>

namespace Color_Space {


float Lab::diff_cie_76(const Lab &other) const {
  return diff_euclidean(*this, other);
}


float Lab::diff_cie_94(const Lab &other, bool mode_graphics) const {
  enum Mode {
    GRAPHICS, ///< For standard graphics/visual design CIE94 formula
    TEXTILES  ///< For textile-specific color comparisons
  };

  Mode mode = mode_graphics ? GRAPHICS : TEXTILES;

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

  // parametric weighting factors set to unity
  const float k_L = 1.0f;
  const float k_C = 1.0f;
  const float k_H = 1.0f;

  // Sharma 2005, eqn. 2
  const float C1 = euclidean_norm(a1, b1);
  const float C2 = euclidean_norm(a2, b2);

  // Sharma 2005, eqn. 3
  const float C_mean = (C1 + C2) / 2.0f;

  // Sharma 2005, eqn. 4
  const float G_component_a = std::pow(25.0f, 7);
  const float G_component_b = std::pow(C_mean, 7);
  const float G =
      0.5f *
      (1.0f - std::sqrt(G_component_b / (G_component_b + G_component_a)));

  // Sharma 2005, eqn. 5
  const float a1_prime = a1 * (1 + G);
  const float a2_prime = a2 * (1 + G);

  // Sharma 2005, eqn. 6
  const float C1_prime = euclidean_norm(a1_prime, b1);
  const float C2_prime = euclidean_norm(a2_prime, b2);

  // Sharma 2005, eqn. 7
  const float h1_prime = to_degrees(std::atan2(b1, a1_prime));
  const float h2_prime = to_degrees(std::atan2(b2, a2_prime));

  // Sharma 2005, eqn. 8
  const float delta_L_prime = L2 - L1;

  // Sharma 2005, eqn. 9
  const float delta_C_prime = C2_prime - C1_prime;

  // Sharma 2005, eqn. 10 (modified by LLM)
  const float h1_corrected = (h1_prime >= 0.0f) ? h1_prime : h1_prime + 360.0f;
  const float h2_corrected = (h2_prime >= 0.0f) ? h2_prime : h2_prime + 360.0f;
  float delta_h_prime =
      std::fmod(h2_corrected - h1_corrected + 540.0f, 360.0f) - 180.0f;

  // Sharma 2005, eqn. 11
  const float delta_H_prime = 2.0f * std::sqrt(C1_prime * C2_prime) *
                              std::sin(to_radians(delta_h_prime / 2.0f));

  // Sharma 2005, eqn. 12
  const float L_prime_mean = (L1 + L2) / 2.0f;

  // Sharma 2005, eqn. 13
  const float C_prime_mean = (C1_prime + C2_prime) / 2.0f;

  // Sharma 2005, eqn. 14
  const float H_prime_mean = (std::abs(h1_corrected - h2_corrected) > 180.0f)
                                 ? (h1_corrected + h2_corrected + 360.0f) / 2.0f
                                 : (h1_corrected + h2_corrected) / 2.0f;

  // Sharma 2005, eqn. 15
  const float T = 1.0f - 0.17f * cos(to_radians(H_prime_mean - 30.0f)) +
                  0.24f * std::cos(to_radians(2.0f * H_prime_mean)) +
                  0.32f * std::cos(to_radians(3.0f * H_prime_mean + 6.0f)) -
                  0.20f * std::cos(to_radians(4.0f * H_prime_mean - 63.0f));

  // Sharma 2005, eqn. 16
  const float delta_theta =
      30.0f * std::exp(-1.0f * std::pow((H_prime_mean - 275.0f) / 25.0f, 2));

  // Sharma 2005, eqn. 17
  const float R_C_component = std::pow(C_prime_mean, 7);
  const float R_C =
      2.0f * std::sqrt(R_C_component / (R_C_component + G_component_a));

  // Sharma 2005, eqn. 18
  const float S_L_component = L_prime_mean - 50.0f;
  const float S_L =
      1.0f + (0.015f * S_L_component * S_L_component) /
                 std::sqrt(20.0f + std::pow(L_prime_mean - 50.0f, 2));

  // Sharma 2005, eqn. 19
  const float S_C = 1.0f + 0.045f * C_prime_mean;

  // Sharma 2005, eqn. 20
  const float S_H = 1.0f + 0.015f * C_prime_mean * T;

  // Sharma 2005, eqn. 21
  const float R_T = -R_C * std::sin(to_radians(2.0f * delta_theta));

  // Sharma 2005, eqn. 22
  const float L_term = delta_L_prime / (k_L * S_L);
  const float C_term = delta_C_prime / (k_C * S_C);
  const float H_term = delta_H_prime / (k_H * S_H);
  const float delta_E = std::sqrt(L_term * L_term + C_term * C_term +
                                  H_term * H_term + R_T * C_term * H_term);

  return delta_E;
}


} // namespace Color_Space

#include "../include/Color.h"
#include "../include/util.h"

#include <algorithm>
#include <array>
#include <cmath>

using namespace Color_Space;


Xyz::Xyz(float x, float y, float z) { m_values = {x, y, z}; }


Rgb Xyz::to_rgb() const { // add rendering intent arg
  Xyz primary_r(0.6400, 0.3300, 0.212656);
  Xyz primary_g(0.3000, 0.6000, 0.715158);
  Xyz primary_b(0.1500, 0.0600, 0.072186);

  Matrix M_matrix = compute_rgb_to_xyz_matrix(primary_r, primary_g, primary_b,
                                              illuminants.at("d65"))
                        .invert();

  Matrix rbg_as_matrix = M_matrix.multiply(this->to_column());

  //// Absolute colorimetric
  const float r = std::clamp<float>(rbg_as_matrix(0, 0), 0.0f, 1.0f);
  const float g = std::clamp<float>(rbg_as_matrix(1, 0), 0.0f, 1.0f);
  const float b = std::clamp<float>(rbg_as_matrix(2, 0), 0.0f, 1.0f);

  return Rgb(r, g, b);
}


// Rgb Xyz::to_rgb(const Xyz &reference_white, const std::array<Xyz, 3>
// &primaries)
//     const { // add rendering intent arg

//   auto [primary_r, primary_g, primary_b] = primaries;

//   //   Xyz primary_r(0.6400, 0.3300, 0.212656);
//   //   Xyz primary_g(0.3000, 0.6000, 0.715158);
//   //   Xyz primary_b(0.1500, 0.0600, 0.072186);

//   Matrix M_matrix = compute_rgb_to_xyz_matrix(primary_r, primary_g,
//   primary_b,
//                                               reference_white)
//                         .invert();

//   Matrix rbg_as_matrix = M_matrix.multiply(this->to_column());

//   //// Absolute colorimetric
//   const float r = std::clamp<float>(rbg_as_matrix(0, 0), 0.0f, 1.0f);
//   const float g = std::clamp<float>(rbg_as_matrix(1, 0), 0.0f, 1.0f);
//   const float b = std::clamp<float>(rbg_as_matrix(2, 0), 0.0f, 1.0f);

//   return Rgb(r, g, b);
// }


Lab Xyz::to_lab() const {

  auto [x, y, z] = illuminants.at("d65").get_values();

  const float xR = m_values[0] / x;
  const float yR = m_values[1] / y;
  const float zR = m_values[2] / z;

  const float fX = (xR > epsilon) ? std::cbrt(xR) : (kappa * xR + 16) / 116.0f;
  const float fY = (yR > epsilon) ? std::cbrt(yR) : (kappa * yR + 16) / 116.0f;
  const float fZ = (zR > epsilon) ? std::cbrt(zR) : (kappa * zR + 16) / 116.0f;

  const float l = 116.0f * fY - 16;
  const float a = 500.0f * (fX - fY);
  const float b = 200.0f * (fY - fZ);

  return Lab(l, a, b);
}


Luv Xyz::to_luv() const {
  auto [xRef, yRef, zRef] = illuminants.at("d65").get_values();
  auto [x, y, z] = m_values;

  const float yR = y / illuminants.at("d65").get_values()[1];

  const float denominator = x + 15.0 * y + 3 * z;
  if (denominator == 0.0) {
    return Luv(0.0, 0.0, 0.0);
  }

  const float uPrime = (4.0 * x) / denominator;
  const float vPrime = (9.0 * y) / denominator;

  const float refDenominator = xRef + 15.0 * yRef + 3.0 * zRef;
  const float refUPrime = (4.0 * xRef) / refDenominator;
  const float refVPrime = (9.0 * yRef) / refDenominator;

  constexpr double accError = 1e-7;
  const float uDiff = uPrime - refUPrime;
  const float vDiff = vPrime - refVPrime;

  const float l =
      (yR > epsilon) ? (116.0 * std::cbrt(yR) - 16.0) : (kappa * yR);
  const float u = (uDiff > accError) ? 13.0 * l * uDiff : 0;
  const float v = (vDiff > accError) ? 13.0 * l * vDiff : 0;

  return Luv(l, u, v);
}


Xyy Xyz::to_xyy() const {
  auto [x, y, z] = m_values;
  const float sum = x + y + z;

  if (sum == 0.0) {

    const Xyy chromaticity_d65 = illuminants.at("d65").to_xyy();

    auto [w_x, w_y, w_Y] = chromaticity_d65.get_values();

    return Xyy(w_x, w_y, y);
  }

  const float xNew = x / sum;
  const float yNew = y / sum;

  return Xyy(xNew, yNew, y);
}


void Xyz::print() const {
  std::cout << "X: " << m_values[0] << "\nY: " << m_values[1]
            << "\nZ: " << m_values[2] << "\n\n";
}

#include "../include/colorDefinitions.h"
#include "../include/util.h"

#include <algorithm>
#include <cmath>
#include <vector>

namespace Color_Space {


Xyz::Xyz(float x, float y, float z) : m_values({x, y, z}) {};


Rgb Xyz::to_rgb() const {

  std::vector<float> values_as_vector(m_values.begin(), m_values.end());


  Matrix rgb_matrix = create_xyz_to_rgb_transformation_matrix().multiply(
      Matrix({values_as_vector}));

  const float r = std::clamp<float>(rgb_matrix(0, 0), 0.0f, 1.0f);
  const float g = std::clamp<float>(rgb_matrix(0, 1), 0.0f, 1.0f);
  const float b = std::clamp<float>(rgb_matrix(0, 2), 0.0f, 1.0f);

  return Rgb(r, g, b);
}


Lab Xyz::to_lab() const {

  const float xR = m_values[0] / reference_white_d60[0];
  const float yR = m_values[1] / reference_white_d60[1];
  const float zR = m_values[2] / reference_white_d60[2];

  const float fX = (xR > epsilon) ? std::cbrt(xR) : (kappa * xR + 16) / 116.0;
  const float fY = (yR > epsilon) ? std::cbrt(yR) : (kappa * yR + 16) / 116.0;
  const float fZ = (zR > epsilon) ? std::cbrt(zR) : (kappa * zR + 16) / 116.0;

  const float l = 116 * fY - 16;
  const float a = 500 * (fX - fY);
  const float b = 200 * (fY - fZ);

  return Lab(l, a, b);
}


Luv Xyz::to_luv() const {
  auto [xRef, yRef, zRef] = reference_white_d60;
  auto [x, y, z] = m_values;

  const float yR = y / reference_white_d60[1];

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
    return Xyy(chromaticity_d60[0], chromaticity_d60[1], y);
  }

  const float xNew = x / sum;
  const float yNew = y / sum;

  return Xyy(xNew, yNew, y);
}


void Xyz::print() const {
  std::cout << "X: " << m_values[0] << "\nY: " << m_values[1]
            << "\nZ: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

#include "../include/util.h"

#include <array>
#include <cmath>
#include <iostream>

namespace ColorSpace {


double toDegrees(const double radians) { return radians * (180.0 / M_PI); }


std::array<float, 3>
toPolarColorSpace(const std::array<float, 3> &cartesianColorSpace) {
  const auto [l, a, b] = cartesianColorSpace; // LchAb equivalents: a=u and b=v
  const float c = std::sqrt(a * a + b * b);
  const float hComponent = toDegrees(std::atan2(b, a));
  const float h = (hComponent >= 0) ? hComponent : hComponent + 360.0;

  return {l, c, h};
}


std::array<float, 3>
multiplyMatrix(const std::array<std::array<float, 3>, 3> &matrix,
               const std::array<float, 3> &vector) {

  std::array<float, 3> result = {0.0, 0.0, 0.0};

  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      result[i] += matrix[i][j] * vector[j];
    }
  }

  return result;
}


} // namespace ColorSpace

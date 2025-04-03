#include "util.h"
#include "color.h"

#include <array>
#include <cmath>
#include <iostream>

namespace ColorSpace {


std::array<float, 3>
toPolarColorSpace(std::array<float, 3> cartesianColorSpace) {
  const auto [l, a, b] = cartesianColorSpace; // LchAb equivalents: a=u and b=v
  const float c = std::sqrt(a * a + b * b);
  float h = toDegrees(std::atan2(b, a));

  if (h < 0) {
    h += 360.0f;
  }

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

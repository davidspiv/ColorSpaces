#include "util.h"
#include "color.h"

#include <array>
#include <iostream>
namespace ColorSpace {

int distSquared(const Srgb &colorA, const Srgb &colorB) {
  const int xD = colorB.r - colorA.r;
  const int yD = colorB.g - colorA.g;
  const int zD = colorB.b - colorA.b;
  return xD * xD + yD * yD + zD * zD;
}


float distSquared(const LinearRgb &colorA, const LinearRgb &colorB) {

  const float xD = colorB.r - colorA.r;
  const float yD = colorB.g - colorA.g;
  const float zD = colorB.b - colorA.b;
  return xD * xD + yD * yD + zD * zD;
}


float distSquared(const CieLab &colorA, const CieLab &colorB) {

  const float xD = colorB.l - colorA.l;
  const float yD = colorB.a - colorA.a;
  const float zD = colorB.b - colorA.b;
  return xD * xD + yD * yD + zD * zD;
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

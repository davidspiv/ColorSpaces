#include "util.h"
#include "color.h"

#include <array>
#include <iostream>
namespace ColorSpace {

int distSquared(const StdRgb &colorA, const StdRgb &colorB) {

  const int xD = colorB.r - colorA.r;
  const int yD = colorB.g - colorA.g;
  const int zD = colorB.b - colorA.b;
  return xD * xD + yD * yD + zD * zD;
}


double distSquared(const LinRgb &colorA, const LinRgb &colorB) {

  const double xD = colorB.r - colorA.r;
  const double yD = colorB.g - colorA.g;
  const double zD = colorB.b - colorA.b;
  return xD * xD + yD * yD + zD * zD;
}


double distSquared(const CieLab &colorA, const CieLab &colorB) {

  const double xD = colorB.lStar - colorA.lStar;
  const double yD = colorB.aStar - colorA.aStar;
  const double zD = colorB.bStar - colorA.bStar;
  return xD * xD + yD * yD + zD * zD;
}

std::array<double, 3>
multiplyMatrix(const std::array<std::array<double, 3>, 3> &matrix,
               const std::array<double, 3> &vector) {

  std::array<double, 3> result = {0.0, 0.0, 0.0};

  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      result[i] += matrix[i][j] * vector[j];
    }
  }

  return result;
}

} // namespace ColorSpace

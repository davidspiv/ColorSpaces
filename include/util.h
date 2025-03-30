// http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html

#ifndef UTIL_H
#define UTIL_H

#include "color.h"
#include <array>

template <typename CoordT>
double distSquared(const CoordT &coordA, const CoordT &coordB) {
  const double xD = coordB.x - coordA.x;
  const double yD = coordB.y - coordA.y;
  const double zD = coordB.z - coordA.z;
  return xD * xD + yD * yD + zD * zD;
}

size_t findClosestColorIdx(const StdRGB &targetColor,
                           const std::vector<StdRGB> &quantColors);


std::array<double, 3>
multiplyMatrix(const std::array<std::array<double, 3>, 3> &matrix,
               const std::array<double, 3> &vector);

#endif

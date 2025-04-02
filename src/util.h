#ifndef UTIL_H
#define UTIL_H

#include "color.h"
#include <array>

namespace ColorSpace {

int distSquared(const StdRgb &colorA, const StdRgb &colorB);
double distSquared(const LinRgb &colorA, const LinRgb &colorB);
double distSquared(const CieLab &colorA, const CieLab &colorB);

std::array<double, 3>
multiplyMatrix(const std::array<std::array<double, 3>, 3> &matrix,
               const std::array<double, 3> &vector);

} // namespace ColorSpace

#endif

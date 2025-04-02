#ifndef UTIL_H
#define UTIL_H

#include "color.h"
#include <array>

namespace ColorSpace {

const CieXyz referenceWhiteD60(0.950470, 1.0, 1.088830);
constexpr float epsilon = 216.0 / 24389.0;
constexpr float kappa = 24389.0 / 27.0;

int distSquared(const Srgb &colorA, const Srgb &colorB);
float distSquared(const LinearRgb &colorA, const LinearRgb &colorB);
float distSquared(const CieLab &colorA, const CieLab &colorB);

std::array<float, 3>
multiplyMatrix(const std::array<std::array<float, 3>, 3> &matrix,
               const std::array<float, 3> &vector);

} // namespace ColorSpace

#endif

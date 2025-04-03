#ifndef UTIL_H
#define UTIL_H

#include "color.h"
#include <array>
#include <cmath>

namespace ColorSpace {

const CieXyz referenceWhiteD60(0.950470, 1.0, 1.088830);
constexpr float epsilon = 216.0 / 24389.0;
constexpr float kappa = 24389.0 / 27.0;

float distEuclideanSquared(const LinearRgb &colorA, const LinearRgb &colorB);
float distEuclideanSquared(const CieXyz &colorA, const CieXyz &colorB);
float distEuclideanSquared(const CieLab &colorA, const CieLab &colorB);
// float distEuclideanSquared(const CieLch &colorA, const CieLch &colorB);

float distEuclidean(const LinearRgb &colorA, const LinearRgb &colorB);
float distEuclidean(const CieXyz &colorA, const CieXyz &colorB);
float distEuclidean(const CieLab &colorA, const CieLab &colorB);
// float distEuclidean(const CieLch &colorA, const CieLch &colorB);

// float distCIE76(const CieLab &colorA, const CieLab &colorB);
// float distCIE76(const CieLch &colorA, const CieLch &colorB);

// float distCIEDE2000(const CieLab &colorA, const CieLab &colorB);
// float distCIEDE2000(const CieLch &colorA, const CieLch &colorB);

// float distCIE94(const CieLab &colorA, const CieLab &colorB);
// float distCIE94(const CieLch &colorA, const CieLch &colorB);

std::array<float, 3>
multiplyMatrix(const std::array<std::array<float, 3>, 3> &matrix,
               const std::array<float, 3> &vector);

} // namespace ColorSpace

#endif

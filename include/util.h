#ifndef UTIL_H
#define UTIL_H

#include <array>
#include <cmath>
#include <stdexcept>

#include "colorDefinitions.h"

namespace ColorSpace {


constexpr std::array<float, 3> referenceWhiteD60 = {0.950470, 1.0, 1.088830};
constexpr std::array<float, 2> chromaticityD60 = {0.312727, 0.329023};
static constexpr float epsilon = 216.0f / 24389.0f;
static constexpr float kappa = 24389.0f / 27.0f;


double toDegrees(const double radians);


std::array<float, 3>
toPolarColorSpace(const std::array<float, 3> &cartesianColorSpace);


template <typename ColorT>
float distEuclideanSquared(const ColorT &a_Color, const ColorT &b_Color) {
  // type check: constraints, ifconstexpr (implemented), or SFINAE?
  if constexpr (!std::is_same_v<ColorT, Rgb> && !std::is_same_v<ColorT, Xyz> &&
                !std::is_same_v<ColorT, Lab>) {

    throw std::domain_error("Euclidean distance only valid for Rgb, "
                            "Xyz, and Lab color spaces");
  }

  constexpr size_t channelCount = 3;

  std::array<float, channelCount> a_Values = a_Color.getValues();
  std::array<float, channelCount> b_Values = b_Color.getValues();

  const float xD = a_Values[0] - b_Values[0];
  const float yD = a_Values[1] - b_Values[1];
  const float zD = a_Values[2] - b_Values[2];
  return xD * xD + yD * yD + zD * zD;
}


template <typename ColorT>
float distEuclidean(const ColorT &a_Color, const ColorT &b_Color) {
  return std::sqrt(distEuclideanSquared(a_Color, b_Color));
};


std::array<float, 3>
multiplyMatrix(const std::array<std::array<float, 3>, 3> &matrix,
               const std::array<float, 3> &vector);

} // namespace ColorSpace

#endif

// Distance Metrics (future implementations)
// float distCIE76(const Lab &other);
// float distCIEDE2000(const Lab &other);
// float distCIE94(const Lab &other);
// float distEuclideanSquared(const CieLch &other);
// float distEuclidean(const CieLch &other);
// float distCIE76(const CieLch &other);
// float distCIEDE2000(const CieLch &other);
// float distCIE94(const CieLch &other);

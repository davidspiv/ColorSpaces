#ifndef UTIL_H
#define UTIL_H

#include <array>
#include <cmath>
#include <stdexcept>

#include "colorDefinitions.h"

namespace ColorSpace {

constexpr std::array<float, 3> referenceWhiteD60 = {0.950470, 1.0, 1.088830};
constexpr std::array<float, 2> chromaticityD60 = {0.312727, 0.329023};
constexpr float epsilon = 216.0f / 24389.0f;
constexpr float kappa = 24389.0f / 27.0f;

double toDegrees(const double radians);

double toRadians(const double degrees);


std::array<float, 3>
toPolarColorSpace(const std::array<float, 3> &cartesianColorSpace);


template <typename T>
auto euclideanNorm(const T xMag, const T yMag, const T zMag) {
  return std::sqrt(xMag * xMag + yMag * yMag + zMag * zMag);
}


template <typename T>
auto euclideanNorm(const T xMag, const T yMag) {
  return std::sqrt(xMag * xMag + yMag * yMag);
}


template <typename ColorT>
float diffEuclidean(const ColorT &a_Color, const ColorT &b_Color) {
  // type check: constraints, ifconstexpr (implemented), or SFINAE?
  //   if constexpr (!std::is_same_v<ColorT, Rgb> && !std::is_same_v<ColorT,
  //   Xyz> &&
  //                 !std::is_same_v<ColorT, Lab>) {

  //     throw std::domain_error("Euclidean distance only valid for Rgb, "
  //                             "Xyz, and Lab color spaces");
  //   }

  std::array<float, 3> aChannels = a_Color.getValues();
  std::array<float, 3> bChannels = b_Color.getValues();

  const float xD = aChannels[0] - bChannels[0];
  const float yD = aChannels[1] - bChannels[1];
  const float zD = aChannels[2] - bChannels[2];

  return euclideanNorm(xD, yD, zD);
}


std::array<float, 3>
multiplyMatrix(const std::array<std::array<float, 3>, 3> &matrix,
               const std::array<float, 3> &vector);


} // namespace ColorSpace

#endif

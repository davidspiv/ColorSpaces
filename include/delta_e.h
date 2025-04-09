#include <array>
#include <cmath>
#include <stdexcept>

#include "Color.h"

namespace Color_Space {


template <typename T> auto euclidean_norm(const T xMag, const T yMag) {
  return std::sqrt(xMag * xMag + yMag * yMag);
}


template <typename T>
auto euclidean_norm(const T xMag, const T yMag, const T zMag) {
  return std::sqrt(xMag * xMag + yMag * yMag + zMag * zMag);
}


template <typename Color_T>
float diff_euclidean(const Color_T &a_color, const Color_T &b_color) {
  // type check: constraints, ifconstexpr (implemented), or SFINAE?
  if constexpr (!std::is_same_v<Color_T, Rgb> &&
                !std::is_same_v<Color_T, Xyz> &&
                !std::is_same_v<Color_T, Lab>) {

    throw std::domain_error("Euclidean distance only valid for Rgb, "
                            "Xyz, and Lab color spaces");
  }

  std::array<float, 3> aChannels = a_color.get_values();
  std::array<float, 3> bChannels = b_color.get_values();

  const float xD = aChannels[0] - bChannels[0];
  const float yD = aChannels[1] - bChannels[1];
  const float zD = aChannels[2] - bChannels[2];

  return euclidean_norm(xD, yD, zD);
}


} // namespace Color_Space

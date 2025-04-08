#ifndef UTIL_H
#define UTIL_H

#include <array>
#include <cmath>
#include <stdexcept>

#include "Color.h"
#include "Matrix.h"
#include "Profile.h"

using namespace Color_Space;


double to_degrees(const double radians);


double to_radians(const double degrees);


std::array<float, 3>
to_polar_color_space(const std::array<float, 3> &cartesianColor_Space);


float apply_gamma(const float c, Gamma gamma);


float remove_gamma(float c, Gamma gamma);


template <typename T> auto euclidean_norm(const T xMag, const T yMag) {
  return std::sqrt(xMag * xMag + yMag * yMag);
}


Matrix create_to_xyz_transformation_matrix(const Profile &profile);


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


template <typename Color_T> Matrix color_to_column(Color_T color) {
  auto [x, y, z] = color.get_values();

  return Matrix({{x}, {y}, {z}});
}


Profile get_profile(const Rgb_Working_space working_space);


#endif

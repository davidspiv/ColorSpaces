#ifndef UTIL_H
#define UTIL_H

#include <array>
#include <cmath>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "Color.h"
#include "Matrix.h"

using namespace Color_Space;


const static std::unordered_map<std::string, Xyz> illuminants = {
    {"a", Xyz(1.09850f, 1.00000f, 0.35585f)},
    {"b", Xyz(0.99072f, 1.00000f, 0.85223f)},
    {"c", Xyz(0.98074f, 1.00000f, 1.18232f)},
    {"d50", Xyz(0.96422f, 1.00000f, 0.82521f)},
    {"d55", Xyz(0.95682f, 1.00000f, 0.92149f)},
    {"d65", Xyz(0.95047f, 1.00000f, 1.08883f)},
    {"d75", Xyz(0.94972f, 1.00000f, 1.22638f)},
    {"e", Xyz(1.00000f, 1.00000f, 1.00000f)},
    {"f2", Xyz(0.99186f, 1.00000f, 0.67393f)},
    {"f7", Xyz(0.95041f, 1.00000f, 1.08747f)},
    {"f11", Xyz(1.00962f, 1.00000f, 0.64350f)}};


const static std::unordered_map<std::string, std::array<Xyz, 3>> primaries = {
    {"srgb",
     {Xyz(0.6400, 0.3300, 0.212656), Xyz(0.3000, 0.6000, 0.715158),
      Xyz(0.1500, 0.0600, 0.072186)}}};


double to_degrees(const double radians);


double to_radians(const double degrees);


std::array<float, 3>
to_polar_color_space(const std::array<float, 3> &cartesianColor_Space);


float apply_gamma(const float c);


template <typename T> auto euclidean_norm(const T xMag, const T yMag) {
  return std::sqrt(xMag * xMag + yMag * yMag);
}


Matrix create_to_xyz_transformation_matrix(const Xyz &reference_illuminant,
                                           const Xyz &r_xyz, const Xyz &g_xyz,
                                           const Xyz &b_xyz);

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

#endif

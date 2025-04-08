#ifndef UTIL_H
#define UTIL_H

#include <array>
#include <cmath>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

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
    {"adobe_rgb_1998",
     {Xyz(0.6400, 0.3300, 0.297361), Xyz(0.2100, 0.7100, 0.627355),
      Xyz(0.1500, 0.0600, 0.075285)}},
    {"apple_rgb",
     {Xyz(0.6250, 0.3400, 0.244634), Xyz(0.2800, 0.5950, 0.672034),
      Xyz(0.1550, 0.0700, 0.083332)}},
    {"best_rgb",
     {Xyz(0.7347, 0.2653, 0.228457), Xyz(0.2150, 0.7750, 0.737352),
      Xyz(0.1300, 0.0350, 0.034191)}},
    {"beta_rgb",
     {Xyz(0.6888, 0.3112, 0.303273), Xyz(0.1986, 0.7551, 0.663786),
      Xyz(0.1265, 0.0352, 0.032941)}},
    {"bruce_rgb",
     {Xyz(0.6400, 0.3300, 0.240995), Xyz(0.2800, 0.6500, 0.683554),
      Xyz(0.1500, 0.0600, 0.075452)}},
    {"cie_rgb",
     {Xyz(0.7350, 0.2650, 0.176204), Xyz(0.2740, 0.7170, 0.812985),
      Xyz(0.1670, 0.0090, 0.010811)}},
    {"colormatch_rgb",
     {Xyz(0.6300, 0.3400, 0.274884), Xyz(0.2950, 0.6050, 0.658132),
      Xyz(0.1500, 0.0750, 0.066985)}},
    {"don_rgb_4",
     {Xyz(0.6960, 0.3000, 0.278350), Xyz(0.2150, 0.7650, 0.687970),
      Xyz(0.1300, 0.0350, 0.033680)}},
    {"eci_rgb_v2",
     {Xyz(0.6700, 0.3300, 0.320250), Xyz(0.2100, 0.7100, 0.602071),
      Xyz(0.1400, 0.0800, 0.077679)}},
    {"ekta_space_ps5",
     {Xyz(0.6950, 0.3050, 0.260629), Xyz(0.2600, 0.7000, 0.734946),
      Xyz(0.1100, 0.0050, 0.004425)}},
    {"ntsc_rgb",
     {Xyz(0.6700, 0.3300, 0.298839), Xyz(0.2100, 0.7100, 0.586811),
      Xyz(0.1400, 0.0800, 0.114350)}},
    {"pal_secam_rgb",
     {Xyz(0.6400, 0.3300, 0.222021), Xyz(0.2900, 0.6000, 0.706645),
      Xyz(0.1500, 0.0600, 0.071334)}},
    {"prophoto_rgb",
     {Xyz(0.7347, 0.2653, 0.288040), Xyz(0.1596, 0.8404, 0.711874),
      Xyz(0.0366, 0.0001, 0.000086)}},
    {"smpte_c_rgb",
     {Xyz(0.6300, 0.3400, 0.212395), Xyz(0.3100, 0.5950, 0.701049),
      Xyz(0.1550, 0.0700, 0.086556)}},
    {"srgb",
     {Xyz(0.6400, 0.3300, 0.212656), Xyz(0.3000, 0.6000, 0.715158),
      Xyz(0.1500, 0.0600, 0.072186)}},
    {"wide_gamut_rgb",
     {Xyz(0.7350, 0.2650, 0.258187), Xyz(0.1150, 0.8260, 0.724938),
      Xyz(0.1570, 0.0180, 0.016875)}}};


const static std::vector<Profile> profiles = {{"srgb", "d65"}};


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

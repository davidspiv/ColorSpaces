#ifndef UTIL_H
#define UTIL_H

#include "color.h"
#include <array>
#include <cmath>

namespace ColorSpace {


const CieXyz referenceWhiteD60(0.950470, 1.0, 1.088830);


template <typename ColorT> struct validEuclideanType {
  static constexpr bool value = std::is_same_v<ColorT, LinearRgb> ||
                                std::is_same_v<ColorT, CieXyz> ||
                                std::is_same_v<ColorT, CieLab>;
};


template <typename ColorT,
          std::enable_if_t<validEuclideanType<ColorT>::value, int> = 0>
float distEuclideanSquared(const ColorT &a_Color, const ColorT &b_Color) {

  std::array<float, 3> a_Values = a_Color.getValues();
  std::array<float, 3> b_Values = b_Color.getValues();

  const float xD = a_Values[0] - b_Values[0];
  const float yD = a_Values[1] - b_Values[1];
  const float zD = a_Values[2] - b_Values[2];
  return xD * xD + yD * yD + zD * zD;
}


template <typename ColorT,
          std::enable_if_t<validEuclideanType<ColorT>::value, int> = 0>
float distEuclidean(const ColorT &a_Color, const ColorT &b_Color) {
  return std::sqrt(distEuclideanSquared(a_Color, b_Color));
};


std::array<float, 3>
multiplyMatrix(const std::array<std::array<float, 3>, 3> &matrix,
               const std::array<float, 3> &vector);

} // namespace ColorSpace

#endif

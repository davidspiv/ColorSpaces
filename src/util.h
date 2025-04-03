#ifndef UTIL_H
#define UTIL_H

#include "color.h"
#include <array>
#include <cmath>

namespace ColorSpace {

const CieXyz referenceWhiteD60(0.950470, 1.0, 1.088830);

template <typename ColorT>
float distEuclideanSquared(const ColorT &a_Color, const ColorT &b_Color) {
  using T = decltype(a_Color.values()[0]);

  std::array<T, 3> a_Values = a_Color.getValues;
  std::array<T, 3> b_Values = b_Color.getValues;

  const T xD = a_Values[0] - b_Values[0];
  const T yD = a_Values[1] - b_Values[1];
  const T zD = a_Values[2] - b_Values[2];
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

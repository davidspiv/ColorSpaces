#include "../include/colorDefinitions.h"
#include "../include/util.h"

#include <array>
#include <cmath>
#include <iostream>

namespace ColorSpace {


Lab::Lab(float l, float a, float b) : mValues({l, a, b}) {};


Xyz Lab::toXyz() const {
  const float fY = (mValues[0] + 16) / 116.0;
  const float fX = fY + (mValues[1] / 500.0);
  const float fZ = fY - (mValues[2] / 200.0);

  const float xR =
      (std::pow(fX, 3) > epsilon) ? std::pow(fX, 3) : (116 * fX - 16) / kappa;
  const float yR =
      (mValues[0] > (kappa * epsilon)) ? std::pow(fY, 3) : mValues[0] / kappa;
  const float zR =
      (std::pow(fZ, 3) > epsilon) ? std::pow(fZ, 3) : (116 * fZ - 16) / kappa;

  const float x = xR * referenceWhiteD60[0];
  const float y = yR * referenceWhiteD60[1];
  const float z = zR * referenceWhiteD60[2];

  return Xyz(x, y, z);
}


LchAb Lab::toLchAb() const {
  const auto [l, c, h] = toPolarColorSpace(mValues);

  return LchAb(l, c, h);
};


float Lab::diffCie76(const Lab &other) { return diffEuclidean(*this, other); }


void Lab::print() const {
  std::cout << "L: " << mValues[0] << "\na: " << mValues[1]
            << "\nb: " << mValues[2] << "\n\n";
}


} // namespace ColorSpace

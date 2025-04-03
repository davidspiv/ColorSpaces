#include "../include/colorDefinitions.h"
#include "../include/util.h"

#include <array>
#include <cmath>
#include <iostream>

namespace ColorSpace {


Xyz Lab::toXyz() const {
  const float fY = (mValues[0] + 16) / 116.0;
  const float fX = fY + (mValues[1] / 500.0);
  const float fZ = fY - (mValues[2] / 200.0);

  const float xR = (std::pow(fX, Lab::channelCount) > epsilon)
                       ? std::pow(fX, Lab::channelCount)
                       : (116 * fX - 16) / kappa;
  const float yR = (mValues[0] > (kappa * epsilon))
                       ? std::pow(fY, Lab::channelCount)
                       : mValues[0] / kappa;
  const float zR = (std::pow(fZ, Lab::channelCount) > epsilon)
                       ? std::pow(fZ, Lab::channelCount)
                       : (116 * fZ - 16) / kappa;

  const float x = xR * referenceWhiteD60[0];
  const float y = yR * referenceWhiteD60[1];
  const float z = zR * referenceWhiteD60[2];

  return Xyz(x, y, z);
}


LchAb Lab::toLchAb() const {
  const auto [l, c, h] = toPolarColorSpace(mValues);

  return LchAb(l, c, h);
};


Lab::Lab(float l, float a, float b) : mValues({l, a, b}) {};


void Lab::print() const {
  std::cout << "L: " << mValues[0] << "\na: " << mValues[1]
            << "\nb: " << mValues[2] << "\n\n";
}


LchAb::LchAb(float l, float c, float h) : mValues({l, c, h}) {}


void LchAb::print() const {
  std::cout << "L: " << mValues[0] << "\nc: " << mValues[1]
            << "\nh: " << mValues[2] << "\n\n";
}


} // namespace ColorSpace

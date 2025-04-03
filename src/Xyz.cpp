#include "../include/colorDefinitions.h"
#include "../include/util.h"

#include <algorithm>
#include <cmath>

namespace ColorSpace {


Xyz::Xyz(float x, float y, float z) : mValues({x, y, z}) {};


Rgb Xyz::toRgb() const {

  std::array<float, Xyz::channelCount> rgbAsArr =
      multiplyMatrix(this->xyzToRgbMatrix, mValues);

  const float r = std::clamp<float>(rgbAsArr[0], 0.0, 1.0);
  const float g = std::clamp<float>(rgbAsArr[1], 0.0, 1.0);
  const float b = std::clamp<float>(rgbAsArr[2], 0.0, 1.0);

  return Rgb(r, g, b);
}


Lab Xyz::toLab() const {

  const float xR = mValues[0] / referenceWhiteD60[0];
  const float yR = mValues[1] / referenceWhiteD60[1];
  const float zR = mValues[2] / referenceWhiteD60[2];

  const float fX = (xR > epsilon) ? std::cbrt(xR) : (kappa * xR + 16) / 116.0;
  const float fY = (yR > epsilon) ? std::cbrt(yR) : (kappa * yR + 16) / 116.0;
  const float fZ = (zR > epsilon) ? std::cbrt(zR) : (kappa * zR + 16) / 116.0;

  const float l = 116 * fY - 16;
  const float a = 500 * (fX - fY);
  const float b = 200 * (fY - fZ);

  return Lab(l, a, b);
}


Luv Xyz::toLuv() const {
  auto [xRef, yRef, zRef] = referenceWhiteD60;
  auto [x, y, z] = mValues;

  const float yR = y / referenceWhiteD60[1];

  const float denominator = x + 15.0 * y + 3 * z;
  if (denominator == 0.0) {
    return Luv(0.0, 0.0, 0.0);
  }

  const float uPrime = (4.0 * x) / denominator;
  const float vPrime = (9.0 * y) / denominator;

  const float refDenominator = xRef + 15.0 * yRef + 3.0 * zRef;
  const float refUPrime = (4.0 * xRef) / refDenominator;
  const float refVPrime = (9.0 * yRef) / refDenominator;

  constexpr double accError = 1e-7;
  const float uDiff = uPrime - refUPrime;
  const float vDiff = vPrime - refVPrime;

  const float l =
      (yR > epsilon) ? (116.0 * std::cbrt(yR) - 16.0) : (kappa * yR);
  const float u = (uDiff > accError) ? 13.0 * l * uDiff : 0;
  const float v = (vDiff > accError) ? 13.0 * l * vDiff : 0;

  return Luv(l, u, v);
}


Xyy Xyz::toXyy() const {
  auto [x, y, z] = mValues;
  const float sum = x + y + z;

  if (sum == 0.0) {
    return Xyy(chromaticityD60[0], chromaticityD60[1], y);
  }

  const float xNew = x / sum;
  const float yNew = y / sum;

  return Xyy(xNew, yNew, y);
}


void Xyz::print() const {
  std::cout << "X: " << mValues[0] << "\nY: " << mValues[1]
            << "\nZ: " << mValues[2] << "\n\n";
}


} // namespace ColorSpace

// http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html

#include "color.h"
#include "util.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace ColorSpace {


Srgb::Srgb(float r, float g, float b) : mValues({r, g, b}) {
  auto validate = [](float c) {
    if (std::min<float>(255, std::max<float>(0, c)) != c) {
      throw std::domain_error("Channel initalized outside of range [0, 255].");
    }
  };

  validate(r);
  validate(g);
  validate(b);
};


float Srgb::removeGamma(const float c) {
  float normalChannel = c / 255.0;

  const float breakpoint = 0.04045;

  return (normalChannel <= breakpoint)
             ? (normalChannel / 12.92)
             : pow((normalChannel + 0.055) / 1.055, 2.4);
};


LinearRgb Srgb::toLinearRgb() const {
  const float r = this->removeGamma(mValues[0]);
  const float g = this->removeGamma(mValues[1]);
  const float b = this->removeGamma(mValues[2]);

  return LinearRgb(r, g, b);
};


void Srgb::print() const {
  std::cout << "r: " << mValues[0] << "\ng: " << mValues[1]
            << "\nb: " << mValues[2] << std::endl;
}


LinearRgb::LinearRgb(float r, float g, float b) : mValues({r, g, b}) {
  auto validate = [](float c) {
    if (std::min<float>(1.0, std::max<float>(0.0, c)) != c) {
      throw std::domain_error("Channel initalized outside of range [0, 1].");
    }
  };

  validate(r);
  validate(g);
  validate(b);
};


float LinearRgb::applyGamma(const int c) {
  float corrected =
      (c <= 0.0031308) ? (c * 12.92) : 1.055 * pow(c, 1.0 / 2.4) - 0.055;
  return std::clamp(static_cast<int>(corrected * 255.0), 0, 255);
};


Srgb LinearRgb::toSrgb() const {

  const float r = this->applyGamma(mValues[0]);
  const float g = this->applyGamma(mValues[1]);
  const float b = this->applyGamma(mValues[2]);

  return Srgb(r, g, b);
};


CieXyz LinearRgb::toCieXyz() const {
  auto [x, y, z] = multiplyMatrix(this->rgbToCieXyzMatrix, mValues);

  return CieXyz(x, y, z);
}


CieXyz::CieXyz(float x, float y, float z) : mValues({x, y, z}) {};


LinearRgb CieXyz::toLinearRgb() const {

  std::array<float, 3> linearRgbAsArr =
      multiplyMatrix(this->xyzToLinearRgbMatrix, mValues);

  const float r = std::clamp<float>(linearRgbAsArr[0], 0.0, 1.0);
  const float g = std::clamp<float>(linearRgbAsArr[1], 0.0, 1.0);
  const float b = std::clamp<float>(linearRgbAsArr[2], 0.0, 1.0);

  return LinearRgb(r, g, b);
};


CieLab CieXyz::toCieLab() const {

  const float xR = mValues[0] / referenceWhiteD60.x();
  const float yR = mValues[1] / referenceWhiteD60.y();
  const float zR = mValues[2] / referenceWhiteD60.z();

  const float fX = (xR > CieLab::epsilon) ? std::cbrt(xR)
                                          : (CieLab::kappa * xR + 16) / 116.0;
  const float fY = (yR > CieLab::epsilon) ? std::cbrt(yR)
                                          : (CieLab::kappa * yR + 16) / 116.0;
  const float fZ = (zR > CieLab::epsilon) ? std::cbrt(zR)
                                          : (CieLab::kappa * zR + 16) / 116.0;

  const float l = 116 * fY - 16;
  const float a = 500 * (fX - fY);
  const float b = 200 * (fY - fZ);

  return CieLab(l, a, b);
}


void CieXyz::print() const {
  std::cout << "X: " << mValues[0] << "\nY: " << mValues[1]
            << "\nZ: " << mValues[2] << std::endl;
}


CieXyz CieLab::toCieXyz() const {
  const float fY = (mValues[0] + 16) / 116.0;
  const float fX = fY + (mValues[1] / 500.0);
  const float fZ = fY - (mValues[2] / 200.0);

  const float xR =
      (std::pow(fX, 3) > epsilon) ? std::pow(fX, 3) : (116 * fX - 16) / kappa;
  const float yR =
      (mValues[0] > (kappa * epsilon)) ? std::pow(fY, 3) : mValues[0] / kappa;
  const float zR =
      (std::pow(fZ, 3) > epsilon) ? std::pow(fZ, 3) : (116 * fZ - 16) / kappa;

  const float x = xR * referenceWhiteD60.x();
  const float y = yR * referenceWhiteD60.y();
  const float z = zR * referenceWhiteD60.z();

  return CieXyz(x, y, z);
}


CieLab::CieLab(float l, float a, float b) : mValues({l, a, b}) {};


void CieLab::print() const {
  std::cout << "L: " << mValues[0] << "\na: " << mValues[1]
            << "\nb: " << mValues[2] << std::endl;
}

} // namespace ColorSpace

// http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html

#include "color.h"
#include "util.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace ColorSpace {


SRgb::SRgb(int r, int g, int b) : mValues({r, g, b}) {
  auto validate = [](int c) {
    if (std::min(255, std::max(0, c)) != c) {
      throw std::domain_error("Channel initalized outside of range [0, 255].");
    }
  };

  validate(r);
  validate(g);
  validate(b);
};


float SRgb::removeGamma(const int c) {
  float normalChannel = c / 255.0;

  const float breakpoint = 0.04045;

  return (normalChannel <= breakpoint)
             ? (normalChannel / 12.92)
             : pow((normalChannel + 0.055) / 1.055, 2.4);
};


Rgb SRgb::toRgb() const {
  const float r = this->removeGamma(mValues[0]);
  const float g = this->removeGamma(mValues[1]);
  const float b = this->removeGamma(mValues[2]);

  return Rgb(r, g, b);
};


void SRgb::print() const {
  std::cout << "r: " << mValues[0] << "\ng: " << mValues[1]
            << "\nb: " << mValues[2] << std::endl;
}


Rgb::Rgb(float r, float g, float b) : mValues({r, g, b}) {
  auto validate = [](float c) {
    if (std::min<float>(1.0, std::max<float>(0.0, c)) != c) {
      throw std::domain_error("Channel initalized outside of range [0, 1].");
    }
  };

  validate(r);
  validate(g);
  validate(b);
};


float Rgb::applyGamma(const int c) {
  float corrected =
      (c <= 0.0031308) ? (c * 12.92) : 1.055 * pow(c, 1.0 / 2.4) - 0.055;
  return std::clamp(corrected * 255.0, 0.0, 255.0);
};


SRgb Rgb::toSRgb() const {

  const float r = this->applyGamma(mValues[0]);
  const float g = this->applyGamma(mValues[1]);
  const float b = this->applyGamma(mValues[2]);

  return SRgb(r, g, b);
};


Xyz Rgb::toXyz() const {
  auto [x, y, z] = multiplyMatrix(this->rgbToXyzMatrix, mValues);

  return Xyz(x, y, z);
}


Xyz::Xyz(float x, float y, float z) : mValues({x, y, z}) {};


Rgb Xyz::toRgb() const {

  std::array<float, Xyz::channelCount> rgbAsArr =
      multiplyMatrix(this->xyzToRgbMatrix, mValues);

  const float r = std::clamp<float>(rgbAsArr[0], 0.0, 1.0);
  const float g = std::clamp<float>(rgbAsArr[1], 0.0, 1.0);
  const float b = std::clamp<float>(rgbAsArr[2], 0.0, 1.0);

  return Rgb(r, g, b);
};


Lab Xyz::toLab() const {

  const float xR = mValues[0] / referenceWhiteD60.x();
  const float yR = mValues[1] / referenceWhiteD60.y();
  const float zR = mValues[2] / referenceWhiteD60.z();

  const float fX = (xR > epsilon) ? std::cbrt(xR) : (kappa * xR + 16) / 116.0;
  const float fY = (yR > epsilon) ? std::cbrt(yR) : (kappa * yR + 16) / 116.0;
  const float fZ = (zR > epsilon) ? std::cbrt(zR) : (kappa * zR + 16) / 116.0;

  const float l = 116 * fY - 16;
  const float a = 500 * (fX - fY);
  const float b = 200 * (fY - fZ);

  return Lab(l, a, b);
}


void Xyz::print() const {
  std::cout << "X: " << mValues[0] << "\nY: " << mValues[1]
            << "\nZ: " << mValues[2] << std::endl;
}


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

  const float x = xR * referenceWhiteD60.x();
  const float y = yR * referenceWhiteD60.y();
  const float z = zR * referenceWhiteD60.z();

  return Xyz(x, y, z);
}


Lch Lab::toLch() const {
  const float c = std::sqrt(mValues[0] * mValues[0] + mValues[1] * mValues[1]);
  const float hComponent = toDegrees(std::atan2(mValues[2], mValues[1]));

  const float h = (hComponent >= 0) ? hComponent : hComponent + 360.0;

  return Lch(mValues[0], c, h);
};


Lab::Lab(float l, float a, float b) : mValues({l, a, b}) {};


void Lab::print() const {
  std::cout << "L: " << mValues[0] << "\na: " << mValues[1]
            << "\nb: " << mValues[2] << std::endl;
}


Lch::Lch(float l, float c, float h) : mValues({l, c, h}) {}


void Lch::print() const {
  std::cout << "L: " << mValues[0] << "\nc: " << mValues[1]
            << "\nh: " << mValues[2] << std::endl;
}


Luv::Luv(float l, float u, float v) : mValues({l, u, v}) {}


void Luv::print() const {
  std::cout << "L: " << mValues[0] << "\nu: " << mValues[1]
            << "\nv: " << mValues[2] << std::endl;
}

} // namespace ColorSpace

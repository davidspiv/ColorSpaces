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


float SRgb::removeGamma(int c) {
  float normalChannel = static_cast<double>(c) / 255.0;

  const float breakpoint = 0.04045f;

  return (normalChannel <= breakpoint)
             ? (normalChannel / 12.92f)
             : std::pow((normalChannel + 0.055f) / 1.055f, 2.4f);
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


float Rgb::applyGamma(const float c) {
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


void Rgb::print() const {
  std::cout << "R: " << mValues[0] << "\nG: " << mValues[1]
            << "\nB: " << mValues[2] << std::endl;
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


void Xyz::print() const {
  std::cout << "X: " << mValues[0] << "\nY: " << mValues[1]
            << "\nZ: " << mValues[2] << "\n\n";
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


Luv::Luv(float l, float u, float v) : mValues({l, u, v}) {}


LchUv Luv::toLchUv() const {
  const auto [l, u, v] = toPolarColorSpace(mValues);

  return LchUv(l, u, v);
};


void Luv::print() const {
  std::cout << "L: " << mValues[0] << "\nu: " << mValues[1]
            << "\nv: " << mValues[2] << "\n\n";
}


LchUv::LchUv(float l, float c, float h) : mValues({l, c, h}) {}


void LchUv::print() const {
  std::cout << "L: " << mValues[0] << "\nc: " << mValues[1]
            << "\nh: " << mValues[2] << "\n\n";
}


Xyy::Xyy(float x, float y, float Y) : mValues({x, y, Y}) {}


void Xyy::print() const {
  std::cout << "x: " << mValues[0] << "\ny: " << mValues[1]
            << "\nY: " << mValues[2] << "\n\n";
}

} // namespace ColorSpace

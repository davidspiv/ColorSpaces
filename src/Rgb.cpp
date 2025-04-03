#include "../include/colorDefinitions.h"
#include "../include/util.h"

#include <algorithm>
#include <array>
#include <iostream>

namespace ColorSpace {


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


} // namespace ColorSpace

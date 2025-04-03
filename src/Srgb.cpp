#include "../include/colorDefinitions.h"

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


} // namespace ColorSpace

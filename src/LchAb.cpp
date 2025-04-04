#include "../include/colorDefinitions.h"

#include <array>
#include <cmath>
#include <iostream>

namespace ColorSpace {


LchAb::LchAb(float l, float c, float h) : mValues({l, c, h}) {}


float LchAb::diffCie94(const LchAb &other, Mode mode) {
  auto [lOther, cOther, hOther] = other.getValues();

  const float lDelta = mValues[0] - lOther;
  const float cDelta = mValues[1] - cOther;

  // Ensure hue difference wraps correctly
  float hDelta = mValues[2] - hOther;
  while (hDelta > 180.0) {
    hDelta -= 360.0;
  }
  while (hDelta < -180.0) {
    hDelta += 360.0;
  }

  // parametric weighting factors
  const float kL = 1.0;
  const float kC = (mode == GRAPHICS) ? 0.045 : 0.048;
  const float kH = (mode == GRAPHICS) ? 0.015 : 0.014;

  const float sL = 1;
  const float sC = 1 + kC * cOther; // Scale chroma
  const float sH = 1 + kH * cOther; // Scale hue using chroma

  const float deltaH2 = hDelta * hDelta;

  const float xMag = lDelta / (kL * sL);
  const float yMag = cDelta / (kC * sC);
  const float zMag = std::sqrt(deltaH2) / (kH * sH);

  return std::sqrt(xMag * xMag + yMag * yMag + zMag * zMag);
}


void LchAb::print() const {
  std::cout << "L: " << mValues[0] << "\nc: " << mValues[1]
            << "\nh: " << mValues[2] << "\n\n";
}


} // namespace ColorSpace

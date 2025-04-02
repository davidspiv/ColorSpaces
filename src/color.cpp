// http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html

#include "color.h"
#include "util.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>

namespace ColorSpace {


LinearRgb Srgb::toLinearRgb() const {
  auto linearizeChannel = [](int c) -> float {
    float normalized = c / 255.0;
    return (normalized <= 0.04045) ? (normalized / 12.92)
                                   : pow((normalized + 0.055) / 1.055, 2.4);
  };

  const float r = linearizeChannel(this->r);
  const float g = linearizeChannel(this->g);
  const float b = linearizeChannel(this->b);

  return LinearRgb(r, g, b);
};


CieLab Srgb::toCieLab() const {
  LinearRgb linearRgb = this->toLinearRgb();
  CieXyz cieXyz = linearRgb.toCieXyz();

  return cieXyz.toCieLab();
}


Srgb LinearRgb::toSrgb() const {
  auto applyGammaToChannel = [](float c) -> int {
    float corrected =
        (c <= 0.0031308) ? (c * 12.92) : 1.055 * pow(c, 1.0 / 2.4) - 0.055;
    return std::clamp(static_cast<int>(corrected * 255.0), 0, 255);
  };

  const float r = applyGammaToChannel(this->r);
  const float g = applyGammaToChannel(this->g);
  const float b = applyGammaToChannel(this->b);

  return Srgb(r, g, b);
};


CieXyz LinearRgb::toCieXyz() const {
  // reference white - D65
  constexpr std::array<std::array<float, 3>, 3> rgbToCieXyzMatrix = {
      {{0.4124564, 0.3575761, 0.1804375},
       {0.2126729, 0.7151522, 0.0721750},
       {0.0193339, 0.1191920, 0.9503041}}};

  std::array<float, 3> cieRGB =
      multiplyMatrix(rgbToCieXyzMatrix, {this->r, this->g, this->b});

  return CieXyz(cieRGB[0], cieRGB[1], cieRGB[2]);
}


LinearRgb CieXyz::toLinearRgb() const {
  // reference white - D65
  constexpr std::array<std::array<float, 3>, 3> xyzToLinearRgbMatrix = {{
      {3.2404542, -1.5371385, -0.4985314},
      {-0.9692660, 1.8760108, 0.0415560},
      {0.0556434, -0.2040259, 1.0572252},
  }};

  std::array<float, 3> linearRgb =
      multiplyMatrix(xyzToLinearRgbMatrix, {this->x, this->y, this->z});

  const float r = std::clamp<float>(linearRgb[0], 0.0, 1.0);
  const float g = std::clamp<float>(linearRgb[1], 0.0, 1.0);
  const float b = std::clamp<float>(linearRgb[2], 0.0, 1.0);

  return LinearRgb(r, g, b);
};


CieLab CieXyz::toCieLab() const {

  const float xR = this->x / referenceWhiteD60.x;
  const float yR = this->y / referenceWhiteD60.y;
  const float zR = this->z / referenceWhiteD60.z;

  const float fX = (xR > epsilon) ? std::cbrt(xR) : (kappa * xR + 16) / 116.0;
  const float fY = (yR > epsilon) ? std::cbrt(yR) : (kappa * yR + 16) / 116.0;
  const float fZ = (zR > epsilon) ? std::cbrt(zR) : (kappa * zR + 16) / 116.0;

  const float l = 116 * fY - 16;
  const float a = 500 * (fX - fY);
  const float b = 200 * (fY - fZ);

  return CieLab(l, a, b);
}


CieXyz CieLab::toCieXyz() const {
  const float fY = (this->l + 16) / 116.0;
  const float fX = fY + (this->a / 500.0);
  const float fZ = fY - (this->b / 200.0);

  const float xR =
      (std::pow(fX, 3) > epsilon) ? std::pow(fX, 3) : (116 * fX - 16) / kappa;
  const float yR =
      (this->l > (kappa * epsilon)) ? std::pow(fY, 3) : this->l / kappa;
  const float zR =
      (std::pow(fZ, 3) > epsilon) ? std::pow(fZ, 3) : (116 * fZ - 16) / kappa;

  const float x = xR * referenceWhiteD60.x;
  const float y = yR * referenceWhiteD60.y;
  const float z = zR * referenceWhiteD60.z;

  return CieXyz(x, y, z);
}


Srgb CieLab::toSrgb() const {
  CieXyz cieXyz = this->toCieXyz();
  LinearRgb linearRgb = cieXyz.toLinearRgb();

  return linearRgb.toSrgb();
}

} // namespace ColorSpace

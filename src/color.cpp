// http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html

#include "color.h"
#include "util.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>

namespace ColorSpace {

StdRgb::StdRgb(int r, int g, int b) : r(r), g(g), b(b) {
  auto validate = [](int c) {
    if (std::min(255, std::max(0, c)) != c) {
      throw std::domain_error("Channel initalized outside of range [0, 255].");
    }
  };

  validate(r);
  validate(g);
  validate(b);
};


LinRgb StdRgb::toLinRgb() const {
  auto linearizeChannel = [](int c) -> double {
    double normalized = c / 255.0;
    return (normalized <= 0.04045) ? (normalized / 12.92)
                                   : pow((normalized + 0.055) / 1.055, 2.4);
  };

  const double r = linearizeChannel(this->r);
  const double g = linearizeChannel(this->g);
  const double b = linearizeChannel(this->b);

  return LinRgb(r, g, b);
};


CieLab StdRgb::toCieLab() const {
  LinRgb linRgb = this->toLinRgb();
  CieXyz cieXyz = linRgb.toXyz();

  return cieXyz.toCieLab();
}


LinRgb::LinRgb(double r, double g, double b) : r(r), g(g), b(b) {
  auto validate = [](double c) {
    if (std::min(1.0, std::max(0.0, c)) != c) {
      throw std::domain_error("Channel initalized outside of range [0, 1].");
    }
  };

  validate(r);
  validate(g);
  validate(b);
};


StdRgb LinRgb::toStdRgb() const {
  auto applyGammaToChannel = [](double c) -> int {
    double corrected =
        (c <= 0.0031308) ? (c * 12.92) : 1.055 * pow(c, 1.0 / 2.4) - 0.055;
    return std::clamp(static_cast<int>(corrected * 255.0), 0, 255);
  };

  const double r = applyGammaToChannel(this->r);
  const double g = applyGammaToChannel(this->g);
  const double b = applyGammaToChannel(this->b);

  return StdRgb(r, g, b);
};


CieXyz LinRgb::toXyz() const {
  // reference white - D65
  constexpr std::array<std::array<double, 3>, 3> rgbToXYZMatrix = {
      {{0.4124564, 0.3575761, 0.1804375},
       {0.2126729, 0.7151522, 0.0721750},
       {0.0193339, 0.1191920, 0.9503041}}};

  std::array<double, 3> cieRGB =
      multiplyMatrix(rgbToXYZMatrix, {this->r, this->g, this->b});

  return CieXyz(cieRGB[0], cieRGB[1], cieRGB[2]);
}


CieXyz::CieXyz(double x, double y, double z) : x(x), y(y), z(z) {};


LinRgb CieXyz::toLinRgb() const {
  // reference white - D65
  constexpr std::array<std::array<double, 3>, 3> xyzToLinRgbMatrix = {{
      {3.2404542, -1.5371385, -0.4985314},
      {-0.9692660, 1.8760108, 0.0415560},
      {0.0556434, -0.2040259, 1.0572252},
  }};

  std::array<double, 3> linRgb =
      multiplyMatrix(xyzToLinRgbMatrix, {this->x, this->y, this->z});

  const double r = std::clamp(linRgb[0], 0.0, 1.0);
  const double g = std::clamp(linRgb[1], 0.0, 1.0);
  const double b = std::clamp(linRgb[2], 0.0, 1.0);

  return LinRgb(r, g, b);
};


CieLab CieXyz::toCieLab() const {

  const double xR = this->x / referenceWhiteD60.x;
  const double yR = this->y / referenceWhiteD60.y;
  const double zR = this->z / referenceWhiteD60.z;

  const double fX = (xR > epsilon) ? std::cbrt(xR) : (kappa * xR + 16) / 116.0;
  const double fY = (yR > epsilon) ? std::cbrt(yR) : (kappa * yR + 16) / 116.0;
  const double fZ = (zR > epsilon) ? std::cbrt(zR) : (kappa * zR + 16) / 116.0;

  const double lStar = 116 * fY - 16;
  const double aStar = 500 * (fX - fY);
  const double bStar = 200 * (fY - fZ);

  return CieLab(lStar, aStar, bStar);
}


CieLab::CieLab(double lStar, double aStar, double bStar)
    : lStar(lStar), aStar(aStar), bStar(bStar) {};


CieXyz CieLab::toXyz() const {
  const double fY = (this->lStar + 16) / 116.0;
  const double fX = fY + (this->aStar / 500.0);
  const double fZ = fY - (this->bStar / 200.0);

  const double xR =
      (std::pow(fX, 3) > epsilon) ? std::pow(fX, 3) : (116 * fX - 16) / kappa;
  const double yR =
      (this->lStar > (kappa * epsilon)) ? std::pow(fY, 3) : this->lStar / kappa;
  const double zR =
      (std::pow(fZ, 3) > epsilon) ? std::pow(fZ, 3) : (116 * fZ - 16) / kappa;

  const double x = xR * referenceWhiteD60.x;
  const double y = yR * referenceWhiteD60.y;
  const double z = zR * referenceWhiteD60.z;

  return CieXyz(x, y, z);
}


StdRgb CieLab::toStdRgb() const {
  CieXyz cieXyz = this->toXyz();
  LinRgb linRgb = cieXyz.toLinRgb();

  return linRgb.toStdRgb();
}

} // namespace ColorSpace

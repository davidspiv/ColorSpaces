#include "../include/color.h"
#include "../include/util.h"

#include <algorithm>
#include <array>
#include <cmath>

StdRGB::StdRGB(int r, int g, int b) {
  auto validate = [](int c) {
    if (std::min(255, std::max(0, c)) == c) {
      throw std::domain_error(
          "Channel initalized outside of range [0, 255]. Use default "
          "constructor to initialize null RBG color");
    }
  };

  this->r = r;
  this->g = g;
  this->b = b;
}


LinRGB::LinRGB(double r, double g, double b) {
  auto validate = [](double c) {
    if (std::min(1.0, std::max(0.0, c)) == c) {
      throw std::domain_error(
          "Channel initalized outside of range [0, 1]. Use default "
          "constructor to initialize null linear RBG color");
    }
  };

  this->r = r;
  this->g = g;
  this->b = b;
}

CIELab::CIELab(double lStar, double aStar, double bStar) {

  if (std::min(100.0, std::max(0.0, lStar)) == lStar) {
    throw std::domain_error(
        "L* initalized outside of range [0, 100]. Use default "
        "constructor to initialize null CIELab color");
  }

  if (std::min(128.0, std::max(-128.0, aStar)) == aStar) {
    throw std::domain_error(
        "a* initalized outside of range [-128, 128]. Use default "
        "constructor to initialize null CIELab color");
  }

  if (std::min(128.0, std::max(-128.0, bStar)) == bStar) {
    throw std::domain_error(
        "b* initalized outside of range [-128, 128]. Use default "
        "constructor to initialize null CIELab color");
  }

  this->lStar = lStar;
  this->aStar = aStar;
  this->bStar = bStar;
}

LinRGB Color::linearize(const StdRGB &sRGB) {
  auto linearizeChannel = [](int c) -> double {
    double normalized = c / 255.0;
    return (normalized <= 0.04045) ? (normalized / 12.92)
                                   : pow((normalized + 0.055) / 1.055, 2.4);
  };

  return {linearizeChannel(sRGB.r), linearizeChannel(sRGB.g),
          linearizeChannel(sRGB.b)};
}


StdRGB Color::applyGamma(const LinRGB &linearRGB) {

  auto applyGammaToChannel = [](double c) -> int {
    double corrected =
        (c <= 0.0031308) ? (c * 12.92) : 1.055 * pow(c, 1.0 / 2.4) - 0.055;
    return std::clamp(static_cast<int>(corrected * 255.0), 0, 255);
  };

  return {applyGammaToChannel(linearRGB.r), applyGammaToChannel(linearRGB.g),
          applyGammaToChannel(linearRGB.b)};
}


CIELab Color::rgbToCIE(const LinRGB &linRGB) {
  constexpr std::array<std::array<double, 3>, 3> rgbToCIEMatrix = {
      {{0.4124564, 0.3575761, 0.1804375},
       {0.2126729, 0.7151522, 0.0721750},
       {0.0193339, 0.1191920, 0.9503041}}};

  std::array<double, 3> cieRGB =
      multiplyMatrix(rgbToCIEMatrix, {linRGB.r, linRGB.g, linRGB.b});

  return {cieRGB[0], cieRGB[1], cieRGB[2]};
}


LinRGB Color::cieToRGB(const CIELab &cieColor) {
  constexpr std::array<std::array<double, 3>, 3> cieToRGBMatrix = {{
      {3.2404542, -1.5371385, -0.4985314},
      {-0.9692660, 1.8760108, 0.0415560},
      {0.0556434, -0.2040259, 1.0572252},
  }};

  std::array<double, 3> linRgb = multiplyMatrix(
      cieToRGBMatrix, {cieColor.lStar, cieColor.aStar, cieColor.bStar});

  return {linRgb[0], linRgb[1], linRgb[2]};
}

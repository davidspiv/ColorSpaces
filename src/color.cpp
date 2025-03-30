#include "../include/color.h"
#include "../include/util.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>


Color::Color(const StdRGB &stdRGB) {
  auto validate = [](int c) {
    if (std::min(255, std::max(0, c)) != c) {
      throw std::domain_error("Channel initalized outside of range [0, 255].");
    }
  };

  auto [r, g, b] = stdRGB;
  validate(r);
  validate(g);
  validate(b);

  _sRGB = stdRGB;
};


Color::Color(const LinRGB &linRGB) {
  auto validate = [](double c) {
    if (std::min(1.0, std::max(0.0, c)) != c) {
      throw std::domain_error("Channel initalized outside of range [0, 1].");
    }
  };

  auto [r, g, b] = linRGB;
  validate(r);
  validate(g);
  validate(b);

  _linRGB = linRGB;
};


Color::Color(const CieXYZ &ceiLab) {

  auto [x, y, z] = ceiLab;

  if (std::min(100.0, std::max(0.0, x)) != x) {
    throw std::domain_error("L* initalized outside of range [0, 100].");
  }

  if (std::min(128.0, std::max(-128.0, y)) != y) {
    throw std::domain_error("a* initalized outside of range [-128, 128].");
  }

  if (std::min(128.0, std::max(-128.0, z)) != z) {
    throw std::domain_error("b* initalized outside of range [-128, 128].");
  }

  _cieXYZ = ceiLab;
}


LinRGB Color::linearize(const StdRGB &sRGB) {
  auto linearizeChannel = [](int c) -> double {
    double normalized = c / 255.0;
    return (normalized <= 0.04045) ? (normalized / 12.92)
                                   : pow((normalized + 0.055) / 1.055, 2.4);
  };

  double r = linearizeChannel(sRGB.r);
  double g = linearizeChannel(sRGB.g);
  double b = linearizeChannel(sRGB.b);

  return {r, g, b};
}


StdRGB Color::applyGamma(const LinRGB &linRGB) {

  auto applyGammaToChannel = [](double c) -> int {
    double corrected =
        (c <= 0.0031308) ? (c * 12.92) : 1.055 * pow(c, 1.0 / 2.4) - 0.055;
    return std::clamp(static_cast<int>(corrected * 255.0), 0, 255);
  };

  return StdRGB(applyGammaToChannel(linRGB.r), applyGammaToChannel(linRGB.g),
                applyGammaToChannel(linRGB.b));
}


CieXYZ Color::rgbToXYZ(const LinRGB &linRGB) {
  // reference white - D65
  constexpr std::array<std::array<double, 3>, 3> rgbToXYZMatrix = {
      {{0.4124564, 0.3575761, 0.1804375},
       {0.2126729, 0.7151522, 0.0721750},
       {0.0193339, 0.1191920, 0.9503041}}};

  std::array<double, 3> cieRGB =
      multiplyMatrix(rgbToXYZMatrix, {linRGB.r, linRGB.g, linRGB.b});

  return CieXYZ(cieRGB[0], cieRGB[1], cieRGB[2]);
}


LinRGB Color::xyzToRGB(const CieXYZ &ceiLab) {
  // reference white - D65
  constexpr std::array<std::array<double, 3>, 3> xyzToRGBMatrix = {{
      {3.2404542, -1.5371385, -0.4985314},
      {-0.9692660, 1.8760108, 0.0415560},
      {0.0556434, -0.2040259, 1.0572252},
  }};

  std::array<double, 3> linRgb =
      multiplyMatrix(xyzToRGBMatrix, {ceiLab.x, ceiLab.y, ceiLab.z});

  return LinRGB(linRgb[0], linRgb[1], linRgb[2]);
}


CieLab Color::xyzToLab(const CieXYZ &cieXYZ) {

  const static CieXYZ referenceWhiteD60 = {0.950470, 1.0, 1.088830};
  const static double epsilon = 216.0 / 24389.0;
  const static double kappa = 24389.0 / 27.0;

  auto [x, y, z] = cieXYZ;

  const double xR = x / referenceWhiteD60.x;
  const double yR = y / referenceWhiteD60.y;
  const double zR = z / referenceWhiteD60.z;

  const double fX = (xR > epsilon) ? std::cbrt(xR) : (kappa * xR + 16) / 116.0;
  const double fY = (yR > epsilon) ? std::cbrt(yR) : (kappa * yR + 16) / 116.0;
  const double fZ = (zR > epsilon) ? std::cbrt(zR) : (kappa * zR + 16) / 116.0;

  const double lStar = 116 * fY - 16;
  const double aStar = 500 * (fX - fY);
  const double bStar = 200 * (fY - fZ);

  return CieLab(lStar, aStar, bStar);
};


StdRGB Color::sRGB() {

  if (_sRGB.r >= 0) {
    return _sRGB;
  }

  if (_linRGB.r >= 0) {
    _sRGB = applyGamma(_linRGB);
    return _sRGB;
  }

  if (_cieXYZ.x >= 0) {
    _linRGB = xyzToRGB(_cieXYZ);
    _sRGB = applyGamma(_linRGB);
    return _sRGB;
  }

  throw std::runtime_error("Color state error");
}


LinRGB Color::linRGB() {
  if (_linRGB.r >= 0) {
    return {_linRGB.r, _linRGB.g, _linRGB.b};
  }

  if (_sRGB.r >= 0) {
    _linRGB = linearize(_sRGB);
    return {_linRGB.r, _linRGB.g, _linRGB.b};
  }

  if (_cieXYZ.x >= 0) {
    _linRGB = xyzToRGB(_cieXYZ);
    return _linRGB;
  }

  throw std::runtime_error("Color state error");
}


CieXYZ Color::cieXYZ() {
  if (_cieXYZ.x >= 0) {
    return {_cieXYZ.x, _cieXYZ.y, _cieXYZ.z};
  }

  if (_linRGB.r >= 0) {
    _cieXYZ = rgbToXYZ(_linRGB);
    return {_cieXYZ.x, _cieXYZ.y, _cieXYZ.z};
  }

  if (_sRGB.r >= 0) {
    _linRGB = linearize(_sRGB);
    _cieXYZ = rgbToXYZ(_linRGB);
    return _cieXYZ;
  }

  throw std::runtime_error("Color state error");
}


CieLab Color::cieLab() {
  if (_cieLab.lStar >= 0) {
    return {_cieLab.lStar, _cieLab.aStar, _cieLab.bStar};
  }

  if (_cieXYZ.x >= 0) {
    _cieLab = xyzToLab(_cieXYZ);
    return _cieLab;
  }

  if (_sRGB.r >= 0) {
    _linRGB = linearize(_sRGB);
    _cieXYZ = rgbToXYZ(_linRGB);
    _cieLab = xyzToLab(_cieXYZ);
    return _cieLab;
  }

  throw std::runtime_error("Color state error");
};

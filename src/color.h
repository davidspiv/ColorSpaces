#ifndef COLOR_H
#define COLOR_H

#include <algorithm>
#include <stdexcept>

namespace ColorSpace {

struct LinearRgb;
struct CieXyz;
struct CieLab;

struct Srgb {
  int r, g, b;

  explicit constexpr Srgb(int r, int g, int b) : r(r), g(g), b(b) {
    auto validate = [](int c) {
      if (std::min(255, std::max(0, c)) != c) {
        throw std::domain_error(
            "Channel initalized outside of range [0, 255].");
      }
    };

    validate(r);
    validate(g);
    validate(b);
  };


  LinearRgb toLinearRgb() const;
};

struct LinearRgb {
  float r, g, b;

  explicit constexpr LinearRgb(float r, float g, float b) : r(r), g(g), b(b) {
    auto validate = [](float c) {
      if (std::min<float>(1.0, std::max<float>(0.0, c)) != c) {
        throw std::domain_error("Channel initalized outside of range [0, 1].");
      }
    };

    validate(r);
    validate(g);
    validate(b);
  };

  Srgb toSrgb() const;
  CieXyz toCieXyz() const;
};

struct CieXyz {
  float x, y, z;

  explicit constexpr CieXyz(float x, float y, float z) : x(x), y(y), z(z) {};

  LinearRgb toLinearRgb() const;
  CieLab toCieLab() const;
};

struct CieLab {
  float l, a, b;

  explicit constexpr CieLab(float l, float a, float b) : l(l), a(a), b(b) {};

  CieXyz toCieXyz() const;
};

} // namespace ColorSpace

#endif

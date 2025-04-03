#ifndef COLOR_H
#define COLOR_H

#include <algorithm>
#include <array>

namespace ColorSpace {

class LinearRgb;
class CieXyz;
class CieLab;

class Srgb {
private:
  std::array<float, 3> values; // r, b, g

  static float removeGamma(const float c);

public:
  Srgb(float r, float g, float b);

  LinearRgb toLinearRgb() const;
  void print() const;
};


class LinearRgb {
private:
  std::array<float, 3> values; // r, b, g

public:
  LinearRgb(float r, float g, float b);

  Srgb toSrgb() const;
  CieXyz toCieXyz() const;
  float distEuclideanSquared(const LinearRgb &other) const;
  float distEuclidean(const LinearRgb &other) const;

private:
  static float applyGamma(int c);

  static constexpr std::array<std::array<float, 3>, 3> rgbToCieXyzMatrix = {
      {{0.4124564, 0.3575761, 0.1804375},
       {0.2126729, 0.7151522, 0.0721750},
       {0.0193339, 0.1191920, 0.9503041}}}; // reference white - D65
};

class CieXyz {
private:
  std::array<float, 3> values; // x, y, z

public:
  explicit constexpr CieXyz(float x, float y, float z) : values({x, y, z}) {};

  float x() const { return values[0]; }
  float y() const { return values[1]; }
  float z() const { return values[2]; }

  LinearRgb toLinearRgb() const;
  CieLab toCieLab() const;
  float distEuclideanSquared(const CieXyz &other) const;
  float distEuclidean(const CieXyz &other) const;

  void print() const;

private:
  static constexpr std::array<std::array<float, 3>, 3> xyzToLinearRgbMatrix = {{
      {3.2404542, -1.5371385, -0.4985314},
      {-0.9692660, 1.8760108, 0.0415560},
      {0.0556434, -0.2040259, 1.0572252}, // reference white - D65
  }};
};

class CieLab {
private:
  std::array<float, 3> values; // l, a, b

public:
  explicit constexpr CieLab(float l, float a, float b) : values({l, a, b}) {};

  CieXyz toCieXyz() const;
  float distEuclideanSquared(const CieLab &other) const;
  float distEuclidean(const CieLab &other) const;
  // float distCIE76(const CieLab &other);
  // float distCIEDE2000(const CieLab &other);
  // float distCIE94(const CieLab &other);

  void print() const;

  static constexpr float epsilon = 216.0 / 24389.0;
  static constexpr float kappa = 24389.0 / 27.0;
};

} // namespace ColorSpace

#endif

// float distEuclideanSquared(const CieLch &other);
// float distEuclidean(const CieLch &other);
// float distCIE76(const CieLch &other);
// float distCIEDE2000(const CieLch &other);
// float distCIE94(const CieLch &other);

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
  std::array<int, 3> mValues; // r, b, g

public:
  Srgb(int r, int g, int b);

  std::array<int, 3> values() { return mValues; };

  LinearRgb toLinearRgb() const;
  void print() const;

private:
  static float removeGamma(const int c);
};


class LinearRgb {
private:
  std::array<float, 3> mValues; // r, b, g

public:
  LinearRgb(float r, float g, float b);

  std::array<float, 3> values() { return mValues; };

  Srgb toSrgb() const;
  CieXyz toCieXyz() const;

private:
  static float applyGamma(const int c);

  static constexpr std::array<std::array<float, 3>, 3> rgbToCieXyzMatrix = {
      {{0.4124564, 0.3575761, 0.1804375},
       {0.2126729, 0.7151522, 0.0721750},
       {0.0193339, 0.1191920, 0.9503041}}}; // reference white - D65
};


class CieXyz {
private:
  std::array<float, 3> mValues; // x, y, z

public:
  CieXyz(float x, float y, float z);

  float x() const { return mValues[0]; }
  float y() const { return mValues[1]; }
  float z() const { return mValues[2]; }
  std::array<float, 3> values() { return mValues; };

  LinearRgb toLinearRgb() const;
  CieLab toCieLab() const;

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
  std::array<float, 3> mValues; // l, a, b

public:
  CieLab(float l, float a, float b);

  std::array<float, 3> values() { return mValues; };

  static constexpr float epsilon = 216.0 / 24389.0;
  static constexpr float kappa = 24389.0 / 27.0;

  CieXyz toCieXyz() const;
  // float distCIE76(const CieLab &other);
  // float distCIEDE2000(const CieLab &other);
  // float distCIE94(const CieLab &other);

  void print() const;
};


} // namespace ColorSpace

#endif

// float distEuclideanSquared(const CieLch &other);
// float distEuclidean(const CieLch &other);
// float distCIE76(const CieLch &other);
// float distCIEDE2000(const CieLch &other);
// float distCIE94(const CieLch &other);

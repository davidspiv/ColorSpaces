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
  static constexpr size_t channelCount = 3;

  std::array<int, channelCount> mValues; // r, g, b

public:
  Srgb(int r, int g, int b);

  std::array<int, channelCount> getValues() const { return mValues; }

  LinearRgb toLinearRgb() const;

  void print() const;

private:
  static float removeGamma(int c);
};


class LinearRgb {
private:
  static constexpr size_t channelCount = 3;
  static constexpr std::array<std::array<float, channelCount>, channelCount>
      rgbToCieXyzMatrix = {{
          {0.4124564, 0.3575761, 0.1804375},
          {0.2126729, 0.7151522, 0.0721750},
          {0.0193339, 0.1191920, 0.9503041} // Reference white - D65
      }};

  std::array<float, channelCount> mValues; // r, g, b

public:
  LinearRgb(float r, float g, float b);

  std::array<float, channelCount> getValues() const { return mValues; }

  Srgb toSrgb() const;
  CieXyz toCieXyz() const;

private:
  static float applyGamma(int c);
};


class CieXyz {
private:
  static constexpr size_t channelCount = 3;
  static constexpr std::array<std::array<float, channelCount>, channelCount>
      xyzToLinearRgbMatrix = {{
          {3.2404542, -1.5371385, -0.4985314},
          {-0.9692660, 1.8760108, 0.0415560},
          {0.0556434, -0.2040259, 1.0572252} // Reference white - D65
      }};

  std::array<float, channelCount> mValues; // x, y, z

public:
  CieXyz(float x, float y, float z);

  float x() const { return mValues[0]; }
  float y() const { return mValues[1]; }
  float z() const { return mValues[2]; }
  std::array<float, channelCount> getValues() const { return mValues; }

  LinearRgb toLinearRgb() const;
  CieLab toCieLab() const;

  void print() const;
};


class CieLab {
private:
  static constexpr size_t channelCount = 3;
  static constexpr float epsilon = 216.0f / 24389.0f;
  static constexpr float kappa = 24389.0f / 27.0f;

  std::array<float, channelCount> mValues; // l, a, b

public:
  CieLab(float l, float a, float b);

  std::array<float, channelCount> getValues() const { return mValues; }

  CieXyz toCieXyz() const;

  void print() const;
};

} // namespace ColorSpace

#endif

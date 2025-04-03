#ifndef COLOR_H
#define COLOR_H

#include <algorithm>
#include <array>

namespace ColorSpace {


class LinearRgb;
class Xyz;
class Lab;
class Lch;


class Srgb {
  static constexpr size_t channelCount = 3;

private:
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
public:
  static constexpr size_t channelCount = 3;

private:
  static constexpr std::array<std::array<float, channelCount>, channelCount>
      rgbToXyzMatrix = {{
          {0.4124564, 0.3575761, 0.1804375},
          {0.2126729, 0.7151522, 0.0721750},
          {0.0193339, 0.1191920, 0.9503041} // Reference white - D65
      }};

  std::array<float, channelCount> mValues; // r, g, b

public:
  LinearRgb(float r, float g, float b);

  std::array<float, channelCount> getValues() const { return mValues; }

  Srgb toSrgb() const;
  Xyz toXyz() const;

private:
  static float applyGamma(int c);
};


class Xyz {
public:
  static constexpr size_t channelCount = 3;

private:
  static constexpr std::array<std::array<float, channelCount>, channelCount>
      xyzToLinearRgbMatrix = {{
          {3.2404542, -1.5371385, -0.4985314},
          {-0.9692660, 1.8760108, 0.0415560},
          {0.0556434, -0.2040259, 1.0572252} // Reference white - D65
      }};

  std::array<float, channelCount> mValues; // x, y, z

public:
  Xyz(float x, float y, float z);

  float x() const { return mValues[0]; }
  float y() const { return mValues[1]; }
  float z() const { return mValues[2]; }
  std::array<float, channelCount> getValues() const { return mValues; }

  LinearRgb toLinearRgb() const;
  Lab toLab() const;

  void print() const;
};


class Lab {
public:
  static constexpr size_t channelCount = 3;

private:
  std::array<float, channelCount> mValues; // l, a, b

public:
  Lab(float l, float a, float b);

  std::array<float, channelCount> getValues() const { return mValues; }

  Xyz toXyz() const;
  Lch toLch() const;

  void print() const;
};


class Lch {
public:
  static constexpr size_t channelCount = 3;

private:
  std::array<float, channelCount> mValues; // l, c, h

public:
  Lch(float l, float c, float h);

  std::array<float, channelCount> getValues() const { return mValues; }

  void print() const;
};


class Luv {
public:
  static constexpr size_t channelCount = 3;

private:
  std::array<float, channelCount> mValues; // l, c, h

public:
  Luv(float l, float u, float v);

  std::array<float, channelCount> getValues() const { return mValues; }

  void print() const;
};


} // namespace ColorSpace

#endif

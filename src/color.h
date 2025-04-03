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
  // Constructors
  Srgb(int r, int g, int b);

  // Accessors
  std::array<int, channelCount> getValues() const { return mValues; }

  // Conversions
  LinearRgb toLinearRgb() const;

  // Utilities
  void print() const;

private:
  // Helper Functions
  static float removeGamma(int c);
};


class LinearRgb {
private:
  static constexpr size_t channelCount = 3;
  std::array<float, channelCount> mValues; // r, g, b

public:
  // Constructors
  LinearRgb(float r, float g, float b);

  // Accessors
  std::array<float, channelCount> getValues() const { return mValues; }

  // Conversions
  Srgb toSrgb() const;
  CieXyz toCieXyz() const;

private:
  // Helper Functions
  static float applyGamma(int c);

  // Static Constants
  static constexpr std::array<std::array<float, channelCount>, channelCount>
      rgbToCieXyzMatrix = {{
          {0.4124564, 0.3575761, 0.1804375},
          {0.2126729, 0.7151522, 0.0721750},
          {0.0193339, 0.1191920, 0.9503041} // Reference white - D65
      }};
};


class CieXyz {
private:
  static constexpr size_t channelCount = 3;
  std::array<float, channelCount> mValues; // x, y, z

public:
  // Constructors
  CieXyz(float x, float y, float z);

  // Accessors
  float x() const { return mValues[0]; }
  float y() const { return mValues[1]; }
  float z() const { return mValues[2]; }
  std::array<float, channelCount> getValues() const { return mValues; }

  // Conversions
  LinearRgb toLinearRgb() const;
  CieLab toCieLab() const;

  // Utilities
  void print() const;

private:
  // Static Constants
  static constexpr std::array<std::array<float, channelCount>, channelCount>
      xyzToLinearRgbMatrix = {{
          {3.2404542, -1.5371385, -0.4985314},
          {-0.9692660, 1.8760108, 0.0415560},
          {0.0556434, -0.2040259, 1.0572252} // Reference white - D65
      }};
};


class CieLab {
private:
  static constexpr size_t channelCount = 3;
  std::array<float, channelCount> mValues; // l, a, b

public:
  // Constructors
  CieLab(float l, float a, float b);

  // Accessors
  std::array<float, channelCount> getValues() const { return mValues; }

  // Constants
  static constexpr float epsilon = 216.0f / 24389.0f;
  static constexpr float kappa = 24389.0f / 27.0f;

  // Conversions
  CieXyz toCieXyz() const;

  // Distance Metrics (future implementations)
  // float distCIE76(const CieLab &other);
  // float distCIEDE2000(const CieLab &other);
  // float distCIE94(const CieLab &other);

  // Utilities
  void print() const;
};

} // namespace ColorSpace

#endif

// float distEuclideanSquared(const CieLch &other);
// float distEuclidean(const CieLch &other);
// float distCIE76(const CieLch &other);
// float distCIEDE2000(const CieLch &other);
// float distCIE94(const CieLch &other);

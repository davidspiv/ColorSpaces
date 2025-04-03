#ifndef COLOR_H
#define COLOR_H

#include <array>
#include <iostream>

namespace ColorSpace {


class Lab;
class LchAb;
class LchUv;
class Luv;
class Rgb;
class SRgb;
class Xyy;
class Xyz;


class Lab {
private:
  std::array<float, 3> mValues; // l, a, b

public:
  Lab(float l, float a, float b);

  std::array<float, 3> getValues() const { return mValues; }

  Xyz toXyz() const;
  LchAb toLchAb() const;

  void print() const;
};


class LchAb {
private:
  std::array<float, 3> mValues; // l, c, h

public:
  LchAb(float l, float c, float h);

  std::array<float, 3> getValues() const { return mValues; }

  void print() const;
};


class LchUv {
private:
  std::array<float, 3> mValues; // l, c, h

public:
  LchUv(float l, float c, float h);

  std::array<float, 3> getValues() const { return mValues; }

  void print() const;
};


class Luv {
private:
  std::array<float, 3> mValues; // l, c, h

public:
  Luv(float l, float u, float v);

  std::array<float, 3> getValues() const { return mValues; }

  LchUv toLchUv() const;

  void print() const;
};


class Rgb {
private:
  static constexpr std::array<std::array<float, 3>, 3>
      rgbToXyzMatrix = {{
          {0.4124564, 0.3575761, 0.1804375},
          {0.2126729, 0.7151522, 0.0721750},
          {0.0193339, 0.1191920, 0.9503041} // Reference white - D65
      }};

  std::array<float, 3> mValues; // r, g, b

public:
  Rgb(float r, float g, float b);

  std::array<float, 3> getValues() const { return mValues; }

  SRgb toSRgb() const;
  Xyz toXyz() const;

  void print() const;

private:
  static float applyGamma(float c);
};


class SRgb {

private:
  std::array<int, 3> mValues; // r, g, b

public:
  SRgb(int r, int g, int b);

  std::array<int, 3> getValues() const { return mValues; }

  Rgb toRgb() const;

  void print() const;

private:
  static float removeGamma(int c);
};


class Xyy {
private:
  std::array<float, 3> mValues; // x, y, Y

public:
  Xyy(float l, float u, float v);

  std::array<float, 3> getValues() const { return mValues; }

  void print() const;
};


class Xyz {
private:
  static constexpr std::array<std::array<float, 3>, 3>
      xyzToRgbMatrix = {{
          {3.2404542, -1.5371385, -0.4985314},
          {-0.9692660, 1.8760108, 0.0415560},
          {0.0556434, -0.2040259, 1.0572252} // Reference white - D65
      }};

  std::array<float, 3> mValues; // x, y, z

public:
  Xyz(float x, float y, float z);

  std::array<float, 3> getValues() const { return mValues; }

  Rgb toRgb() const;
  Lab toLab() const;
  Luv toLuv() const;
  Xyy toXyy() const;

  void print() const;
};


} // namespace ColorSpace

#endif

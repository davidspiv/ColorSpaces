#ifndef COLOR_H
#define COLOR_H

#include "Matrix.h"

#include <array>
#include <iostream>

namespace Color_Space {

enum Mode { GRAPHICS, TEXTILES };

class Lab;
class Lch_Ab;
class Lch_Uv;
class Luv;
class Rgb;
class S_Rgb;
class Xyy;
class Xyz;

class Color_Base {
protected:
  std::array<float, 3> m_values;

public:
  std::array<float, 3> get_values() const { return m_values; }

  Matrix to_column() const {
    return Matrix({{m_values[0]}, {m_values[1]}, {m_values[2]}});
  };
};


class Lab : public Color_Base {
public:
  Lab(float l, float a, float b);

  // Conversions
  Xyz to_xyz() const;
  Lch_Ab to_lch_ab() const;

  // Distance Metrics
  float diff_cie_76(const Lab &other) const;
  float diff_cie_94(const Lab &other, Mode mode = GRAPHICS) const;
  float diff_cie_2000(const Lab &other) const;

  void print() const;
};


class Lch_Ab : public Color_Base {
public:
  Lch_Ab(float l, float c, float h);

  void print() const;
};


class Lch_Uv : public Color_Base {
public:
  Lch_Uv(float l, float c, float h);

  void print() const;
};


class Luv : public Color_Base {
public:
  Luv(float l, float u, float v);

  // Conversions
  Lch_Uv to_lch_uv() const;

  void print() const;
};


class Rgb : public Color_Base {
public:
  Rgb(float r, float g, float b);

  // Conversions
  S_Rgb to_s_rgb() const;
  Xyz to_xyz() const;

  void print() const;

private:
  static float apply_gamma(float c);
};


class S_Rgb : public Color_Base {
public:
  S_Rgb(float r, float g, float b);

  // Conversions
  Rgb to_rgb() const;

  void print() const;

private:
  static float remove_gamma(int c);
};


class Xyy : public Color_Base {
public:
  Xyy(float l, float u, float v);

  void print() const;
};


class Xyz : public Color_Base {
public:
  Xyz(float x, float y, float z);

  // Conversions
  Rgb to_rgb() const;
  Lab to_lab() const;
  Luv to_luv() const;
  Xyy to_xyy() const;

  void print() const;
};


} // namespace Color_Space

#endif

#ifndef COLOR_H
#define COLOR_H

#include "Matrix.h"
#include "Profile.h"

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

namespace Color_Space {

enum Mode { GRAPHICS, TEXTILES };

class Lab;
class Lch_Ab;
class Lch_Uv;
class Luv;
class Rgb;
class Rgb;
class Xyy;
class Xyz;

class Color {
protected:
  std::array<float, 3> m_values;

public:
  std::array<float, 3> get_values() const { return m_values; }

  Matrix to_column() const {
    return Matrix({{m_values[0]}, {m_values[1]}, {m_values[2]}});
  };

protected:
  static constexpr float epsilon = 216.0f / 24389.0f;
  static constexpr float kappa = 24389.0f / 27.0f;
};


class Lab : public Color {
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


class Lch_Ab : public Color {
public:
  Lch_Ab(float l, float c, float h);

  void print() const;
};


class Lch_Uv : public Color {
public:
  Lch_Uv(float l, float c, float h);

  void print() const;
};


class Luv : public Color {
public:
  Luv(float l, float u, float v);

  // Conversions
  Lch_Uv to_lch_uv() const;

  void print() const;
};


class Rgb : public Color {
public:
  Rgb(float r, float g, float b);

  // Conversions
  Xyz to_xyz(const Profile &profile) const;
  Xyz to_xyz() const;

  void print() const;
};


class Xyy : public Color {
public:
  Xyy(float x, float y, float Y);

  void print() const;
};


class Xyz : public Color {
public:
  Xyz(float x, float y, float z);

  // Conversions
  Rgb to_rgb(const Profile &profile) const;
  Rgb to_rgb() const;
  Lab to_lab() const;
  Luv to_luv() const;
  Xyy to_xyy() const;

  Xyz adapt_to_white_point(const Xyz &src_illuminant,
                           const Xyz &dest_illuminant) const;

  void print() const;
};


} // namespace Color_Space

#endif

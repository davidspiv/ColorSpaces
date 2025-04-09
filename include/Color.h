#ifndef COLOR_H
#define COLOR_H

#include "Matrix.h"

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

namespace Color_Space {

enum Illuminant_Label { A, B, C, D50, D55, D65, D75, E, F2, F7, F11 };

enum Rgb_Working_Space {
  S_RGB,
  ADOBE_RGB_1998,
  APPLE_RGB,
  BEST_RGB,
  BETA_RGB,
  BRUCE_RGB,
  CIE_RGB,
  COLORMATCH_RGB,
  DON_RGB_4,
  ECI_RGB_V2,
  EKTA_SPACE_PS5,
  NTSC_RGB,
  PAL_SECAM_RGB,
  PROPHOTO_RGB,
  SMPTE_C_RGB,
  WIDE_GAMUT_RGB,
  NONE
};

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
  Illuminant_Label m_ref_white;

public:
  std::array<float, 3> get_values() const { return m_values; }

  Matrix to_column() const {
    return Matrix({{m_values[0]}, {m_values[1]}, {m_values[2]}});
  };

  bool operator==(const Color &other) const {
    auto [x, y, z] = m_values;
    auto [other_x, other_y, other_z] = other.get_values();

    return (x == other_x) && (y == other_y) && (z == other_z);
  }

  bool operator!=(const Color &other) const { return !(*this == other); }
};


class Lab : public Color {
public:
  Lab(float l, float a, float b, Illuminant_Label ref_white = D65);

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
  Lch_Ab(float l, float c, float h, Illuminant_Label ref_white = D65);

  void print() const;
};


class Lch_Uv : public Color {
public:
  Lch_Uv(float l, float c, float h, Illuminant_Label ref_white = D65);

  void print() const;
};


class Luv : public Color {
public:
  Luv(float l, float u, float v, Illuminant_Label ref_white = D65);

  // Conversions
  Lch_Uv to_lch_uv() const;

  void print() const;
};


class Rgb : public Color {
public:
  Rgb(float r, float g, float b, Illuminant_Label ref_white = D65);

  // Conversions
  Xyz to_xyz(const Rgb_Working_Space working_space = NONE) const;

  void print() const;
};


class Xyy : public Color {
public:
  Xyy(float x, float y, float Y, Illuminant_Label ref_white = D65);

  void print() const;
};


class Xyz : public Color {
public:
  Xyz(float x, float y, float z, Illuminant_Label ref_white = D65);

  // Conversions
  Rgb to_rgb(const Rgb_Working_Space working_space = NONE) const;
  Lab to_lab() const;
  Luv to_luv() const;
  Xyy to_xyy() const;

  Xyz adapt_to_white_point(const Illuminant_Label illuminant_label) const;

  void print() const;
};


} // namespace Color_Space

#endif

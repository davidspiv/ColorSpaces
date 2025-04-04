#ifndef COLOR_H
#define COLOR_H

#include <array>
#include <iostream>

namespace Color_Space {

enum Mode { GRAPHICS, TEXTILES };

class Lab;
class Lch_Ab;
class Lch_Uv;
class Luv;
class Rgb;
class Srgb;
class Xyy;
class Xyz;


class Lab {
private:
  std::array<float, 3> m_values; // l, a, b

public:
  Lab(float l, float a, float b);

  std::array<float, 3> get_values() const { return m_values; }

  // Conversions
  Xyz to_xyz() const;
  Lch_Ab to_lch_ab() const;

  // Distance Metrics
  float diff_cie_76(const Lab &other) const;
  float diff_cie_94(const Lab &other, Mode mode = GRAPHICS) const;
  float diff_cie_2000(const Lab &other) const;

  void print() const;
};


class Lch_Ab {
private:
  std::array<float, 3> m_values; // l, c, h

public:
  Lch_Ab(float l, float c, float h);

  std::array<float, 3> get_values() const { return m_values; }

  void print() const;
};


class Lch_Uv {
private:
  std::array<float, 3> m_values; // l, c, h

public:
  Lch_Uv(float l, float c, float h);

  std::array<float, 3> get_values() const { return m_values; }

  void print() const;
};


class Luv {
private:
  std::array<float, 3> m_values; // l, c, h

public:
  Luv(float l, float u, float v);

  std::array<float, 3> get_values() const { return m_values; }

  // Conversions
  Lch_Uv to_lch_uv() const;

  void print() const;
};


class Rgb {
private:
  static constexpr std::array<std::array<float, 3>, 3> rgbTo_xyzMatrix = {{
      {0.4124564, 0.3575761, 0.1804375},
      {0.2126729, 0.7151522, 0.0721750},
      {0.0193339, 0.1191920, 0.9503041} // Reference white - D65
  }};

  std::array<float, 3> m_values; // r, g, b

public:
  Rgb(float r, float g, float b);

  std::array<float, 3> get_values() const { return m_values; }

  // Conversions
  Srgb to_srgb() const;
  Xyz to_xyz() const;

  void print() const;

private:
  static float apply_gamma(float c);
};


class Srgb {

private:
  std::array<int, 3> m_values; // r, g, b

public:
  Srgb(int r, int g, int b);

  std::array<int, 3> get_values() const { return m_values; }

  // Conversions
  Rgb to_rgb() const;

  void print() const;

private:
  static float remove_gamma(int c);
};


class Xyy {
private:
  std::array<float, 3> m_values; // x, y, Y

public:
  Xyy(float l, float u, float v);

  std::array<float, 3> get_values() const { return m_values; }

  void print() const;
};


class Xyz {
private:
  static constexpr std::array<std::array<float, 3>, 3> xyzTo_rgbMatrix = {{
      {3.2404542, -1.5371385, -0.4985314},
      {-0.9692660, 1.8760108, 0.0415560},
      {0.0556434, -0.2040259, 1.0572252} // Reference white - D65
  }};

  std::array<float, 3> m_values; // x, y, z

public:
  Xyz(float x, float y, float z);

  std::array<float, 3> get_values() const { return m_values; }

  // Conversions
  Rgb to_rgb() const;
  Lab to_lab() const;
  Luv to_luv() const;
  Xyy to_xyy() const;

  void print() const;
};


} // namespace Color_Space

#endif

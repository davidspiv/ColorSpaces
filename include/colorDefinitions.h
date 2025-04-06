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

#ifndef COLOR_H
#define COLOR_H

#include "Matrix.h"

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

namespace Color_Space {

class Lab;
class Lch_Ab;
class Lch_Uv;
class Luv;
class Rgb;
class Rgb;
class Xyy;
class Xyz;

enum Illuminant_Label {
  A,
  B,
  C,
  D50,
  D55,
  D65,
  D75,
  E,
  F2,
  F7,
  F11
  /// CIE standard illuminants
};

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
  PRO_PHOTO_RGB,
  SMPTE_C_RGB,
  WIDE_GAMUT_RGB,
  UNSPECIFIED
  /// RGB color spaces
};

class Color {
protected:
  std::array<float, 3> m_values;
  Illuminant_Label m_illuminant;

public:
  /**
   * @brief Returns the color's internal channel values.
   * @return Array containing 3 float components
   */
  [[nodiscard]] std::array<float, 3> get_values() const;

  /**
   * @brief Returns the color as a 3x1 column matrix representation.
   * @return Matrix with column form of color values.
   */
  [[nodiscard]] Matrix to_column() const;

  [[nodiscard]] bool operator==(const Color &other) const;
  [[nodiscard]] bool operator!=(const Color &other) const;
};


class Lab : public Color {
public:
  /**
   * @brief Constructs a Lab color.
   * @param l Lightness (0–100)
   * @param a Green–Red component
   * @param b Blue–Yellow component
   * @param illuminant Cie illuminant (default D50)
   */
  Lab(float l, float a, float b, Illuminant_Label illuminant = D50);

  /**
   * @brief Converts Lab to XYZ color space.
   * @return Xyz object representing this Lab color.
   */
  Xyz to_xyz() const;

  /**
   * @brief Converts Lab to cylindrical Lch(ab) format.
   * @return Lch_Ab representation
   */
  Lch_Ab to_lch_ab() const;

  /**
   * @brief Approximates color difference between the two colors, using the
   * CIE76 formula (basic Euclidean distance).
   * @param other Lab color to compute with.
   * @return perceptual distance (ΔE*)
   */
  [[nodiscard]] float diff_cie_76(const Lab &other) const;

  /**
   * @brief Approximates color difference between the two colors, using the
   * CIE94 formula.
   * @param other Lab color to compute with.
   * @param mode Application mode (GRAPHICS or TEXTILES)
   * @return perceptual distance (ΔE*).
   */
  [[nodiscard]] float diff_cie_94(const Lab &other,
                                  bool mode_graphics = true) const;

  /**
   * @brief Approximates color difference between the two colors, using the
   * CIEDE2000 formula.
   * @param other Lab color to compute with.
   * @return perceptual distance (ΔE*).
   */
  [[nodiscard]] float diff_cie_2000(const Lab &other) const;

  /**
   * @brief Prints Lab components to the console.
   */
  void print() const;
};


class Lch_Ab : public Color {
public:
  /**
   * @brief Constructs an Lch(ab) color (cylindrical Lab).
   * @param l Lightness
   * @param c Chroma
   * @param h Hue angle [degrees]
   * @param illuminant Cie illuminant (default D50)
   */
  Lch_Ab(float l, float c, float h, Illuminant_Label illuminant = D50);

  /**
   * @brief Prints Lch(ab) components to the console.
   */
  void print() const;
};


class Lch_Uv : public Color {
public:
  /**
   * @brief Constructs an Lch(uv) color (cylindrical Luv).
   * @param l Lightness
   * @param c Chroma
   * @param h Hue angle (in degrees)
   * @param illuminant Cie illuminant (default D50).
   */
  Lch_Uv(float l, float c, float h, Illuminant_Label illuminant = D50);

  /**
   * @brief Prints Lch(uv) components to the console.
   */
  void print() const;
};


class Luv : public Color {
public:
  /**
   * @brief Constructs a Luv color.
   * @param l Lightness
   * @param u Chromaticity U
   * @param v Chromaticity V
   * @param illuminant Cie illuminant (default D50)
   */
  Luv(float l, float u, float v, Illuminant_Label illuminant = D50);

  /**
   * @brief Converts Luv to cylindrical Lch(uv) representation.
   * @return Lch_Uv object.
   */
  [[nodiscard]] Lch_Uv to_lch_uv() const;

  /**
   * @brief Prints Luv components to the console.
   */
  void print() const;
};


class Rgb : public Color {
public:
  /**
   * @brief Constructs an RGB color.
   * @param r Red channel
   * @param g Green channel
   * @param b Blue channel
   * @param illuminant Cie illuminant (default D50)
   */
  Rgb(float r, float g, float b, Illuminant_Label illuminant = D50);

  /**
   * @brief Converts RGB to XYZ color space.
   * @param working_space The RGB color space (sRGB, Adobe RGB, etc.)
   * @return Xyz object representing this RGB color.
   */
  [[nodiscard]] Xyz
  to_xyz(const Rgb_Working_Space working_space = UNSPECIFIED) const;

  /**
   * @brief Prints RGB components to the console.
   */
  void print() const;
};


class Xyy : public Color {
public:
  /**
   * @brief Constructs an xyY color.
   * @param x Chromaticity x
   * @param y Chromaticity y
   * @param Y Luminance
   * @param illuminant Cie illuminant (default D50)
   */
  Xyy(float x, float y, float Y, Illuminant_Label illuminant = D50);

  /**
   * @brief Prints xyY components to the console.
   */
  void print() const;
};


class Xyz : public Color {
public:
  /**
   * @brief Constructs an XYZ color.
   * @param x X component
   * @param y Y component (luminance)
   * @param z Z component
   * @param illuminant Cie illuminant (default D50)
   */
  Xyz(float x, float y, float z, Illuminant_Label illuminant = D50);

  /**
   * @brief Converts XYZ to RGB.
   * @param working_space RGB color space to use for conversion.
   * @return RGB color.
   */
  [[nodiscard]] Rgb
  to_rgb(const Rgb_Working_Space working_space = UNSPECIFIED) const;

  /**
   * @brief Converts XYZ to Lab.
   * @return Lab representation of this color.
   */
  [[nodiscard]] Lab to_lab() const;

  /**
   * @brief Converts XYZ to Luv.
   * @return Luv representation.
   */
  [[nodiscard]] Luv to_luv() const;

  /**
   * @brief Converts XYZ to xyY chromaticity space.
   * @return Xyy object.
   */
  [[nodiscard]] Xyy to_xyy() const;

  /**
   * @brief Performs chromatic adaptation to a different illuminant.
   * @param illuminant_label New reference white point.
   * @return Adapted XYZ color.
   */
  [[nodiscard]] Xyz
  adapt_to_white_point(const Illuminant_Label illuminant_label) const;

  /**
   * @brief Prints XYZ components to the console.
   */
  void print() const;
};


} // namespace Color_Space

#endif

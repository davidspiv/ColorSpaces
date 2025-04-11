#ifndef COLOR_H
#define COLOR_H

#include "Matrix.h"

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

namespace Color_Space {


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
  /// RGB color spaces
};


enum Gamma {
  SRGB,
  SIMPLE_22,
  SIMPLE_18,
  L_STAR
  // determines which function to use when gamma encoding/decoding
};


enum CIE94_Mode {
  GRAPHICS,
  TEXTILE
  // determines weighted parameters in CIE94 color difference calculation
};


// forward declarations
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
  Illuminant_Label m_illuminant;

public:
  Color(float x, float y, float z, Illuminant_Label illuminant = D65) {
    m_values = {x, y, z};
    m_illuminant = illuminant;
  }


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
  virtual void print() const {
    std::cout << "[GEN]" << "\nC1: " << m_values[0] << "\nC2: " << m_values[1]
              << "\nC3: " << m_values[2] << "\n\n";
  }

  [[nodiscard]] bool operator==(const Color &other) const;
  [[nodiscard]] bool operator!=(const Color &other) const;
};


class Lab : public Color {
public:
  /**
   * @brief Constructs a Lab color.
   * @param l Lightness (L*)
   * @param a Green–Red component (a*)
   * @param b Blue–Yellow component (b*)
   * @param illuminant Cie illuminant (default D65)
   */
  Lab(float l, float a, float b, Illuminant_Label illuminant = D65);

  /**
   * @brief Converts Lab to XYZ color space.
   * @return the converted color as a Xyz object
   */
  Xyz to_xyz() const;

  /**
   * @brief Converts Lab to cylindrical Lch(ab) format.
   * @return the converted color as a Lch_Ab object
   */
  Lch_Ab to_lch_ab() const;

  /**
   * @brief Approximates color difference between the two colors, using the
   * CIE76 formula (basic Euclidean distance).
   * @param other Lab color to compute with.
   * @return perceptual distance as defined by the CIE (ΔE*)
   */
  [[nodiscard]] float diff_cie_76(const Lab &other) const;

  /**
   * @brief Approximates color difference between the two colors, using the
   * CIE94 formula.
   * @param other Lab color to compute with.
   * @param mode Application mode (GRAPHICS or TEXTILES)
   * @return perceptual distance as defined by the CIE (ΔE*)
   */
  [[nodiscard]] float diff_cie_94(const Lab &other,
                                  CIE94_Mode mode = GRAPHICS) const;

  /**
   * @brief Approximates color difference between the two colors, using the
   * CIEDE2000 formula.
   * @param other Lab color to compute with.
   * @return perceptual distance as defined by the CIE (ΔE*)
   */
  [[nodiscard]] float diff_cie_2000(const Lab &other) const;

  /**
   * @brief Prints Lab components to the console.
   */
  void print() const override;
};


class Lch_Ab : public Color {
public:
  /**
   * @brief Constructs an Lch(ab) color (cylindrical Lab).
   * @param l Lightness
   * @param c Chroma
   * @param h Hue angle [degrees]
   * @param illuminant Cie illuminant (default D65)
   */
  Lch_Ab(float l, float c, float h, Illuminant_Label illuminant = D65);

  /**
   * @brief Prints Lch(ab) components to the console.
   */
  void print() const override;
};


class Luv : public Color {
public:
  /**
   * @brief Constructs a Luv color.
   * @param l Lightness
   * @param u Chromaticity U
   * @param v Chromaticity V
   * @param illuminant Cie illuminant (default D65)
   */
  Luv(float l, float u, float v, Illuminant_Label illuminant = D65);

  /**
   * @brief Converts Luv to cylindrical Lch(uv) representation.
   * @return The converted color as a Lch_Uv object
   */
  [[nodiscard]] Lch_Uv to_lch_uv() const;

  /**
   * @brief Prints Luv components to the console.
   */
  void print() const override;
};


class Lch_Uv : public Color {
public:
  /**
   * @brief Constructs an Lch(uv) color (cylindrical Luv).
   * @param l Lightness
   * @param c Chroma
   * @param h Hue angle (in degrees)
   * @param illuminant Cie illuminant (default D65).
   */
  Lch_Uv(float l, float c, float h, Illuminant_Label illuminant = D65);

  /**
   * @brief Prints Lch(uv) components to the console.
   */
  void print() const override;
};


class Rgb : public Color {
public:
  /**
   * @brief Constructs an RGB color.
   * @param r Red channel
   * @param g Green channel
   * @param b Blue channel
   * @param illuminant Cie illuminant (default D65)
   */
  Rgb(float r, float g, float b, Illuminant_Label illuminant = D65);

  /**
   * @brief Converts RGB to XYZ color space.
   * @param working_space The RGB color space (sRGB, Adobe RGB, etc.)
   * @return the converted color as a Xyz object
   */
  [[nodiscard]] Xyz to_xyz(const Rgb_Working_Space working_space = S_RGB) const;

  /**
   * @brief Prints RGB components to the console.
   */
  void print() const override;
};


class Xyy : public Color {
public:
  /**
   * @brief Constructs an xyY color.
   * @param x Chromaticity x
   * @param y Chromaticity y
   * @param Y Luminance
   * @param illuminant Cie illuminant (default D65)
   */
  Xyy(float x, float y, float Y, Illuminant_Label illuminant = D65);

  /**
   * @brief Prints xyY components to the console.
   */
  void print() const override;
};


class Xyz : public Color {
public:
  /**
   * @brief Constructs an XYZ color.
   * @param X a mix of the three CIE RGB curves chosen to be nonnegative (X)
   * @param Y luminance (Y)
   * @param Z quasi-equal to the "blue" monochromatic primary (Z)
   * @param illuminant Cie illuminant (default D65)
   */
  Xyz(float X, float Y, float Z, Illuminant_Label illuminant = D65);

  /**
   * @brief Converts XYZ to RGB.
   * @param working_space RGB color space to use for conversion.
   * @return RGB color.
   */
  [[nodiscard]] Rgb to_rgb(const Rgb_Working_Space working_space = S_RGB) const;

  /**
   * @brief Converts XYZ to Lab.
   * @return the converted color as a Lab object
   */
  [[nodiscard]] Lab to_lab() const;

  /**
   * @brief Converts XYZ to Luv.
   * @return the converted color as a Luv object
   */
  [[nodiscard]] Luv to_luv() const;

  /**
   * @brief Converts XYZ to xyY chromaticity space.
   * @return the converted color as a Xyy object
   */
  [[nodiscard]] Xyy to_xyy() const;

  /**
   * @brief Performs chromatic adaptation to a different illuminant.
   * @param illuminant_label New reference white point
   * @return Adapted color as a Xyz object
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

# ColorSpaces
**ColorSpaces** is a lightweight C++ color science library for converting between color spaces, computing perceptual differences, and performing chromatic adaptation.

## Dependencies
- **Make**
- **C++17** or higher


## Installation
* Use `make` command to build library, all binaries will be in be in newly created build directory.
* Use `make run` to run tests.

## Features
- Conversion between color spaces:
  - sRGB
  - Adobe RGB 1998
  - Apple RGB
  - Best RGB
  - Beta RGB
  - Bruce RGB
  - Cie RGB
  - Colormatch RGB
  - Don RGB 4
  - eciRGB v2
  - Ekta Space PS 5
  - NTSC RGB
  - Pal Secam RGB
  - ProPhoto RGB
  - Smpte-C RGB
  - Wide Gamut RGB
  - CIE Lab
  - CIE LCh(ab)
  - CIE LUV
  - CIE LCh(uv)
  - CIE XYZ (1931)
  - CIE xyY

- Perceptual color difference formulas:
  - CIE76
  - CIE94 (Graphics and Textiles)
  - CIEDE2000

- Chromatic adaptation between white points:
  - A, B, C, D50, D55, D65, D75, E, F2, F7, F11

## Example Usage
```cpp
// specify a named RGB color space when converting both to and from RGB
Color_Space::Rgb rgb(30, 99, 15);
Color_Space::Xyz xyz = rgb.to_xyz(Color_Space::SMPTE_C_RGB)
							.adapt_to_white_point(Color_Space::D75);
Color_Space::Lab lab = xyz.to_lab();

// alternatively, when declaring a color you can specify the referenced illuminant as the fourth  argument
Color_Space::Lab other_lab(53.2f, 15.0f, -40.0f, Color_Space::D75);

float deltaE = lab.diff_cie_2000(other_lab);
```

## References
* [Bruce Lindbloom's Color Science](<http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html>)

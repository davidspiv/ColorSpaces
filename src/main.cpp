#include <iomanip>
#include <iostream>

#include "../include/colorDefinitions.h"
#include "../include/timer.h"
#include "../include/util.h"

int main() {
  Timer timer;

  //   const ColorSpace::SRgb sRgb(77, 3, 155);
  //   const ColorSpace::Rgb rgb = sRgb.toRgb();
  //   const ColorSpace::Xyz xyz = rgb.toXyz();
  //   const ColorSpace::Lab lab = xyz.toLab();

  const ColorSpace::Lab a_lab(87.8823, -84.6508, 80.0226);
  const ColorSpace::Lab b_lab(23.7018, 56.835, -63.5484);

  const ColorSpace::LchAb a_lch = a_lab.toLchAb();
  const ColorSpace::LchAb b_lch = b_lab.toLchAb();

  std::cout << setw(20) << "CIE 1976: " << a_lab.diffCie76(b_lab) << '\n';
  std::cout << setw(20)
            << "CIE 1994 (g): " << a_lch.diffCie94(b_lch, ColorSpace::GRAPHICS)
            << '\n';
  std::cout << setw(20) << "CIE 1994 (t): " << a_lch.diffCie94(b_lch) << '\n';
  std::cout << setw(20) << "CIE 2000: " << a_lab.diffCiede2000(b_lab) << '\n';
}

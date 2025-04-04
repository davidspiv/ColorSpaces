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

  ColorSpace::Lab a_lab = {87.8823f, -84.6508f, 80.0226f};
  ColorSpace::Lab b_lab = {23.7018f, 56.8350f, -63.5484f};

  std::cout << setw(20) << "CIE 1976: " << a_lab.diffCie76(b_lab) << '\n';
  std::cout << setw(20) << "CIE 1994 (g): " << a_lab.diffCie94(b_lab) << '\n';
  std::cout << setw(20)
            << "CIE 1994 (t): " << a_lab.diffCie94(b_lab, ColorSpace::TEXTILES)
            << '\n';
  std::cout << setw(20) << "CIE 2000: " << a_lab.diffCiede2000(b_lab) << '\n';
}

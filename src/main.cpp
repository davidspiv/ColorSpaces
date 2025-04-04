#include <iomanip>
#include <iostream>

#include "../include/colorDefinitions.h"
#include "../include/timer.h"
#include "../include/util.h"

int main() {
  Timer timer;

  //   const Color_Space::SRgb sRgb(77, 3, 155);
  //   const Color_Space::Rgb rgb = sRgb.toRgb();
  //   const Color_Space::Xyz xyz = rgb.toXyz();
  //   const Color_Space::Lab lab = xyz.toLab();

  Color_Space::Lab a_lab = {87.8823f, -84.6508f, 80.0226f};
  Color_Space::Lab b_lab = {23.7018f, 56.8350f, -63.5484f};

  std::cout << setw(20) << "CIE 1976: " << a_lab.diff_cie_76(b_lab) << '\n';
  std::cout << setw(20) << "CIE 1994 (g): " << a_lab.diff_cie_94(b_lab) << '\n';
  std::cout << setw(20) << "CIE 1994 (t): "
            << a_lab.diff_cie_94(b_lab, Color_Space::TEXTILES) << '\n';
  std::cout << setw(20) << "CIE 2000: " << a_lab.diff_cie_2000(b_lab) << '\n';
}

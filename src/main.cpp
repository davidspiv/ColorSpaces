#include "color.h"
#include "util.h"

#include <cmath>
#include <iostream>

#include "timer.h"

int main() {
  Timer timer;

  ColorSpace::StdRGB startRGB(100, 0, 0);
  const ColorSpace::CieLab lab(startRGB);

  std::cout << "lStar: " << lab.lStar << ", aStar: " << lab.aStar
            << ", bStar: " << lab.bStar << std::endl;
}

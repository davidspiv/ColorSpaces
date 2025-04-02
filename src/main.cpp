
#include <cmath>
#include <iostream>

#include "color.h"
#include "timer.h"
#include "util.h"

int main() {
  Timer timer;

  const ColorSpace::StdRgb startRgb(100, 0, 0);
  const ColorSpace::CieLab cieLab = startRgb.toCieLab();

  std::cout << "lStar: " << cieLab.lStar << ", aStar: " << cieLab.aStar
            << ", bStar: " << cieLab.bStar << std::endl;
}

#include "../include/color.h"
#include "../include/util.h"

#include <cmath>
#include <iostream>

#include "../include/timer.h"

int main() {
  Timer timer;

  StdRGB startRGB(100, 0, 0);
  const CieLab lab(startRGB);

  std::cout << "lStar: " << lab.lStar << ", aStar: " << lab.aStar
            << ", bStar: " << lab.bStar << std::endl;
}


#include <cmath>
#include <iostream>

#include "color.h"
#include "timer.h"
#include "util.h"

int main() {
  Timer timer;

  const ColorSpace::Srgb startRgb(100, 0, 0);
  const ColorSpace::CieLab cieLab = startRgb.toCieLab();

  std::cout << "l*: " << cieLab.l << ", a*: " << cieLab.a
            << ", b*: " << cieLab.b << std::endl;
}


#include <cmath>
#include <iostream>

#include "color.h"
#include "timer.h"
#include "util.h"

int main() {
  Timer timer;

  const ColorSpace::Srgb sRgbA(100, 0, 0);
  const ColorSpace::LinearRgb linearRgbA = sRgbA.toLinearRgb();
  const ColorSpace::CieLab cieLabA = sRgbA.toCieLab();

  const ColorSpace::Srgb sRgbB(0, 201, 0);
  const ColorSpace::LinearRgb linearRgbB = sRgbB.toLinearRgb();
  const ColorSpace::CieLab cieLabB = sRgbB.toCieLab();

  const int distRgb = distSquared(sRgbA, sRgbB);
  const float distLinear = distSquared(linearRgbA, linearRgbB);
  const float distLab = distSquared(cieLabA, cieLabB);

  std::cout << "srgb: " << distRgb << '\n';
  std::cout << "linear: " << distLinear << '\n';
  std::cout << "lab: " << distLab << '\n';
}
 
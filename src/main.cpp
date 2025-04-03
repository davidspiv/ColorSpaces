
#include <cmath>
#include <iostream>

#include "color.h"
#include "timer.h"
#include "util.h"

int main() {
  Timer timer;

  const ColorSpace::Srgb sRgbA(100, 0, 0);
  const ColorSpace::LinearRgb linearRgbA = sRgbA.toLinearRgb();
  const ColorSpace::CieXyz cieXyzA = linearRgbA.toCieXyz();
  const ColorSpace::CieLab cieLabA = cieXyzA.toCieLab();

  const ColorSpace::Srgb sRgbB(0, 201, 0);
  const ColorSpace::LinearRgb linearRgbB = sRgbB.toLinearRgb();
  const ColorSpace::CieXyz cieXyzB = linearRgbB.toCieXyz();
  const ColorSpace::CieLab cieLabB = cieXyzB.toCieLab();

  //   const float distLinear = distEuclideanSquared(linearRgbA, linearRgbB);
  //   const float distXyz = distEuclideanSquared(cieXyzA, cieXyzB);
  //   const float distLab = distEuclideanSquared(cieLabA, cieLabB);

  const float distLinear = distEuclidean(linearRgbA, linearRgbB);
  const float distXyz = distEuclidean(cieXyzA, cieXyzB);
  const float distLab = distEuclidean(cieLabA, cieLabB);

  std::cout << "linear: " << distLinear << '\n';
  std::cout << "xyz: " << distXyz << '\n';
  std::cout << "lab: " << distLab << '\n';
}

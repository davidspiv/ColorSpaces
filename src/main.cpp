
#include <cmath>
#include <iostream>

#include "color.h"
#include "timer.h"
#include "util.h"

int main() {
  Timer timer;

  const ColorSpace::Srgb sRgb_A(30, 0, 0);
  const ColorSpace::LinearRgb linearRgb_A = sRgb_A.toLinearRgb();
  const ColorSpace::CieXyz cieXy_A = linearRgb_A.toCieXyz();
  const ColorSpace::CieLab cieLab_A = cieXy_A.toCieLab();

  //   cieLab_A.print();

  const ColorSpace::Srgb sRgb_B(0, 201, 0);
  const ColorSpace::LinearRgb linearRgb_B = sRgb_B.toLinearRgb();
  const ColorSpace::CieXyz cieXyz_B = linearRgb_B.toCieXyz();
  const ColorSpace::CieLab cieLab_B = cieXyz_B.toCieLab();

  //   const float distLinear = distEuclideanSquared(linearRgb_A, linearRgb_B);
  //   const float distXyz = distEuclideanSquared(cieXy_A, cieXyz_B);
  //   const float distLab = distEuclideanSquared(cieLab_A, cieLab_B);

  const float distLinear = distEuclidean(linearRgb_A, linearRgb_B);
  const float distXyz = distEuclidean(cieXy_A, cieXyz_B);
  const float distLab = distEuclidean(cieLab_A, cieLab_B);

  std::cout << "linear: " << distLinear << '\n';
  std::cout << "xyz: " << distXyz << '\n';
  std::cout << "lab: " << distLab << '\n';
}

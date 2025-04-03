
#include <cmath>
#include <iomanip>
#include <iostream>

#include "color.h"
#include "timer.h"
#include "util.h"

int main() {
  Timer timer;

  const ColorSpace::Srgb sRgb_A(113, 91, 255);
  const ColorSpace::LinearRgb linearRgb_A = sRgb_A.toLinearRgb();
  const ColorSpace::Xyz cieXy_A = linearRgb_A.toXyz();
  const ColorSpace::Lab lab_A = cieXy_A.toLab();
  const ColorSpace::Lch lch_A = lab_A.toLch();

  lch_A.print();

  const ColorSpace::Srgb sRgb_B(0, 201, 0);
  const ColorSpace::LinearRgb linearRgb_B = sRgb_B.toLinearRgb();
  const ColorSpace::Xyz xyz_B = linearRgb_B.toXyz();
  const ColorSpace::Lab lab_B = xyz_B.toLab();

  //   const float distLinear = distEuclideanSquared(linearRgb_A, linearRgb_B);
  //   const float distXyz = distEuclideanSquared(cieXy_A, xyz_B);
  //   const float distLab = distEuclideanSquared(lab_A, lab_B);

  const float distLinear = distEuclidean(linearRgb_A, linearRgb_B);
  const float distXyz = distEuclidean(cieXy_A, xyz_B);
  const float distLab = distEuclidean(lab_A, lab_B);

  std::cout << '\n'
            << setw(10) << "linear: " << distLinear << '\n'
            << setw(10) << "xyz: " << distXyz << '\n'
            << setw(10) << "lab: " << distLab << '\n'
            << std::endl;
}

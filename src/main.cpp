
#include <cmath>
#include <iostream>

#include "color.h"
#include "timer.h"
#include "util.h"

int main() {
  Timer timer;

  const ColorSpace::SRgb sRgb_A(113, 91, 255);
  const ColorSpace::Rgb rgb_A = sRgb_A.toRgb();
  const ColorSpace::Xyz cieXy_A = rgb_A.toXyz();
  const ColorSpace::Lab lab_A = cieXy_A.toLab();
  const ColorSpace::Lch lch_A = lab_A.toLch();

  lch_A.print();

  const ColorSpace::SRgb sRgb_B(0, 201, 0);
  const ColorSpace::Rgb rgb_B = sRgb_B.toRgb();
  const ColorSpace::Xyz xyz_B = rgb_B.toXyz();
  const ColorSpace::Lab lab_B = xyz_B.toLab();

  //   const float distRgb = distEuclideanSquared(rgb_A, rgb_B);
  //   const float distXyz = distEuclideanSquared(cieXy_A, xyz_B);
  //   const float distLab = distEuclideanSquared(lab_A, lab_B);

  const float distRgb = distEuclidean(rgb_A, rgb_B);
  const float distXyz = distEuclidean(cieXy_A, xyz_B);
  const float distLab = distEuclidean(lab_A, lab_B);

  std::cout << '\n'
            << "rgb: " << distRgb << '\n'
            << "xyz: " << distXyz << '\n'
            << "lab: " << distLab << '\n'
            << std::endl;
}

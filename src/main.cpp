
#include <cmath>
#include <iostream>

#include "color.h"
#include "timer.h"
#include "util.h"

int main() {
  Timer timer;

  const ColorSpace::SRgb a_sRgb(113, 91, 255);
  const ColorSpace::Rgb a_rgb = a_sRgb.toRgb();
  const ColorSpace::Xyz a_cieXy = a_rgb.toXyz();
  const ColorSpace::Lab a_lab = a_cieXy.toLab();
  const ColorSpace::LchAb a_lchAb = a_lab.toLchAb();

  a_lchAb.print();

  const ColorSpace::SRgb b_sRgb(0, 201, 0);
  const ColorSpace::Rgb b_rgb = b_sRgb.toRgb();
  const ColorSpace::Xyz b_xyz = b_rgb.toXyz();
  const ColorSpace::Lab b_lab = b_xyz.toLab();

  //   const float distRgb = distEuclideanSquared(a_rgb, b_rgb);
  //   const float distXyz = distEuclideanSquared(a_cieXy, b_xyz);
  //   const float distLab = distEuclideanSquared(a_lab, b_lab);

  const float distRgb = distEuclidean(a_rgb, b_rgb);
  const float distXyz = distEuclidean(a_cieXy, b_xyz);
  const float distLab = distEuclidean(a_lab, b_lab);

  std::cout << '\n'
            << "rgb: " << distRgb << '\n'
            << "xyz: " << distXyz << '\n'
            << "lab: " << distLab << '\n'
            << std::endl;
}

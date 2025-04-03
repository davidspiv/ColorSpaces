
#include <cmath>
#include <iostream>

#include "color.h"
#include "timer.h"
#include "util.h"

int main() {
  Timer timer;

  const ColorSpace::SRgb a_sRgb(255, 255, 255);
  const ColorSpace::Rgb a_rgb = a_sRgb.toRgb();
  const ColorSpace::Xyz a_xyz = a_rgb.toXyz();
  const ColorSpace::Lab a_lab = a_xyz.toLab();
  const ColorSpace::LchAb a_lchAb = a_lab.toLchAb();
  const ColorSpace::Luv a_luv = a_xyz.toLuv();
  const ColorSpace::LchUv a_lchUv = a_luv.toLchUv();
  const ColorSpace::Xyy a_xyy = a_xyz.toXyy();

  a_xyz.print();
  a_xyy.print();
  a_lab.print();
  a_lchAb.print();
  a_luv.print();
  a_lchUv.print();
  a_sRgb.print();

  //   const ColorSpace::SRgb b_sRgb(0, 201, 0);
  //   const ColorSpace::Rgb b_rgb = b_sRgb.toRgb();
  //   const ColorSpace::Xyz b_xyz = b_rgb.toXyz();
  //   const ColorSpace::Lab b_lab = b_xyz.toLab();

  //   //   const float distRgb = distEuclideanSquared(a_rgb, b_rgb);
  //   //   const float distXyz = distEuclideanSquared(a_cieXy, b_xyz);
  //   //   const float distLab = distEuclideanSquared(a_lab, b_lab);

  //   const float distRgb = distEuclidean(a_rgb, b_rgb);
  //   const float distXyz = distEuclidean(a_xyz, b_xyz);
  //   const float distLab = distEuclidean(a_lab, b_lab);

  //   std::cout << '\n'
  //             << "rgb: " << distRgb << '\n'
  //             << "xyz: " << distXyz << '\n'
  //             << "lab: " << distLab << '\n'
  //             << std::endl;
}

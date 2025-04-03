
#include <iostream>

#include "../include/colorDefinitions.h"
#include "../include/timer.h"
#include "../include/util.h"

int main() {
  Timer timer;

  const ColorSpace::SRgb sRgb(255, 255, 255);
  const ColorSpace::Rgb rgb = sRgb.toRgb();
  const ColorSpace::Xyz xyz = rgb.toXyz();
  const ColorSpace::Lab lab = xyz.toLab();
  const ColorSpace::LchAb lchAb = lab.toLchAb();
  const ColorSpace::Luv luv = xyz.toLuv();
  const ColorSpace::LchUv lchUv = luv.toLchUv();
  const ColorSpace::Xyy xyy = xyz.toXyy();

  xyz.print();
  xyy.print();
  lab.print();
  lchAb.print();
  luv.print();
  lchUv.print();
  sRgb.print();
}

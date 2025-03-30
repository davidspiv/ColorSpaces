#ifndef COLOR_H
#define COLOR_H

#include "../include/picture.h"
#include <stdexcept>

struct StdRGB {
  StdRGB(int r, int g, int b);
  int r, g, b;
};


struct LinRGB {
  LinRGB(double r, double g, double b);
  double r, g, b;
};


struct CieXYZ {
  CieXYZ(double x, double y, double z);
  double x, y, z;
};

struct CieLab {
  CieLab(double lStar, double aStar, double bStar);
  explicit CieLab(StdRGB stdRgb);
  double lStar, aStar, bStar;
};

LinRGB linearize(const StdRGB &stdRGB);
StdRGB applyGamma(const LinRGB &linRGB);
CieXYZ rgbToXYZ(const LinRGB &linRGB);
LinRGB xyzToRGB(const CieXYZ &cieXYZ);
CieLab xyzToLab(const CieXYZ &cieXYZ);

#endif

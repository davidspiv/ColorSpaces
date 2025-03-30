#ifndef COLOR_H
#define COLOR_H

#include "../include/picture.h"
#include <stdexcept>

struct StdRGB {
  StdRGB() : r(-1), g(-1), b(-1) {};
  StdRGB(int r, int g, int b) : r(r), g(g), b(b) {};
  int r, g, b;
};


struct LinRGB {
  LinRGB() : r(-1.0), g(-1.0), b(-1.0) {};
  LinRGB(double r, double g, double b) : r(r), g(g), b(b) {};
  double r, g, b;
};


struct CieXYZ {
  CieXYZ() : x(-1.0), y(-1.0), z(-1.0) {};
  CieXYZ(double x, double y, double z) : x(x), y(y), z(z) {};
  double x, y, z;
};

struct CieLab {
  CieLab() : lStar(-1.0), aStar(-129.0), bStar(-129.0) {};
  CieLab(double lStar, double aStar, double bStar)
      : lStar(lStar), aStar(aStar), bStar(bStar) {};
  double lStar, aStar, bStar;
};


// include automatic invalidation mechanism (overload '=' operator?)
// lazy computation of color space structs
class Color {

public:
  explicit Color(const StdRGB &stdRGB);
  explicit Color(const LinRGB &linRGB);
  explicit Color(const CieXYZ &cieXYZ);

  StdRGB sRGB();
  LinRGB linRGB();
  CieXYZ cieXYZ();
  CieLab cieLab();

private:
  StdRGB _sRGB;
  LinRGB _linRGB;
  CieXYZ _cieXYZ;
  CieLab _cieLab;

  LinRGB linearize(const StdRGB &stdRGB);
  StdRGB applyGamma(const LinRGB &linRGB);
  CieXYZ rgbToXYZ(const LinRGB &linRGB);
  LinRGB xyzToRGB(const CieXYZ &cieXYZ);
  CieLab xyzToLab(const CieXYZ &cieXYZ);
};

#endif

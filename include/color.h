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


struct CIELab {
  CIELab() : lStar(-1.0), aStar(-129.0), bStar(-129.0) {};
  CIELab(double lStar, double aStar, double bStar)
      : lStar(lStar), aStar(aStar), bStar(bStar) {};
  double lStar, aStar, bStar;
};

// include automatic invalidation mechanism (overload '=' operator?)
// lazy computation of color space structs
class Color {

public:
  explicit Color(const StdRGB &stdRGB);
  explicit Color(const LinRGB &linRGB);
  explicit Color(const CIELab &ceiLab);

  StdRGB sRGB();
  LinRGB linRGB();
  CIELab cieLab();

private:
  StdRGB _sRGB;
  LinRGB _linRGB;
  CIELab _cieLab;

  LinRGB linearize(const StdRGB &stdRGB);
  StdRGB applyGamma(const LinRGB &linRGB);
  CIELab rgbToCIE(const LinRGB &linRGB);
  LinRGB cieToRGB(const CIELab &ceiLab);
};

#endif

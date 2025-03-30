#ifndef COLOR_H
#define COLOR_H

#include "../include/picture.h"
#include <stdexcept>

struct Coord {
  double x;
  double y;
  double z;
};

struct StdRGB {
  StdRGB() : r(-1), g(-1), b(-1) {};
  StdRGB(int r, int g, int b);
  int r, g, b;
};


struct LinRGB {
  LinRGB() : r(-1.0), g(-1.0), b(-1.0) {};
  LinRGB(double r, double g, double b);
  double r, g, b;
};


struct CIELab {
  CIELab() : lStar(-1.0), aStar(-129.0), bStar(-129.0) {};
  CIELab(double lStar, double aStart, double bStar);
  double lStar, aStar, bStar;
};

// include automatic invalidation mechanism
// lazy computation of color space structs
class Color {

public:
  Color::Color(int r, int g, int b) : _sRGB({r, g, b}) {};
  Color::Color(double r, double g, double b, bool isLin)
      : _linRGB({r, g, b}) {};
  Color::Color(double lStar, double aStart, double bStar)
      : _cieLab({lStar, aStart, bStar}) {};

  Coord sRGB();
  Coord linRGB();
  Coord cieLab();

private:
  StdRGB _sRGB;
  LinRGB _linRGB;
  CIELab _cieLab;

  LinRGB linearize(const StdRGB &StdRGB);
  StdRGB applyGamma(const LinRGB &linearRGB);
  CIELab rgbToCIE(const LinRGB &linRGB);
  LinRGB cieToRGB(const CIELab &cieColor);
};

#endif

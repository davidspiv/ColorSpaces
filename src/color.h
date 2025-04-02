#ifndef COLOR_H
#define COLOR_H

namespace ColorSpace {

struct CieLab;
struct LinRgb;
struct CieXyz;

struct StdRgb {
  StdRgb(int r, int g, int b);
  int r, g, b;

  LinRgb toLinRgb() const;
  CieLab toCieLab() const;
};

struct LinRgb {
  LinRgb(double r, double g, double b);
  double r, g, b;

  StdRgb toStdRgb() const;
  CieXyz toXyz() const;
};

struct CieXyz {
  CieXyz(double x, double y, double z);
  double x, y, z;

  LinRgb toLinRgb() const;
  CieLab toCieLab() const;
};

struct CieLab {
  CieLab(double lStar, double aStar, double bStar);
  double lStar, aStar, bStar;

  CieXyz toXyz() const;
  StdRgb toStdRgb() const;
};

const CieXyz referenceWhiteD60(0.950470, 1.0, 1.088830);
constexpr double epsilon = 216.0 / 24389.0;
constexpr double kappa = 24389.0 / 27.0;

} // namespace ColorSpace

#endif

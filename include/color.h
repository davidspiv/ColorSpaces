#ifndef COLOR_H
#define COLOR_H

struct CieLab;

struct StdRGB {
  StdRGB(int r, int g, int b);
  explicit StdRGB(const CieLab &ceiLab);
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
  explicit CieLab(const StdRGB &stdRgb);
  double lStar, aStar, bStar;
};

const CieXYZ referenceWhiteD60(0.950470, 1.0, 1.088830);
constexpr double epsilon = 216.0 / 24389.0;
constexpr double kappa = 24389.0 / 27.0;

LinRGB linearize(const StdRGB &stdRGB);
StdRGB applyGamma(const LinRGB &linRGB);
CieXYZ rgbToXYZ(const LinRGB &linRGB);
LinRGB xyzToRGB(const CieXYZ &cieXYZ);
CieLab xyzToLab(const CieXYZ &cieXYZ);
CieXYZ labToXYZ(const CieLab &cieLab);

#endif

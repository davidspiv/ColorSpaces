#include "../include/color.h"
#include "../include/picture.h"
#include "../include/util.h"

#include <cmath>
#include <iostream>

int main() {
  StdRGB startRGB(83, 196, 197);
  StdRGB endRGB(235, 64, 60);

  Picture picture(100, 100);

  for (int i = 0; i < picture.width(); i++) {
    float t = i / float(picture.width() - 1);

    int r = int(round(startRGB.r * (1 - t) + endRGB.r * t));
    int g = int(round(startRGB.g * (1 - t) + endRGB.g * t));
    int b = int(round(startRGB.b * (1 - t) + endRGB.b * t));

    for (int j = 0; j < picture.height() / 2; j++) {
      picture.set(i, j, r, g, b, 255);
    }
  }

  CieLab startLab(startRGB);
  CieLab endLab(endRGB);

  for (int i = 0; i < picture.width(); i++) {
    float t = i / float(picture.width() - 1);

    double lStar = startLab.lStar * (1 - t) + endLab.lStar * t;
    double aStar = startLab.aStar * (1 - t) + endLab.aStar * t;
    double bStar = startLab.bStar * (1 - t) + endLab.bStar * t;

    for (int j = picture.height() / 2; j < picture.height(); j++) {
      CieLab newLab(lStar, aStar, bStar);
      auto [r, g, b] = StdRGB(newLab);
      picture.set(i, j, r, g, b, 255);
    }
  }

  picture.save("result.png");


  //   StdRGB startRGB(0, 0, 255);
  //   StdRGB endRGB(0, 255, 0);
  //   CieLab startLab(startRGB);
  //   CieLab endLab(endRGB);
}

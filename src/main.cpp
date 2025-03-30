#include "../include/color.h"
#include "../include/picture.h"

#include <iostream>

int main() {
  Color color(StdRGB(255, 30, 45));
  CieLab labColor = color.cieLab();

  std::cout << "L*: " << labColor.lStar << std::endl;
  std::cout << "a*: " << labColor.aStar << std::endl;
  std::cout << "b*: " << labColor.bStar << std::endl;
}

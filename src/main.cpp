#include "../include/color.h"
#include "../include/picture.h"

#include <iostream>

int main() {
  StdRGB orgRGB(22, 124, 56);
  CieLab labColor(orgRGB);

  std::cout << "L*: " << labColor.lStar << std::endl;
  std::cout << "a*: " << labColor.aStar << std::endl;
  std::cout << "b*: " << labColor.bStar << std::endl;

  StdRGB resRGB(labColor);

  std::cout << "r: " << resRGB.r << std::endl;
  std::cout << "g: " << resRGB.g << std::endl;
  std::cout << "b: " << resRGB.b << std::endl;
}

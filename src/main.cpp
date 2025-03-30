#include "../include/color.h"
#include "../include/picture.h"

#include <iostream>

int main() {
  Color color(StdRGB(30, 30, 30));
  CieXYZ labColor = color.cieXYZ();

  std::cout << "X: " << labColor.x << std::endl;
  std::cout << "Y: " << labColor.y << std::endl;
  std::cout << "Z: " << labColor.z << std::endl;
}

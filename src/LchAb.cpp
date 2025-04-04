#include "../include/colorDefinitions.h"

#include <array>
#include <cmath>
#include <iostream>

namespace ColorSpace {


LchAb::LchAb(float l, float c, float h) : mValues({l, c, h}) {}


void LchAb::print() const {
  std::cout << "L: " << mValues[0] << "\nc: " << mValues[1]
            << "\nh: " << mValues[2] << "\n\n";
}


} // namespace ColorSpace

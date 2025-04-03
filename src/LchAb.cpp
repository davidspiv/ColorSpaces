#include "../include/colorDefinitions.h"

#include <array>
#include <iostream>

namespace ColorSpace {


LchUv::LchUv(float l, float c, float h) : mValues({l, c, h}) {}


void LchUv::print() const {
  std::cout << "L: " << mValues[0] << "\nc: " << mValues[1]
            << "\nh: " << mValues[2] << "\n\n";
}


} // namespace ColorSpace

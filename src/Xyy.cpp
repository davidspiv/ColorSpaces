#include "../include/util.h"

#include <iostream>

namespace ColorSpace {


Xyy::Xyy(float x, float y, float Y) : mValues({x, y, Y}) {}


void Xyy::print() const {
  std::cout << "x: " << mValues[0] << "\ny: " << mValues[1]
            << "\nY: " << mValues[2] << "\n\n";
}


} // namespace ColorSpace

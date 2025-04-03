#include "../include/colorDefinitions.h"
#include "../include/util.h"

#include <array>
#include <iostream>

namespace ColorSpace {


Luv::Luv(float l, float u, float v) : mValues({l, u, v}) {}


LchUv Luv::toLchUv() const {
  const auto [l, u, v] = toPolarColorSpace(mValues);

  return LchUv(l, u, v);
};


void Luv::print() const {
  std::cout << "L: " << mValues[0] << "\nu: " << mValues[1]
            << "\nv: " << mValues[2] << "\n\n";
}


} // namespace ColorSpace

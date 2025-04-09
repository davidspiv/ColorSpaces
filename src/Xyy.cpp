#include "../include/Color.h"

#include <iostream>

using namespace Color_Space;


Xyy::Xyy(float x, float y, float Y, Illuminant_Label ref_white) {
  m_values = {x, y, Y};
  this->m_ref_white = ref_white;
}


void Xyy::print() const {
  std::cout << "[xyY]" << "\nx: " << m_values[0] << "\ny: " << m_values[1]
            << "\nY: " << m_values[2] << "\n\n";
}

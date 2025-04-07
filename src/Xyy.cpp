#include "../include/util.h"

#include <iostream>

using namespace Color_Space;

Xyy::Xyy(float x, float y, float Y) : m_values({x, y, Y}) {}


void Xyy::print() const {
  std::cout << "x: " << m_values[0] << "\ny: " << m_values[1]
            << "\nY: " << m_values[2] << "\n\n";
}

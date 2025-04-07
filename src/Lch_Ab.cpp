#include "../include/Color.h"

#include <array>
#include <cmath>
#include <iostream>

using namespace Color_Space;


Lch_Ab::Lch_Ab(float l, float c, float h) : m_values({l, c, h}) {}


void Lch_Ab::print() const {
  std::cout << "L: " << m_values[0] << "\nc: " << m_values[1]
            << "\nh: " << m_values[2] << "\n\n";
}


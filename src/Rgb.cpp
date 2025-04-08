#include "../include/Color.h"
#include "../include/Matrix.h"
#include "../include/util.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <string>

using namespace Color_Space;


Rgb::Rgb(float r, float g, float b) {
  auto validate = [](float c) {
    if (std::min<float>(1.0, std::max<float>(0.0, c)) != c) {
      throw std::domain_error("Channel initalized outside of range [0, 1].");
    }
  };

  validate(r);
  validate(g);
  validate(b);

  m_values = {r, g, b};
};


void Rgb::print() const {
  std::cout << "R: " << m_values[0] << "\nG: " << m_values[1]
            << "\nB: " << m_values[2] << std::endl;
}

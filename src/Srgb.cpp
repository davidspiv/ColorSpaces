#include "../include/colorDefinitions.h"

#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace Color_Space {


Srgb::Srgb(int r, int g, int b) : m_values({r, g, b}) {
  auto validate = [](int c) {
    if (std::min(255, std::max(0, c)) != c) {
      throw std::domain_error("Channel initalized outside of range [0, 255].");
    }
  };

  validate(r);
  validate(g);
  validate(b);
};


float Srgb::remove_gamma(int c) {
  float normalChannel = static_cast<double>(c) / 255.0;

  const float breakpoint = 0.04045f;

  return (normalChannel <= breakpoint)
             ? (normalChannel / 12.92f)
             : std::pow((normalChannel + 0.055f) / 1.055f, 2.4f);
};


Rgb Srgb::to_rgb() const {
  const float r = this->remove_gamma(m_values[0]);
  const float g = this->remove_gamma(m_values[1]);
  const float b = this->remove_gamma(m_values[2]);

  return Rgb(r, g, b);
};


void Srgb::print() const {
  std::cout << "r: " << m_values[0] << "\ng: " << m_values[1]
            << "\nb: " << m_values[2] << std::endl;
}


} // namespace Color_Space

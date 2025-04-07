#include "../include/Color.h"

#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace Color_Space;


S_Rgb::S_Rgb(float r, float g, float b) {
  auto validate = [](float c) {
    if (std::min(255.0f, std::max(0.0f, c)) != c) {
      throw std::domain_error("Channel initalized outside of range [0, 255].");
    }
  };

  validate(r);
  validate(g);
  validate(b);

  m_values = {r, g, b};
};


float S_Rgb::remove_gamma(int c) {
  float normalized_channel = static_cast<double>(c) / 255.0;

  const float breakpoint = 0.04045f;

  return (normalized_channel <= breakpoint)
             ? (normalized_channel / 12.92f)
             : std::pow((normalized_channel + 0.055f) / 1.055f, 2.4f);
};


Rgb S_Rgb::to_rgb() const {
  const float r = this->remove_gamma(m_values[0]);
  const float g = this->remove_gamma(m_values[1]);
  const float b = this->remove_gamma(m_values[2]);

  return Rgb(r, g, b);
};


void S_Rgb::print() const {
  std::cout << "r: " << m_values[0] << "\ng: " << m_values[1]
            << "\nb: " << m_values[2] << std::endl;
}

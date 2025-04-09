#include "../include/Color.h"

using namespace Color_Space;


Lch_Uv::Lch_Uv(float l, float c, float h, Illuminant_Label illuminant) {
  m_values = {l, c, h};
  this->m_illuminant = illuminant;
}


void Lch_Uv::print() const {
  std::cout << "[LCHuv]" << "\nL: " << m_values[0] << "\nc: " << m_values[1]
            << "\nh: " << m_values[2] << "\n\n";
}

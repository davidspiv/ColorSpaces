#include "../include/Color.h"

namespace Color_Space {


Lch_Uv::Lch_Uv(float l, float c, float h, Illuminant_Label illuminant)
    : Color(l, c, h, illuminant) {}


void Lch_Uv::print() const {
  std::cout << "[LCHuv]" << "\nL: " << m_values[0] << "\nc: " << m_values[1]
            << "\nh: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

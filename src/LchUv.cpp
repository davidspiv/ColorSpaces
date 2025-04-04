#include "../include/colorDefinitions.h"

namespace Color_Space {


Lch_Uv::Lch_Uv(float l, float c, float h) : m_values({l, c, h}) {}


void Lch_Uv::print() const {
  std::cout << "L: " << m_values[0] << "\nc: " << m_values[1]
            << "\nh: " << m_values[2] << "\n\n";
}


} // namespace Color_Space

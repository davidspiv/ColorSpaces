#ifndef UTIL_H
#define UTIL_H

#include "color.h"
#include <array>
#include <cmath>

namespace ColorSpace {

const CieXyz referenceWhiteD60(0.950470, 1.0, 1.088830);

std::array<float, 3>
multiplyMatrix(const std::array<std::array<float, 3>, 3> &matrix,
               const std::array<float, 3> &vector);

} // namespace ColorSpace

#endif

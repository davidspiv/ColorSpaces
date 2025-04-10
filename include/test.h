#ifndef TEST_H
#define TEST_H

#include "Color.h"

namespace Color_Space {

void test_cie2000();
void test_xyz_to_rgb_to_xyz(const Rgb &in_rgb);
void test_conversion();

} // namespace Color_Space

#endif

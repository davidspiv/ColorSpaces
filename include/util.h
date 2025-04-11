#ifndef UTIL_H
#define UTIL_H

#include <array>

#include "Color.h"
#include "Matrix.h"
#include "Profile.h"

namespace Color_Space {


static constexpr float epsilon = 216.0f / 24389.0f;
static constexpr float kappa = 24389.0f / 27.0f;


float to_degrees(const float radians);


float to_radians(const float degrees);


std::array<float, 3>
to_polar_color_space(const std::array<float, 3> &cartesianColor_Space);


float apply_gamma(const float c, Gamma gamma);


float remove_gamma(float c, Gamma gamma);


Matrix create_to_xyz_transformation_matrix(const Profile &profile);


Profile get_profile(const Rgb_Profile_Label profile);


} // namespace Color_Space
#endif

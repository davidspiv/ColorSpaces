#ifndef PROFILE_H
#define PROFILE_H

#include "Color.h"
#include "Matrix.h"

#include <array>
#include <iostream>
#include <unordered_map>

namespace Color_Space {


struct Profile {
  Rgb_Working_Space working_space;
  Xyz primary_r;
  Xyz primary_g;
  Xyz primary_b;
  Illuminant_Label illuminant_label;
  Gamma gamma;
};


const static std::unordered_map<Illuminant_Label, Xyz> illuminants = {
    {A, Xyz(1.09850f, 1.00000f, 0.35585f)},
    {B, Xyz(0.99072f, 1.00000f, 0.85223f)},
    {C, Xyz(0.98074f, 1.00000f, 1.18232f)},
    {D50, Xyz(0.96422f, 1.00000f, 0.82521f)},
    {D55, Xyz(0.95682f, 1.00000f, 0.92149f)},
    {D65, Xyz(0.95047f, 1.00000f, 1.08883f)},
    {D75, Xyz(0.94972f, 1.00000f, 1.22638f)},
    {E, Xyz(1.00000f, 1.00000f, 1.00000f)},
    {F2, Xyz(0.99186f, 1.00000f, 0.67393f)},
    {F7, Xyz(0.95041f, 1.00000f, 1.08747f)},
    {F11, Xyz(1.00962f, 1.00000f, 0.64350f)}};


const static std::vector<Profile> profiles = {
    {S_RGB, Xyz(0.6400f, 0.3300f, 0.212656f), Xyz(0.3000f, 0.6000f, 0.715158f),
     Xyz(0.1500f, 0.0600f, 0.072186f), D65, Gamma::SRGB},

    {ADOBE_RGB_1998, Xyz(0.6400f, 0.3300f, 0.297361f),
     Xyz(0.2100f, 0.7100f, 0.627355f), Xyz(0.1500f, 0.0600f, 0.075285f), D65,
     Gamma::SIMPLE_22},

    {APPLE_RGB, Xyz(0.6250f, 0.3400f, 0.244634f),
     Xyz(0.2800f, 0.5950f, 0.672034f), Xyz(0.1550f, 0.0700f, 0.083332f), D65,
     Gamma::SIMPLE_18},

    {BEST_RGB, Xyz(0.7347f, 0.2653f, 0.228457f),
     Xyz(0.2150f, 0.7750f, 0.737352f), Xyz(0.1300f, 0.0350f, 0.034191f), D50,
     Gamma::SIMPLE_22}, // D50

    {BETA_RGB, Xyz(0.6888f, 0.3112f, 0.303273f),
     Xyz(0.1986f, 0.7551f, 0.663786f), Xyz(0.1265f, 0.0352f, 0.032941f), D50,
     Gamma::SIMPLE_22},

    {BRUCE_RGB, Xyz(0.6400f, 0.3300f, 0.240995f),
     Xyz(0.2800f, 0.6500f, 0.683554f), Xyz(0.1500f, 0.0600f, 0.075452f), D65,
     Gamma::SIMPLE_22},

    {CIE_RGB, Xyz(0.7350f, 0.2650f, 0.176204f),
     Xyz(0.2740f, 0.7170f, 0.812985f), Xyz(0.1670f, 0.0090f, 0.010811f), E,
     Gamma::SIMPLE_22},

    {COLORMATCH_RGB, Xyz(0.6300f, 0.3400f, 0.274884f),
     Xyz(0.2950f, 0.6050f, 0.658132f), Xyz(0.1500f, 0.0750f, 0.066985f), D50,
     Gamma::SIMPLE_18},

    {DON_RGB_4, Xyz(0.6960f, 0.3000f, 0.278350f),
     Xyz(0.2150f, 0.7650f, 0.687970f), Xyz(0.1300f, 0.0350f, 0.033680f), D50,
     Gamma::SIMPLE_22},

    {ECI_RGB_V2, Xyz(0.6700f, 0.3300f, 0.320250f),
     Xyz(0.2100f, 0.7100f, 0.602071f), Xyz(0.1400f, 0.0800f, 0.077679f), D50,
     Gamma::L_STAR},

    {EKTA_SPACE_PS5, Xyz(0.6950f, 0.3050f, 0.260629f),
     Xyz(0.2600f, 0.7000f, 0.734946f), Xyz(0.1100f, 0.0050f, 0.004425f), D50,
     Gamma::SIMPLE_22},

    {NTSC_RGB, Xyz(0.6700f, 0.3300f, 0.298839f),
     Xyz(0.2100f, 0.7100f, 0.586811f), Xyz(0.1400f, 0.0800f, 0.114350f), C,
     Gamma::SIMPLE_22},

    {PAL_SECAM_RGB, Xyz(0.6400f, 0.3300f, 0.222021f),
     Xyz(0.2900f, 0.6000f, 0.706645f), Xyz(0.1500f, 0.0600f, 0.071334f), D65,
     Gamma::SIMPLE_22},

    {PRO_PHOTO_RGB, Xyz(0.7347f, 0.2653f, 0.288040f),
     Xyz(0.1596f, 0.8404f, 0.711874f), Xyz(0.0366f, 0.0001f, 0.000086f), D50,
     Gamma::SIMPLE_18},

    {SMPTE_C_RGB, Xyz(0.6300f, 0.3400f, 0.212395f),
     Xyz(0.3100f, 0.5950f, 0.701049f), Xyz(0.1550f, 0.0700f, 0.086556f), D65,
     Gamma::SIMPLE_22},

    {WIDE_GAMUT_RGB, Xyz(0.7350f, 0.2650f, 0.258187f),
     Xyz(0.1150f, 0.8260f, 0.724938f), Xyz(0.1570f, 0.0180f, 0.016875f), D50,
     Gamma::SIMPLE_22},
};


} // namespace Color_Space
#endif

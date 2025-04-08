#ifndef PROFILE_H
#define PROFILE_H

#include "Matrix.h"

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

enum Gamma { SRGB, SIMPLE_22, SIMPLE_18, L_STAR };

struct Profile {
  std::string name;
  Matrix primary_r;
  Matrix primary_g;
  Matrix primary_b;
  Matrix illuminant;
  Gamma gamma;
};

const static std::unordered_map<std::string, Matrix> illuminants = {
    {"a", Matrix({{1.09850f}, {1.00000f}, {0.35585f}})},
    {"b", Matrix({{0.99072f}, {1.00000f}, {0.85223f}})},
    {"c", Matrix({{0.98074f}, {1.00000f}, {1.18232f}})},
    {"d50", Matrix({{0.96422f}, {1.00000f}, {0.82521f}})},
    {"d55", Matrix({{0.95682f}, {1.00000f}, {0.92149f}})},
    {"d65", Matrix({{0.95047f}, {1.00000f}, {1.08883f}})},
    {"d75", Matrix({{0.94972f}, {1.00000f}, {1.22638f}})},
    {"e", Matrix({{1.00000f}, {1.00000f}, {1.00000f}})},
    {"f2", Matrix({{0.99186f}, {1.00000f}, {0.67393f}})},
    {"f7", Matrix({{0.95041f}, {1.00000f}, {1.08747f}})},
    {"f11", Matrix({{1.00962f}, {1.00000f}, {0.64350f}})}};


const static std::vector<Profile> profiles = {
    {"srgb", Matrix({{0.6400f}, {0.3300f}, {0.212656f}}),
     Matrix({{0.3000f}, {0.6000f}, {0.715158f}}),
     Matrix({{0.1500f}, {0.0600f}, {0.072186f}}), illuminants.at("d65"),
     Gamma::SRGB},

    {"adobe_rgb_1998", Matrix({{0.6400f}, {0.3300f}, {0.297361f}}),
     Matrix({{0.2100f}, {0.7100f}, {0.627355f}}),
     Matrix({{0.1500f}, {0.0600f}, {0.075285f}}), illuminants.at("d65"),
     Gamma::SIMPLE_22},

    {"apple_rgb", Matrix({{0.6250f}, {0.3400f}, {0.244634f}}),
     Matrix({{0.2800f}, {0.5950f}, {0.672034f}}),
     Matrix({{0.1550f}, {0.0700f}, {0.083332f}}), illuminants.at("d65"),
     Gamma::SIMPLE_18},

    {"best_rgb", Matrix({{0.7347f}, {0.2653f}, {0.228457f}}),
     Matrix({{0.2150f}, {0.7750f}, {0.737352f}}),
     Matrix({{0.1300f}, {0.0350f}, {0.034191f}}), illuminants.at("d50"),
     Gamma::SIMPLE_22}, // D50

    {"beta_rgb", Matrix({{0.6888f}, {0.3112f}, {0.303273f}}),
     Matrix({{0.1986f}, {0.7551f}, {0.663786f}}),
     Matrix({{0.1265f}, {0.0352f}, {0.032941f}}), illuminants.at("d50"),
     Gamma::SIMPLE_22},

    {"bruce_rgb", Matrix({{0.6400f}, {0.3300f}, {0.240995f}}),
     Matrix({{0.2800f}, {0.6500f}, {0.683554f}}),
     Matrix({{0.1500f}, {0.0600f}, {0.075452f}}), illuminants.at("d65"),
     Gamma::SIMPLE_22},

    {"cie_rgb", Matrix({{0.7350f}, {0.2650f}, {0.176204f}}),
     Matrix({{0.2740f}, {0.7170f}, {0.812985f}}),
     Matrix({{0.1670f}, {0.0090f}, {0.010811f}}), illuminants.at("e"),
     Gamma::SIMPLE_22},

    {"colormatch_rgb", Matrix({{0.6300f}, {0.3400f}, {0.274884f}}),
     Matrix({{0.2950f}, {0.6050f}, {0.658132f}}),
     Matrix({{0.1500f}, {0.0750f}, {0.066985f}}), illuminants.at("d50"),
     Gamma::SIMPLE_18},

    {"don_rgb_4", Matrix({{0.6960f}, {0.3000f}, {0.278350f}}),
     Matrix({{0.2150f}, {0.7650f}, {0.687970f}}),
     Matrix({{0.1300f}, {0.0350f}, {0.033680f}}), illuminants.at("d50"),
     Gamma::SIMPLE_22},

    {"eci_rgb_v2", Matrix({{0.6700f}, {0.3300f}, {0.320250f}}),
     Matrix({{0.2100f}, {0.7100f}, {0.602071f}}),
     Matrix({{0.1400f}, {0.0800f}, {0.077679f}}), illuminants.at("d50"),
     Gamma::L_STAR},

    {"ekta_space_ps5", Matrix({{0.6950f}, {0.3050f}, {0.260629f}}),
     Matrix({{0.2600f}, {0.7000f}, {0.734946f}}),
     Matrix({{0.1100f}, {0.0050f}, {0.004425f}}), illuminants.at("d50"),
     Gamma::SIMPLE_22},

    {"ntsc_rgb", Matrix({{0.6700f}, {0.3300f}, {0.298839f}}),
     Matrix({{0.2100f}, {0.7100f}, {0.586811f}}),
     Matrix({{0.1400f}, {0.0800f}, {0.114350f}}), illuminants.at("c"),
     Gamma::SIMPLE_22},

    {"pal_secam_rgb", Matrix({{0.6400f}, {0.3300f}, {0.222021f}}),
     Matrix({{0.2900f}, {0.6000f}, {0.706645f}}),
     Matrix({{0.1500f}, {0.0600f}, {0.071334f}}), illuminants.at("d65"),
     Gamma::SIMPLE_22},

    {"prophoto_rgb", Matrix({{0.7347f}, {0.2653f}, {0.288040f}}),
     Matrix({{0.1596f}, {0.8404f}, {0.711874f}}),
     Matrix({{0.0366f}, {0.0001f}, {0.000086f}}), illuminants.at("d50"),
     Gamma::SIMPLE_18},

    {"smpte_c_rgb", Matrix({{0.6300f}, {0.3400f}, {0.212395f}}),
     Matrix({{0.3100f}, {0.5950f}, {0.701049f}}),
     Matrix({{0.1550f}, {0.0700f}, {0.086556f}}), illuminants.at("d65"),
     Gamma::SIMPLE_22},

    {"wide_gamut_rgb", Matrix({{0.7350f}, {0.2650f}, {0.258187f}}),
     Matrix({{0.1150f}, {0.8260f}, {0.724938f}}),
     Matrix({{0.1570f}, {0.0180f}, {0.016875f}}), illuminants.at("d50"),
     Gamma::SIMPLE_22},
};

#endif

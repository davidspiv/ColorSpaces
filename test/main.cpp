#include "../include/Color.h"
#include "../include/test.h"
#include "../include/timer.h"
#include "../include/util.h"

using namespace Color_Space;

int main() {
  Timer timer;

  Rgb rgb(100, 45, 200);
  //   Xyz xyz(0.148317, 0.082178, 0.416816);

  Xyz(0.166163, 0.087556, 0.554469).to_rgb(profiles[1]).print();
  //   .adapt_to_white_point(illuminants.at("d65"), illuminants.at("d50"))

  test_xyz_to_rgb_to_xyz(rgb);
  test_cie2000();
}

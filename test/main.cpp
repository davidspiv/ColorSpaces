#include "../include/Color.h"
#include "../include/test.h"
#include "../include/timer.h"
#include "../include/util.h"

using namespace Color_Space;

int main() {
  Timer timer;

  S_Rgb s_rgb(100, 45, 200);

//   s_rgb.to_rgb()
//       .to_xyz()
//       .adapt_to_white_point(illuminants.at("d65"), illuminants.at("d50"))
//       .to_rgb(illuminants.at("d50"), primaries.at("srgb"))
//       .to_s_rgb()
//       .print();

  test_xyz_to_rgb_to_xyz(s_rgb);
  test_cie2000();
}

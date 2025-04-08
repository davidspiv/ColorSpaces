#include "../include/Color.h"
#include "../include/test.h"
#include "../include/timer.h"
#include "../include/util.h"

#include <algorithm>
#include <string>

using namespace Color_Space;


int main() {
  Timer timer;

  Rgb rgb(100, 45, 200);
  Xyz xyz(0.166163, 0.087556, 0.554469);

  //   xyz.adapt_to_white_point(get_illuminant("d65"), get_illuminant("d65"))
  //       .to_rgb(curr_profile)
  //       .print();

  xyz.to_lab().print();

  test_xyz_to_rgb_to_xyz(rgb);
  test_cie2000();
}

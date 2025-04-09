#include "../include/Color.h"
#include "../include/Profile.h"
#include "../include/test.h"
#include "../include/timer.h"
#include "../include/util.h"

using namespace Color_Space;


int main() {
  Timer timer;

  Rgb rgb(100, 45, 200);
  Xyz xyz = Xyz(0.166163, 0.087556, 0.554469, D50);

  xyz.to_xyy().print();
  xyz.to_lab().print();
  xyz.to_lab().to_lch_ab().print();
  xyz.to_luv().print();
  xyz.to_luv().to_lch_uv().print();
  xyz.to_rgb().print();

  test_xyz_to_rgb_to_xyz(rgb);
  test_cie2000();
}

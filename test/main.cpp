#include "../include/Color.h"
#include "../include/Profile.h"
#include "../include/test.h"
#include "../include/timer.h"
#include "../include/util.h"

int main() {
  Timer timer;
  const Color_Space::Lch_Uv lch_uv(52.4876, 67.1528, 124.4229);

  lch_uv.to_luv().print();

  //   const Color_Space::Rgb rgb(115, 80, 64);
  //   Color_Space::test_xyz_to_rgb_to_xyz(rgb);
  //   Color_Space::test_cie2000();
  //   Color_Space::test_conversion();
}

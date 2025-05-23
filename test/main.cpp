#include "../include/Color.h"
#include "../include/Profile.h"
#include "../include/test.h"
#include "../include/timer.h"
#include "../include/util.h"

int main() {
  Timer timer;
  const Color_Space::Lch_Uv lch_uv(52.4876, 67.1528, 124.4229, Color_Space::E);

  lch_uv.to_luv().to_xyz().to_rgb(Color_Space::ADOBE_RGB_1998).print();

  const Color_Space::Rgb rgb(115, 80, 64);
  Color_Space::test_cie2000();
  Color_Space::test_conversion();
}

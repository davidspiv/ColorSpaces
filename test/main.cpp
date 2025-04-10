#include "../include/Color.h"
#include "../include/Profile.h"
#include "../include/test.h"
#include "../include/timer.h"
#include "../include/util.h"

int main() {
  Timer timer;

  //   Color_Space::Lab lab(38.4400, 13.6100, 14.5291, Color_Space::D50);

  //   lab.to_xyz().to_rgb(Color_Space::ADOBE_RGB_1998).print();

  //   rgb.to_xyz().print();

  const Color_Space::Rgb rgb(1, 1, 1);
  Color_Space::test_xyz_to_rgb_to_xyz(rgb);
  Color_Space::test_cie2000();
  Color_Space::test_conversion();
}

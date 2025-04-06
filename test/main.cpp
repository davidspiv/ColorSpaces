#include "../include/Color.h"
#include "../include/test.h"
#include "../include/timer.h"
#include "../include/util.h"

using namespace Color_Space;

int main() {

  S_Rgb s_rgb(100, 45, 200);

  test_xyz_to_rgb_to_xyz(s_rgb);
  test_cie2000();
}

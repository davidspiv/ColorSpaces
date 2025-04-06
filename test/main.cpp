#include "../include/colorDefinitions.h"
#include "../include/test.h"
#include "../include/timer.h"
#include "../include/util.h"

using namespace Color_Space;

int main() {

  Srgb srgb(100, 45, 200);

  test_xyz_to_rgb_to_xyz(srgb);
  test_cie2000();
}

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/colorDefinitions.h"
#include "../include/test.h"
#include "../include/timer.h"
#include "../include/util.h"

using namespace Color_Space;

int main() {

  Srgb srgb(100, 45, 200);

  srgb.to_rgb().to_xyz().to_rgb().to_srgb().print();

  test_cie2000();
}

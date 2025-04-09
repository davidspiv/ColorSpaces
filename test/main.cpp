#include "../include/Color.h"
#include "../include/Profile.h"
#include "../include/test.h"
#include "../include/timer.h"
#include "../include/util.h"

int main() {
  Timer timer;

  //   Rgb rgb(100, 45, 200);
  //   Xyz xyz = Xyz(0.166163, 0.087556, 0.554469, D50);

  //   xyz.to_xyy().print();
  //   xyz.to_lab().print();
  //   xyz.to_lab().to_lch_ab().print();
  //   xyz.to_luv().print();
  //   xyz.to_luv().to_lch_uv().print();
  //   xyz.to_rgb().print();

  Color_Space::Rgb rgb(30, 99, 15);
  Color_Space::Xyz xyz = rgb.to_xyz(Color_Space::SMPTE_C_RGB)
                             .adapt_to_white_point(Color_Space::D75);
  Color_Space::Lab lab = xyz.to_lab();

  Color_Space::Lab other_lab(53.2f, 15.0f, -40.0f, Color_Space::D75);
  float deltaE = lab.diff_cie_2000(other_lab);

  Color_Space::test_xyz_to_rgb_to_xyz(rgb);
  Color_Space::test_cie2000();
}

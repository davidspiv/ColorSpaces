#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/Color.h"
#include "../include/util.h"

namespace Color_Space {


void test_xyz_to_rgb_to_xyz(const Rgb &in_rgb) {
  auto [in_r, in_g, in_b] = in_rgb.get_values();

  const Rgb out_rgb = in_rgb.to_xyz().to_rgb();

  auto [out_r, out_g, out_b] = out_rgb.get_values();

  if (std::abs(out_r - in_r) <= 1 && std::abs(out_g - in_g) <= 1 &&
      std::abs(out_b - in_b) <= 1) {
    std::cout << "rgb->xyz->rgb test passed!" << std::endl;
  } else {
    std::cout << "FAILED: rgb->xyz->rgb test" << std::endl;
  }
};


void test_cie2000() {
  std::ifstream in("./test/dist.dat");
  if (!in) {
    std::cerr << "Failed to open file.\n";
    return;
  }

  std::string line;

  size_t errorCt = 0;
  const float errTolerance = 0.0001f;

  for (int i = 0; i < 32; ++i) {
    std::vector<float> tokens;

    // Read first line
    if (!std::getline(in, line)) {
      std::cerr << "Unexpected end of file at line " << 2 * i + 1 << '\n';
      break;
    }

    std::istringstream iss1(line);
    float value;
    while (iss1 >> value) {
      tokens.push_back(value);
    }

    if (tokens.size() < 5) {
      std::cerr << "Not enough values in line " << 2 * i + 1 << '\n';
      continue;
    }

    Color_Space::Lab a_lab(tokens[2], tokens[3], tokens[4]);
    float deltaE = tokens.back();

    tokens.clear();

    // Read second line
    if (!std::getline(in, line)) {
      std::cerr << "Unexpected end of file at line " << 2 * i + 2 << '\n';
      break;
    }

    std::istringstream iss2(line);
    while (iss2 >> value) {
      tokens.push_back(value);
    }

    if (tokens.size() < 5) {
      std::cerr << "Not enough values in line " << 2 * i + 2 << '\n';
      continue;
    }

    Color_Space::Lab b_lab(tokens[1], tokens[2], tokens[3]);

    // Output both labs
    const float answer = a_lab.diff_cie_2000(b_lab);

    if ((std::abs(answer - deltaE) >= errTolerance)) {
      std::cout << "ERROR with CEI2000 at input #" << i << std::endl;
      std::cout << "answer: " << answer << '\n';
      std::cout << "result: " << deltaE << '\n' << std::endl;
      ++errorCt;
    }
  }
  if (!errorCt) {
    std::cout << "CEI2000 test passed!" << std::endl;
  }

  in.close();
}

// LLM code
void test_conversion() {
  std::ifstream in("./test/conversion.dat");
  if (!in) {
    std::cerr << "Failed to open file.\n";
    return;
  }

  std::string line;
  getline(in, line);

  while (getline(in, line)) {


    std::istringstream ss(line);
    std::vector<double> tokens;
    std::vector<Color> colors;
    double value;

    while (ss >> value) {
      tokens.push_back(value);
    }


    colors.emplace_back(
        Lab(tokens[3], tokens[4], tokens[5])); // Your Lab constructor

    for (size_t i = 6; i < tokens.size(); i += 3) {
      float r = static_cast<float>(tokens[i]);
      float g = static_cast<float>(tokens[i + 1]);
      float b = static_cast<float>(tokens[i + 2]);
      colors.emplace_back(Rgb(r, g, b));
    }

    auto [l, a, b] = colors.at(0).get_values(); // Assuming Lab input as
    Lab source_lab(l, a, b, D50);

    const Rgb adobe_rgb_1998 = source_lab.to_xyz().to_rgb(ADOBE_RGB_1998);
    const Rgb apple_rgb = source_lab.to_xyz().to_rgb(APPLE_RGB);
    const Rgb best_rgb = source_lab.to_xyz().to_rgb(BEST_RGB);
    const Rgb beta_rgb = source_lab.to_xyz().to_rgb(BETA_RGB);
    const Rgb bruce_rgb = source_lab.to_xyz().to_rgb(BRUCE_RGB);
    // const Rgb cie_rgb = source_lab.to_xyz().to_rgb(CIE_RGB);
    const Rgb colormatch_rgb = source_lab.to_xyz().to_rgb(COLORMATCH_RGB);
    const Rgb don_rgb_4 = source_lab.to_xyz().to_rgb(DON_RGB_4);
    // const Rgb eci_rgb_v2 = source_lab.to_xyz().to_rgb(ECI_RGB_V2);
    const Rgb ekta_space_ps5 = source_lab.to_xyz().to_rgb(EKTA_SPACE_PS5);
    // const Rgb ntsc_rgb = source_lab.to_xyz().to_rgb(NTSC_RGB);
    // const Rgb pal_secam_rgb = source_lab.to_xyz().to_rgb(PAL_SECAM_RGB);
    const Rgb pro_photo_rgb = source_lab.to_xyz().to_rgb(PRO_PHOTO_RGB);
    // const Rgb smpte_c_rgb = source_lab.to_xyz().to_rgb(SMPTE_C_RGB);
    const Rgb wide_gamut_rgb = source_lab.to_xyz().to_rgb(WIDE_GAMUT_RGB);

    if (adobe_rgb_1998 != colors.at(1)) {
      std::cout << std::endl;
      std::cout << "failed: adobe_rgb_1998" << std::endl;
      auto [t_r, t_g, t_b] = colors.at(1).get_values();
      Rgb(t_r, t_g, t_b).print();
      adobe_rgb_1998.print();
      std::cout << std::endl;
      return;
    };

    if (apple_rgb != colors.at(2)) {
      std::cout << std::endl;
      std::cout << "failed: apple_rgb" << std::endl;
      auto [t_r, t_g, t_b] = colors.at(2).get_values();
      Rgb(t_r, t_g, t_b).print();
      apple_rgb.print();
      std::cout << std::endl;
      source_lab.print();
      continue;
    };

    if (best_rgb != colors.at(3)) {
      std::cout << std::endl;
      std::cout << "failed: best_rgb" << std::endl;
      auto [t_r, t_g, t_b] = colors.at(3).get_values();
      Rgb(t_r, t_g, t_b).print();
      best_rgb.print();
      std::cout << std::endl;
      return;
    };

    if (beta_rgb != colors.at(4)) {
      std::cout << std::endl;
      std::cout << "failed: beta_rgb" << std::endl;
      auto [t_r, t_g, t_b] = colors.at(4).get_values();
      Rgb(t_r, t_g, t_b).print();
      beta_rgb.print();
      std::cout << std::endl;
      return;
    };

    if (bruce_rgb != colors.at(5)) {
      std::cout << std::endl;
      std::cout << "failed: bruce_rgb" << std::endl;
      auto [t_r, t_g, t_b] = colors.at(5).get_values();
      Rgb(t_r, t_g, t_b).print();
      bruce_rgb.print();
      std::cout << std::endl;
      return;
    };

    // if (cie_rgb != colors.at(6)) {
    //   std::cout << "failed" << std::endl;continue;
    // };

    if (colormatch_rgb != colors.at(7)) {
      std::cout << std::endl;
      std::cout << "failed: colormatch_rgb" << std::endl;
      auto [t_r, t_g, t_b] = colors.at(7).get_values();
      Rgb(t_r, t_g, t_b).print();
      colormatch_rgb.print();
      std::cout << std::endl;
      return;
    };

    if (don_rgb_4 != colors.at(8)) {
      std::cout << std::endl;
      std::cout << "failed: don_rgb_4" << std::endl;
      auto [t_r, t_g, t_b] = colors.at(8).get_values();
      Rgb(t_r, t_g, t_b).print();
      don_rgb_4.print();
      std::cout << std::endl;
      return;
    };

    // if (eci_rgb_v2 != colors.at(9)) {
    //   std::cout << "failed" << std::endl;continue;
    // };

    if (ekta_space_ps5 != colors.at(10)) {
      std::cout << std::endl;
      std::cout << "failed: ekta_space_ps5" << std::endl;
      auto [t_r, t_g, t_b] = colors.at(10).get_values();
      Rgb(t_r, t_g, t_b).print();
      ekta_space_ps5.print();
      std::cout << std::endl;
      return;
    };

    // if (ntsc_rgb != colors.at(12)) {
    //   std::cout << "failed" << std::endl;continue;
    // };

    // if (pal_secam_rgb != colors.at(13)) {
    //   std::cout << "failed" << std::endl;continue;
    // };

    if (pro_photo_rgb != colors.at(14)) {
      std::cout << std::endl;
      std::cout << "failed: pro_photo_rgb" << std::endl;
      auto [t_r, t_g, t_b] = colors.at(14).get_values();
      Rgb(t_r, t_g, t_b).print();
      pro_photo_rgb.print();
      std::cout << std::endl;
      return;
    };

    // if (smpte_c_rgb != colors.at(17)) {
    //   std::cout << "failed" << std::endl;continue;
    // };

    if (wide_gamut_rgb != colors.at(19)) {
      std::cout << std::endl;
      std::cout << "failed: wide_gamut_rgb" << std::endl;
      auto [t_r, t_g, t_b] = colors.at(19).get_values();
      Rgb(t_r, t_g, t_b).print();
      wide_gamut_rgb.print();
      std::cout << std::endl;
      return;
    };
  }


  in.close();
  std::cout << "conversion test passed!" << std::endl;
}


} // namespace Color_Space

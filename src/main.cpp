#include <cstring> // for strtok
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/colorDefinitions.h"
#include "../include/timer.h"
#include "../include/util.h"


int main() {
  std::ifstream in("test.dat");
  if (!in) {
    std::cerr << "Failed to open file.\n";
    return 1;
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
}

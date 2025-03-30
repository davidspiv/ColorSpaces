#include "../include/util.h"
#include "../include/color.h"

#include <array>


std::array<double, 3>
multiplyMatrix(const std::array<std::array<double, 3>, 3> &matrix,
               const std::array<double, 3> &vector) {

  std::array<double, 3> result = {0.0, 0.0, 0.0};

  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      result[i] += matrix[i][j] * vector[j];
    }
  }

  return result;
}


size_t findClosestColorIdx(const StdRGB &targetColor,
                           const std::vector<StdRGB> &quantColors) {
  size_t closestColorIdx = 0;
  double minDist = std::numeric_limits<double>::max();

  const CIELab tColorCEI = rgbToCIE(linearize(targetColor));

  for (size_t i = 0; i < quantColors.size(); i++) {

    const CIELab oColorCEI = rgbToCIE(linearize(quantColors.at(i)));

    double dist = distSquared(tColorCEI, oColorCEI);
    if (dist < minDist) {
      minDist = dist;
      closestColorIdx = i;
    }
  }

  return closestColorIdx;
}

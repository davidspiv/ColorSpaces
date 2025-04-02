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

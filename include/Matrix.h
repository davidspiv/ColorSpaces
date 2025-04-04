#ifndef MATRICES_H
#define MATRICES_H

#include <array>
#include <iostream>
#include <vector>

class Matrix {
public:
  Matrix(int rows, int cols);
  Matrix(const std::vector<std::vector<float>> &arr_2d);

  size_t rows() const { return m_rows; }
  size_t cols() const { return m_cols; }

  const float &operator()(int i, int j) const; // Read
  float &operator()(int i, int j);             // Assign

  Matrix multiply(const Matrix &other) const;
  Matrix column_wise_scaling(const Matrix &other) const;
  Matrix invert() const;

private:
  std::vector<std::vector<float>> m_values;
  size_t m_rows;
  size_t m_cols;
};

std::ostream &operator<<(std::ostream &os, const Matrix &a);

#endif

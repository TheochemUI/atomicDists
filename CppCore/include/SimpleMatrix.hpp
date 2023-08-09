#pragma once

#include <cstddef>
#include <iostream>
#include <range/v3/algorithm/copy.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/transform.hpp>
#include <vector>

namespace atmdist::types {
template <typename T> class SimpleMatrix;
template <typename T>
SimpleMatrix<T> concatenate_horizontal(const SimpleMatrix<T> &mat1,
                                       const SimpleMatrix<T> &mat2);
template <typename T>
SimpleMatrix<T> concatenate_vertical(const SimpleMatrix<T> &mat1,
                                     const SimpleMatrix<T> &mat2);

template <typename T> class SimpleMatrix {
public:
  SimpleMatrix(size_t rows, size_t cols)
      : data(rows, std::vector<T>(cols, 0)) {}
  SimpleMatrix(size_t rows, size_t cols, T value)
      : data(rows, std::vector<T>(cols, value)) {}
  SimpleMatrix(std::initializer_list<std::initializer_list<T>> values)
      : data(values.begin(), values.end()) {}
  SimpleMatrix(size_t rows, size_t cols,
               std::initializer_list<std::initializer_list<T>> values) {
    if (values.size() != rows ||
        (values.size() > 0 && values.begin()->size() != cols)) {
      throw std::invalid_argument(
          "Size mismatch between parameters and initializer list");
    }

    data.resize(rows);
    auto it = values.begin();
    for (size_t i = 0; i < rows; ++i, ++it) {
      data[i] = std::vector<T>(it->begin(), it->end());
    }
  }

  T &operator()(size_t row, size_t col) { return data[row][col]; }
  const T &operator()(size_t row, size_t col) const { return data[row][col]; }

  size_t rows() const { return data.size(); }
  size_t cols() const { return data.empty() ? 0 : data[0].size(); }

  friend std::ostream &operator<<(std::ostream &os,
                                  const SimpleMatrix<T> &mat) {
    for (const auto &row : mat.data) {
      for (const auto &val : row) {
        os << val << ' ';
      }
      os << '\n';
    }
    return os;
  }
  std::vector<T> &row(size_t row) { return data[row]; }
  const std::vector<T> &row(size_t row) const { return data[row]; }
  auto column(size_t col) {
    return ranges::views::iota(size_t(0), data.size()) |
           ranges::views::transform(
               [this, col](size_t row) { return std::ref(data[row][col]); });
  }
  auto column(size_t col) const {
    return ranges::views::iota(size_t(0), data.size()) |
           ranges::views::transform(
               [this, col](size_t row) -> const T & { return data[row][col]; });
  }

  friend SimpleMatrix concatenate_horizontal<>(const SimpleMatrix &mat1,
                                               const SimpleMatrix &mat2);
  friend SimpleMatrix concatenate_vertical<>(const SimpleMatrix &mat1,
                                             const SimpleMatrix &mat2);

private:
  std::vector<std::vector<T>> data;
};

template <typename T>
SimpleMatrix<T> concatenate_horizontal(const SimpleMatrix<T> &mat1,
                                       const SimpleMatrix<T> &mat2) {
  if (mat1.rows() != mat2.rows()) {
    throw std::invalid_argument(
        "Number of rows must be the same for horizontal concatenation");
  }

  SimpleMatrix<T> result(mat1.rows(), mat1.cols() + mat2.cols());
  for (size_t i = 0; i < mat1.rows(); ++i) {
    auto row1 = mat1.row(i);
    auto row2 = mat2.row(i);
    ranges::copy(row1, result.row(i).begin());
    ranges::copy(row2, result.row(i).begin() + mat1.cols());
  }
  return result;
}

template <typename T>
SimpleMatrix<T> concatenate_vertical(const SimpleMatrix<T> &mat1,
                                     const SimpleMatrix<T> &mat2) {
  if (mat1.cols() != mat2.cols()) {
    throw std::invalid_argument(
        "Number of columns must be the same for vertical concatenation");
  }

  SimpleMatrix<T> result(mat1.rows() + mat2.rows(), mat1.cols());
  ranges::copy(mat1.data.begin(), mat1.data.end(), result.data.begin());
  ranges::copy(mat2.data.begin(), mat2.data.end(),
               result.data.begin() + mat1.rows());
  return result;
}

} // namespace atmdist::types

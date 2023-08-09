#include "include/DistOps.hpp"
#include "include/SimpleMatrix.hpp"
#include <cstdlib>

// #ifdef WITH_FMT
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
// #endif

using namespace atmdist::types;

int main(int argc, char *argv[]) {
  SimpleMatrix<int> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  fmt::print("Cols: {}\n", mat.cols());
  fmt::print("Rows: {}\n", mat.rows());
  fmt::print("Matrix:\n{}\n", fmt::streamed(mat));
  for (int &x : mat.column(2)) {
    std::cout << x << ' ';
  }
  for (int &x : mat.row(2)) {
    std::cout << x << ' ';
  }

  SimpleMatrix<double> mat2(
      {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
  auto result = atmdist::rowwise_euclidean_distances(mat2);
  fmt::print("Initially\n{}\nResult:\n{}\n", fmt::streamed(mat2),
             fmt::streamed(result));
  return EXIT_SUCCESS;
}

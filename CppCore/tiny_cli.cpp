#include "include/SimpleMatrix.hpp"
#include <cstdlib>

// #ifdef WITH_FMT
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
// #endif



int main(int argc, char *argv[]) {
  atmdist::types::SimpleMatrix<int> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  fmt::print("Cols: {}\n", mat.cols());
  fmt::print("Rows: {}\n", mat.rows());
  fmt::print("Matrix:\n{}\n", fmt::streamed(mat));
    for (int& x : mat.column(2)) {
        std::cout << x << ' ';
    }
    for (int& x : mat.row(2)) {
        std::cout << x << ' ';
    }
  return EXIT_SUCCESS;
}

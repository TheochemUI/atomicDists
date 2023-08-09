#include "include/SimpleMatrix.hpp"
#include <cstdlib>

// #ifdef WITH_FMT
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
// #endif


int main(int argc, char *argv[]) {
  auto foo = atmdist::types::SimpleMatrix<double>(3, 3);
  fmt::print("{}", foo.cols());
  fmt::print("{}", foo.rows());

  return EXIT_SUCCESS;
}

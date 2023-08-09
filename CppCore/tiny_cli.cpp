#include "include/DistOps.hpp"
#include "include/EuclideanDistance.hpp"
#include "include/SimpleMatrix.hpp"
#include "include/AtomicMeasures.hpp"
#include "../subprojects/readCon/CppCore/include/ReadCon.hpp"
#include <cstdlib>

// #ifdef WITH_FMT
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
// #endif

using namespace atmdist::types;
using namespace atmdist::distance;

int main(int argc, char *argv[]) {
  // SimpleMatrix<int> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  // fmt::print("Cols: {}\n", mat.cols());
  // fmt::print("Rows: {}\n", mat.rows());
  // fmt::print("Matrix:\n{}\n", fmt::streamed(mat));
  // for (int &x : mat.column(2)) {
  //   std::cout << x << ' ';
  // }
  // for (int &x : mat.row(2)) {
  //   std::cout << x << ' ';
  // }

  // SimpleMatrix<double> mat2(
  //     {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
  // auto result = atmdist::rowwise_distances(mat2, EuclideanDistance<double>());
  // fmt::print("Initially\n{}\nResult:\n{}\n", fmt::streamed(mat2),
  //            fmt::streamed(result));

  if (argc != 4) {
    std::cout << "Usage: " << argv[0] << " <filename> <atomid1> <atomid2>" << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  size_t atmid1 = static_cast<size_t>(std::stod(argv[2]));
  size_t atmid2 = static_cast<size_t>(std::stod(argv[3]));
  std::vector<std::string> fconts =
      yodecon::helpers::file::read_con_file(filename);

  auto tmp = yodecon::create_single_con<yodecon::types::ConFrame>(fconts);
  auto atmA = tmp.atom_data[atmid1];
  auto atmB = tmp.atom_data[atmid2];
  auto diff = atomdatum_diff(atmA, atmB, EuclideanDistance<double>());
  fmt::print("Diff: {}, Tag: {}\n", diff.first, diff.second);

  return EXIT_SUCCESS;
}

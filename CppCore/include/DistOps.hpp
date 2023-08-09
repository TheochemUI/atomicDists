#pragma once
#include <cmath>

namespace atmdist {

namespace types {
// Forward declaration
template <typename T> class SimpleMatrix;
} // namespace types
namespace traits {
// For generically working with different matrix types

template <typename MatrixType> struct matrices;

template <typename T> struct matrices<atmdist::types::SimpleMatrix<T>> {
  using value_type = T;
};

#ifdef USE_ARMADILLO
template <typename T> struct matrices<arma::Mat<T>> {
  using value_type = typename arma::Mat<T>::elem_type;
};
#endif

#ifdef USE_EIGEN
template <typename T>
struct matrices<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> {
  using value_type =
      typename Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Scalar;
};
#endif
} // namespace traits

template <typename MatrixType, typename DistanceFunction>
auto rowwise_distances(const MatrixType& mat, DistanceFunction distanceFunc) {
  using ValueType = typename traits::matrices<MatrixType>::value_type;
  size_t n = mat.rows();
  MatrixType result(n, n);

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i; j < n; ++j) {
      ValueType distance = distanceFunc(mat.row(i), mat.row(j));
      result(i, j) = result(j, i) = distance; // Assuming symmetry
    }
  }

  return result;
}

} // namespace atmdist

#pragma once
#include <cmath>

namespace atmdist {

namespace types {
    // Forward declaration
template <typename T> class SimpleMatrix;
}
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
template <typename T> struct matrices<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> {
  using value_type = typename Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Scalar;
};
#endif
} // namespace traits

template <typename MatrixType>
auto rowwise_euclidean_distances(const MatrixType &mat) {
  using ValueType = typename traits::matrices<MatrixType>::value_type;
  size_t n = mat.rows();
  MatrixType result(n, n);

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i; j < n; ++j) {
      ValueType distance = 0;
      for (size_t k = 0; k < mat.cols(); ++k) {
        ValueType diff = mat(i, k) - mat(j, k);
        distance += diff * diff;
      }
      distance = std::sqrt(distance);
      result(i, j) = result(j, i) = distance; // Assuming symmetry
    }
  }

  return result;
}

} // namespace atmdist

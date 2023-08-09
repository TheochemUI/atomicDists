#pragma once
#include "Distance.hpp"
#include <cmath>

namespace atmdist::distance {
template <typename T>
class LpDistance {
public:
  explicit LpDistance(double p) : p_(p) {
    if (p_ <= 0) {
      throw std::invalid_argument("p must be greater than 0");
    }
  }

  T operator()(const std::vector<T> &vec1,
               const std::vector<T> &vec2) const {
    if (vec1.size() != vec2.size()) {
      throw std::invalid_argument(
          "Vectors must have the same size for distance calculation");
    }

    T sum = 0;
    for (size_t i = 0; i < vec1.size(); ++i) {
      T diff = std::abs(vec1[i] - vec2[i]);
      sum += std::pow(diff, p_);
    }

    return std::pow(sum, 1.0 / p_);
  }

private:
  double p_;
};
}

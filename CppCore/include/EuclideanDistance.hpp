#pragma once
#include "Distance.hpp"
#include <cmath>

namespace atmdist::distance {

template <typename T> class EuclideanDistance : public Distance<T> {
public:
  T calculate(const std::vector<T> &vec1,
              const std::vector<T> &vec2) const override {
    if (vec1.size() != vec2.size()) {
      throw std::invalid_argument(
          "Vectors must have the same size for distance calculation");
    }

    T sum = 0;
    for (size_t i = 0; i < vec1.size(); ++i) {
      T diff = vec1[i] - vec2[i];
      sum += diff * diff;
    }

    return std::sqrt(sum);
  }
};

} // namespace atmdist::distance

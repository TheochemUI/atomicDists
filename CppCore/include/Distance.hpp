#pragma once
#include <vector>
namespace atmdist::distance {

template <typename T> class Distance {
public:
  virtual T calculate(const std::vector<T> &vec1,
                      const std::vector<T> &vec2) const = 0;
  virtual ~Distance() = default;
};

} // namespace atmdist::distance

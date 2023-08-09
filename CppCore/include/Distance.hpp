#pragma once
#include <vector>
#include <stdexcept>
namespace atmdist::distance {

template <typename T> class Distance {
public:
  virtual T operator()(const std::vector<T> &vec1,
                      const std::vector<T> &vec2) const = 0;
  virtual ~Distance() = default;
};

} // namespace atmdist::distance

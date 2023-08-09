#pragma once

#include <cstddef>
#include <vector>

namespace atmdist::types {

template <typename T>
class SimpleMatrix {
public:
    SimpleMatrix(size_t rows, size_t cols) : data(rows, std::vector<T>(cols, 0)) {}

    T& operator()(size_t row, size_t col) { return data[row][col]; }
    const T& operator()(size_t row, size_t col) const { return data[row][col]; }

    size_t rows() const { return data.size(); }
    size_t cols() const { return data.empty() ? 0 : data[0].size(); }

private:
    std::vector<std::vector<T>> data;
};

} // namespace atmdist::types

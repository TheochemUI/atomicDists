#pragma once

#include <cstddef>
#include <vector>
#include <iostream>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/transform.hpp>

namespace atmdist::types {

template <typename T>
class SimpleMatrix {
public:
    SimpleMatrix(size_t rows, size_t cols) : data(rows, std::vector<T>(cols, 0)) {}
    SimpleMatrix(size_t rows, size_t cols, T value)
        : data(rows, std::vector<T>(cols, value)) {}
    SimpleMatrix(std::initializer_list<std::initializer_list<T>> values)
        : data(values.begin(), values.end()) {}

    T& operator()(size_t row, size_t col) { return data[row][col]; }
    const T& operator()(size_t row, size_t col) const { return data[row][col]; }

    size_t rows() const { return data.size(); }
    size_t cols() const { return data.empty() ? 0 : data[0].size(); }

    friend std::ostream& operator<<(std::ostream& os, const SimpleMatrix<T>& mat) {
        for (const auto& row : mat.data) {
            for (const auto& val : row) {
                os << val << ' ';
            }
            os << '\n';
        }
        return os;
    }
    std::vector<T>& row(size_t row) { return data[row]; }
    const std::vector<T>& row(size_t row) const { return data[row]; }
    auto column(size_t col) {
        return ranges::views::iota(size_t(0), data.size())
             | ranges::views::transform([this, col](size_t row) { return std::ref(data[row][col]); });
    }

private:
    std::vector<std::vector<T>> data;
};

} // namespace atmdist::types

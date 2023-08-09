#include "../include/SimpleMatrix.hpp"

#include <gtest/gtest.h>
#include <sstream>

using namespace atmdist::types;

TEST(SimpleMatrixTest, DefaultConstructor) {
    SimpleMatrix<int> mat(3, 4);
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 4);
    for (size_t i = 0; i < mat.rows(); ++i) {
        for (size_t j = 0; j < mat.cols(); ++j) {
            EXPECT_EQ(mat(i, j), 0);
        }
    }
}

TEST(SimpleMatrixTest, ValueConstructor) {
    SimpleMatrix<int> mat(3, 4, 7);
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 4);
    for (size_t i = 0; i < mat.rows(); ++i) {
        for (size_t j = 0; j < mat.cols(); ++j) {
            EXPECT_EQ(mat(i, j), 7);
        }
    }
}

TEST(SimpleMatrixTest, InitializerListConstructor) {
    SimpleMatrix<int> mat{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 2);
    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(0, 1), 2);
    EXPECT_EQ(mat(1, 0), 3);
    EXPECT_EQ(mat(1, 1), 4);
    EXPECT_EQ(mat(2, 0), 5);
    EXPECT_EQ(mat(2, 1), 6);
}

TEST(SimpleMatrixTest, OstreamOperator) {
    SimpleMatrix<int> mat{{1, 2}, {3, 4}};
    std::ostringstream oss;
    oss << mat;
    EXPECT_EQ(oss.str(), "1 2 \n3 4 \n");
}

TEST(SimpleMatrixTest, RowAccessor) {
    SimpleMatrix<int> mat{{1, 2}, {3, 4}};
    std::vector<int> row = mat.row(1);
    EXPECT_EQ(row, (std::vector<int>{3, 4}));
}

TEST(SimpleMatrixTest, ColumnAccessor) {
    SimpleMatrix<int> mat{{1, 2, 3}, {4, 5, 6}};
    auto col = mat.column(1);
    EXPECT_TRUE(std::equal(col.begin(), col.end(), std::vector<int>{2, 5}.begin()));
}

TEST(SimpleMatrixTest, ConstColumnAccessor) {
    const SimpleMatrix<int> mat{{1, 2, 3}, {4, 5, 6}};
    auto col = mat.column(1);
    EXPECT_TRUE(std::equal(col.begin(), col.end(), std::vector<int>{2, 5}.begin()));
}

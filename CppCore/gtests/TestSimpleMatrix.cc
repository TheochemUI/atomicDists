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
  SimpleMatrix<double> mat({
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  });

  ASSERT_EQ(mat.rows(), 3);
  ASSERT_EQ(mat.cols(), 3);
  ASSERT_EQ(mat(0, 0), 1.0);
  ASSERT_EQ(mat(0, 1), 2.0);
  ASSERT_EQ(mat(0, 2), 3.0);
  ASSERT_EQ(mat(1, 0), 4.0);
  ASSERT_EQ(mat(1, 1), 5.0);
  ASSERT_EQ(mat(1, 2), 6.0);
  ASSERT_EQ(mat(2, 0), 7.0);
  ASSERT_EQ(mat(2, 1), 8.0);
  ASSERT_EQ(mat(2, 2), 9.0);
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

TEST(SimpleMatrixConcatenationTest, HorizontalConcatenation) {
    SimpleMatrix<int> mat1{{1, 2}, {3, 4}};
    SimpleMatrix<int> mat2{{5, 6}, {7, 8}};
    SimpleMatrix<int> result = concatenate_horizontal(mat1, mat2);
    EXPECT_EQ(result.rows(), 2);
    EXPECT_EQ(result.cols(), 4);
    EXPECT_EQ(result(0, 0), 1);
    EXPECT_EQ(result(0, 1), 2);
    EXPECT_EQ(result(0, 2), 5);
    EXPECT_EQ(result(0, 3), 6);
    EXPECT_EQ(result(1, 0), 3);
    EXPECT_EQ(result(1, 1), 4);
    EXPECT_EQ(result(1, 2), 7);
    EXPECT_EQ(result(1, 3), 8);
}

TEST(SimpleMatrixConcatenationTest, VerticalConcatenation) {
    SimpleMatrix<int> mat1{{1, 2}, {3, 4}};
    SimpleMatrix<int> mat2{{5, 6}, {7, 8}};
    SimpleMatrix<int> result = concatenate_vertical(mat1, mat2);
    EXPECT_EQ(result.rows(), 4);
    EXPECT_EQ(result.cols(), 2);
    EXPECT_EQ(result(0, 0), 1);
    EXPECT_EQ(result(0, 1), 2);
    EXPECT_EQ(result(1, 0), 3);
    EXPECT_EQ(result(1, 1), 4);
    EXPECT_EQ(result(2, 0), 5);
    EXPECT_EQ(result(2, 1), 6);
    EXPECT_EQ(result(3, 0), 7);
    EXPECT_EQ(result(3, 1), 8);
}

TEST(SimpleMatrixConcatenationTest, MismatchedRowsForHorizontalConcatenation) {
    SimpleMatrix<int> mat1(2, 2);
    SimpleMatrix<int> mat2(3, 2);
    EXPECT_THROW(concatenate_horizontal(mat1, mat2), std::invalid_argument);
}

TEST(SimpleMatrixConcatenationTest, MismatchedColsForVerticalConcatenation) {
    SimpleMatrix<int> mat1(2, 2);
    SimpleMatrix<int> mat2(2, 3);
    EXPECT_THROW(concatenate_vertical(mat1, mat2), std::invalid_argument);
}

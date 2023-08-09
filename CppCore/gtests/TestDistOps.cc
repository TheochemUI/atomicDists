#include <gtest/gtest.h>
#include "../include/DistOps.hpp"
#include "../include/SimpleMatrix.hpp"
using namespace atmdist::types;
using namespace atmdist;

TEST(RowwiseEuclideanDistances, EmptyMatrix) {
  SimpleMatrix<double> mat(0, 0);
  auto result = rowwise_euclidean_distances(mat);
  EXPECT_EQ(result.rows(), 0);
  EXPECT_EQ(result.cols(), 0);
}

TEST(RowwiseEuclideanDistances, SingleRow) {
  SimpleMatrix<double> mat(1, 3, { {1.0, 2.0, 3.0} });
  auto result = rowwise_euclidean_distances(mat);
  EXPECT_EQ(result.rows(), 1);
  EXPECT_EQ(result.cols(), 1);
  EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
}

TEST(RowwiseEuclideanDistances, MultipleRows) {
  SimpleMatrix<double> mat({
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  });
  auto result = rowwise_euclidean_distances(mat);
  EXPECT_EQ(result.rows(), 3);
  EXPECT_EQ(result.cols(), 3);

  // Expected distances:
  // sqrt((1-4)^2 + (2-5)^2 + (3-6)^2) = sqrt(9 + 9 + 9) = 3*sqrt(3)
  // sqrt((1-7)^2 + (2-8)^2 + (3-9)^2) = sqrt(36 + 36 + 36) = 6*sqrt(3)
  EXPECT_DOUBLE_EQ(result(0, 1), 3*std::sqrt(3.0));
  EXPECT_DOUBLE_EQ(result(0, 2), 6*std::sqrt(3.0));
  EXPECT_DOUBLE_EQ(result(1, 2), 3*std::sqrt(3.0));
}

// Additional tests for edge cases, invalid inputs, etc.

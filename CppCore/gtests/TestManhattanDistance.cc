#include "../include/ManhattanDistance.hpp"
#include <gtest/gtest.h>

namespace atmdist::distance {

class ManhattanDistanceTest : public ::testing::Test {
protected:
  ManhattanDistance<double> distance;
};

TEST_F(ManhattanDistanceTest, ZeroDistanceSameVectors) {
  std::vector<double> vec1 = {1.0, 2.0, 3.0};
  std::vector<double> vec2 = {1.0, 2.0, 3.0};

  double result = distance.calculate(vec1, vec2);
  EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(ManhattanDistanceTest, PositiveDistanceDifferentVectors) {
  std::vector<double> vec1 = {1.0, 2.0, 3.0};
  std::vector<double> vec2 = {4.0, 6.0, 8.0};

  double result = distance.calculate(vec1, vec2);
  EXPECT_NEAR(result, 12, 1e-16);
}

TEST_F(ManhattanDistanceTest, ThrowsExceptionDifferentSize) {
  std::vector<double> vec1 = {1.0, 2.0, 3.0};
  std::vector<double> vec2 = {4.0, 6.0};

  EXPECT_THROW(distance.calculate(vec1, vec2), std::invalid_argument);
}

TEST_F(ManhattanDistanceTest, ZeroDistanceEmptyVectors) {
  std::vector<double> vec1 = {};
  std::vector<double> vec2 = {};

  double result = distance.calculate(vec1, vec2);
  EXPECT_DOUBLE_EQ(result, 0.0);
}

} // namespace atmdist::distance

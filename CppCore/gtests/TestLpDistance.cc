#include "../include/LpDistance.hpp"
#include <gtest/gtest.h>
using namespace atmdist::distance;

TEST(LpDistance, SameVectors) {
  std::vector<double> vec = {1.0, 2.0, 3.0};
  LpDistance<double> dist(2); // Euclidean distance
  EXPECT_DOUBLE_EQ(dist(vec, vec), 0.0);
}

TEST(LpDistance, EuclideanDistance) {
  std::vector<double> vec1 = {1.0, 2.0, 3.0};
  std::vector<double> vec2 = {4.0, 5.0, 6.0};
  LpDistance<double> dist(2); // Euclidean distance
  EXPECT_DOUBLE_EQ(dist(vec1, vec2), 3 * std::sqrt(3.0));
}

TEST(LpDistance, ManhattanDistance) {
  std::vector<double> vec1 = {1.0, 2.0, 3.0};
  std::vector<double> vec2 = {4.0, 5.0, 6.0};
  LpDistance<double> dist(1); // Manhattan distance
  EXPECT_DOUBLE_EQ(dist(vec1, vec2), 9.0);
}

TEST(LpDistance, GeneralizedLpDistance) {
  std::vector<double> vec1 = {1.0, 2.0, 3.0};
  std::vector<double> vec2 = {4.0, 5.0, 6.0};
  LpDistance<double> dist(3); // L3 distance
  EXPECT_DOUBLE_EQ(dist(vec1, vec2), std::pow(27 + 27 + 27, 1.0/3.0));
}

TEST(LpDistance, InvalidP) {
  EXPECT_THROW(LpDistance<double>(0), std::invalid_argument);
  EXPECT_THROW(LpDistance<double>(-1), std::invalid_argument);
}

TEST(LpDistance, DifferentSizeVectors) {
  std::vector<double> vec1 = {1.0, 2.0};
  std::vector<double> vec2 = {1.0, 2.0, 3.0};
  LpDistance<double> dist(2);
  EXPECT_THROW(dist(vec1, vec2), std::invalid_argument);
}

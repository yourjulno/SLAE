//
// Created by julia on 12.02.23.
//

#include <gtest/gtest.h>
#include "../src/three_diagonal.hpp"
#include "../src/solve/TreeDiagonalSolve.hpp"

TEST(TESTTRIDIAGONAL, FIRST){
std::vector<SLAE::line<double>> example = {{0,2,3},{6,3,9},{2,5,2},{4,3,0}};
std::vector<double> free = {21.0, 69.0, 34.0, 22.0};
std::vector<double> x = {2.9, 4.8, 3.8, 1.6};


ThirdDiagonalMatrix<double> first(example);

std::vector <double> solve = solveTridiagonal(first, free);

for (int i = 0; i < solve.size(); i++){
ASSERT_NEAR(solve[i], x[i], 0.01);
}
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


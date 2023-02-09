#include <iostream>
#include <cmath>
#include <gtest/gtest.h>
#include "ThreeDiagonalMatrix/three_diagonal.h"
#include "solve/TreeDiagonalSolve.h"
using namespace std;

TEST(TESTTRIDIAGONAL, FIRST){
    vector<line> example = {{2, -1, 0}, {5, 4, 2}, {0, 1, -3}};
    vector<double> free = {3,6,2};
    vector<double> x = {1.49, -0.026, -0.67};


    ThirdDiagonalMatrix first(example);

    vector <double> solve = SolveOfTridiagonal::find_q_p(first, free);

   for (int i = 0; i < solve.size(); i++){
       ASSERT_NEAR(solve[i], x[i], 0.01);
   }
}

int main()
{

//  return RUN_ALL_TESTS();
}

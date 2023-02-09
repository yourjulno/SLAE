#include <iostream>
#include <cmath>
#include <gtest/gtest.h>
#include "ThreeDiagonalMatrix/three_diagonal.hpp"
#include "solve/TreeDiagonalSolve.hpp"
using namespace std;

//TEST(TESTTRIDIAGONAL, FIRST){
//    vector<line<double>> example = {{0,2,3},{6,3,9},{2,5,2},{4,3,0}};
//    vector<double> free = {21.0, 69.0, 34.0, 22.0};
//    vector<double> x = {3.0, 5.0, 4.0, 2.0};
//
//
//    ThirdDiagonalMatrix<double> first(example);
//
//    vector <double> solve = SolveOfTridiagonal::find_q_p(first, free);
//
//   for (int i = 0; i < solve.size(); i++){
//       ASSERT_NEAR(solve[i], x[i], 0.01);
//   }
//}

int main()
{
    vector<line<double>> example = {{1,2, 0},{6,3,9},{0,5,2},{4,3,0}};
    vector<double> free = {21.0, 69.0, 34.0, 22.0};
    vector<double> x = {3.0, 5.0, 4.0, 2.0};


    ThirdDiagonalMatrix<double> first(example);

    vector <double> solve = find_q_p(first, free);
    for (auto i:solve){
        cout << i << " ";
    }
//  return RUN_ALL_TESTS();
}

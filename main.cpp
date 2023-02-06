#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "ThreeDiagonalMatrix/three_diagonal.h"
#include "solve/TreeDiagonalSolve.h"
using namespace std;

TEST(TestGroupName, Subtest_1) {
  ASSERT_TRUE(1 == 1);
}

TEST(TestGroupName, Subtest_2) {
  ASSERT_FALSE('b' == 'b');
  cout << "continue test after failure" << endl;
}

int main(int argc, char **argv)
{
    vector<line> example = {{2, -1, 0}, {5, 4, 2}, {0, 1, -3}};
    vector<double> free = {3,6,2};
    vector<double> x = {1, -1};
    // Arrange
    ThirdDiagonalMatrix first(example);

    vector <double> solve = SolveOfTridiagonal::find_q_p(first, free);
    for (auto& i:solve){
        std::cout<<i << " ";
    }
//  ::testing::InitGoogleTest(&argc, argv);
//
//  return RUN_ALL_TESTS();
}
//TEST(TestGroupName, increment_by_5)
//{
//    vector<double> example = {2, 1, 5, 3};
//    vector<double> free = {1, 2};
//    vector<double> x = {1, -1};
//    // Arrange
//     ThirdDiagonalMatrix first(example);
//
//     vector <double> solve = SolveOfTridiagonal::find_q_p(first, free);
//
//
//    // Act
////    string value = mc.GetId();
//
//    // Assert
////    EXPECT_STREQ(value.c_str(), "root"); // строки сравнивают с _STREQ
//}
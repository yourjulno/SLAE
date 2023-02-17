//
// Created by julia on 13.02.23.
//

#include <gtest/gtest.h>
#include "../src/sparse/sparse.hpp"


TEST(SPARSE, FIRST){
    std::set<Tri<double>> example = {{0,0,1},{0,1,2},
                                     {0,3,3},{1,2,4}, {2, 1, 1},
                                     {2, 3, 11}};
    std::vector<double> free = {0, 0, 0, 1};
    std::vector<double> x = {3, 0, 11};


    CSR<double> first(example, 4, 3);
    auto val = first(2, 3);
    auto val2 = first(0, 2);
    auto val_1 = first * free;
    auto v = first(0, 3);
    ASSERT_EQ(3, v);
    ASSERT_EQ(0, val2);
    ASSERT_EQ(11, val);
    ASSERT_EQ(x, val_1);
}
TEST(SPARSE_SECOND_Test, SECOND){
    std::set<Tri<double>> example = {{0,0,1},{0,1,2},
                                     {0,3,3},{1,2,4}, {2, 1, 1},
                                     {2, 3, 11}, {0, 0, 0}};
    std::vector<double> free = {0, 0, 0, 1};
    std::vector<double> x = {3, 0, 11, 0};
    CSR<double> first(example, 4, 4);
    auto val_1 = first * free;
    ASSERT_EQ(val_1, x);
}
//TEST(SPARSE_THIRD_Test, THIRD){
//    std::set<Tri<double>> example = {{0,1,2},
//                                     {0,3,3},{1,2,4}, {2, 1, 1},
//                                     {2, 3, 11}};
//    std::vector<double> free = {0, 0, 0, 1, 0};
//    std::vector<double> x = {0, 0, 11, 0, 0};
//    CSR<double> first(example, 4, 5);
//    auto val_1 = first * free;
//    ASSERT_EQ(val_1, x);
//}

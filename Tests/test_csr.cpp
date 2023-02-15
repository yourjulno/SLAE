//
// Created by julia on 13.02.23.
//

#include <gtest/gtest.h>
#include "../src/sparse/sparse.h"
#include "../src/sparse/multiply_sparse_vector.hpp"

TEST(SPARSE, FIRST){
    std::set<Tri<double>> example = {{0,0,1},{0,1,2},
                                     {0,3,3},{1,2,4}, {2, 1, 1},
                                     {2, 3, 11}};
    std::vector<double> free = {0, 0, 0, 1};
    std::vector<double> x = {3, 0, 11};


    CSR<double> first(example, 4, 3);
    auto val = first(2, 3);
    auto val2 = first(0, 2);
    auto val_1 = MultiplySparseVec(first, free);
    auto v = first(0, 3);
    ASSERT_EQ(3, v);
    ASSERT_EQ(0, val2);
    ASSERT_EQ(11, val);
    ASSERT_EQ(x, val_1);
}

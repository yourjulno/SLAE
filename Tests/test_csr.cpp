//
// Created by julia on 13.02.23.
//

#include <gtest/gtest.h>
#include "../src/sparse.h"


TEST(SPARSE, FIRST){
    std::set<Tri<double>> example = {{0,0,1},{0,1,2},
                                     {0,3,3},{1,2,4}, {2, 1, 1},
                                     {2, 3, 11}};
    std::vector<double> free = {21.0, 69.0, 34.0, 22.0};
    std::vector<double> x = {2.9, 4.8, 3.8, 1.6};


    CSR<double> first(example, 4, 3);
    auto val = first.operator()(2, 3);
    ASSERT_EQ(11, val);
}

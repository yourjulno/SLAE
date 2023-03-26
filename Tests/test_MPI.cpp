//
// Created by julia on 04.03.23.
//


#include <gtest/gtest.h>
#include "../src/sparse/sparse.hpp"
#include "../src/solve/MPI.hpp"

TEST(MPI, FIRST){
    std::set<Tri<double>> example = {{0,0,100},{0,1,0.2},
                                     {1,0,0.2},{1,1,100}};
    std::vector<double> free = {1000, 999};
    std::vector<double> x = {0,0};


    CSR<double> first(example, 2, 2);
    auto res = MPI(first, x,free, 0.001, 0.002);
    auto val = first(2, 3);
    auto val2 = first(0, 2);
    auto val_1 = first * free;
    auto v = first(0, 3);
    ASSERT_EQ(3, v);
    ASSERT_EQ(0, val2);
    ASSERT_EQ(11, val);
    ASSERT_EQ(x, val_1);

    std::set<Tri<double>> example2 = {{0,0,10},{0,1,1},
                                     {1,0,1},{1,1,7},{1,2, 0.1}, {2,2,1} };
    std::vector<double> free2 = {20, 30, 1};
    std::vector<double> x2 = {0,0, 0};
    std::vector<double> counts;
    std::vector<double> taus = {0.02, 0.04, 0.06, 0.08, 0.10};
    CSR<double> first2(example2, 3, 3);

    auto res2 = MPI(first2, x2,free2, pow(10, -12), 0.001);

}


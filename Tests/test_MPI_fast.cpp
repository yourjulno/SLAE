//
// Created by julia on 13.03.23.
//
#include <gtest/gtest.h>
#include "../src/sparse/sparse.hpp"
#include "../src/solve/MPI_fast.hpp"
#include "../src/solve/MPI.hpp"

TEST(FIRST, MPI_FAST){
    std::set<Tri<double>> example = {{0,0,10},{0,1,1},
                                     {1,0,1},{1,1,7},{1,2, 0.1}, {2,2,1} };
    std::vector<double> free = {1000, 999};
    std::vector<double> x = {0,0};
    CSR<double> first(example, 2, 2);
    auto res_from_fast = MPI_fast(first, x,free, pow(10, -5),8);
    auto res_from_slow =
            MPI(first, x, free, pow(10, -5),0.001);

    ASSERT_GT(res_from_slow.second, res_from_fast.second);
}

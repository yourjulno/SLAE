//
// Created by julia on 04.03.23.
//

#include <gtest/gtest.h>
#include "../src/sparse/sparse.hpp"
#include "../src/solve/GZ.hpp"
#include "../src/solve/MPI.hpp"

TEST(iteration, GZ_fast_){
    std::set<Tri<double>> example2 = {{0,0,10},{0,1,1},
                                      {1,0,1},{1,1,7},{1,2, 0.1}, {2,2,1} };
    std::vector<double> free2 = {20, 30, 1};
    std::vector<double> x = {0,0, 0};


    CSR<double> first2(example2, 3, 3);
    auto res = GZFast(first2, x, free2, 1e-5, 0.233);
    std::cout << res.second;

}

TEST(iteration_GZ_fast__Test, GZFast_){
    std::set<Tri<double>> example2 = {{0,0,10},{0,1,1},
                                      {1,0,1},{1,1,7},{1,2, 0.1}, {2,2,1} };
    std::vector<double> free2 = {20, 30, 1};
    std::vector<double> x = {0,0, 0};


    CSR<double> first2(example2, 3, 3);
    double lambda_max = max_lambda(first2);
    double precision = 1e-12;
    auto res_from_GZ_fast = GZFast(first2, x, free2, precision, lambda_max);
    auto res_from_GZ_slow = GZ(first2, x, free2, precision);
    ASSERT_GE(res_from_GZ_fast.second, res_from_GZ_slow.second);
}
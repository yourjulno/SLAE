//
// Created by julia on 07.04.23.
//
//
// Created by julia on 07.04.23.
//
#include <gtest/gtest.h>
#include "../src/dense_matrix.hpp"
#include "../src/solve/Descent.hpp"
#include "../src/solve/CG.hpp"

TEST(CG, FIRST){
    std::set<Tri<double>> example = {{0, 0, 12}, {0, 1, 17}, {0, 2, 3}, {1, 0, 17}, {1, 1, 15825}, {1, 2, 28},
                                     {2, 0, 3}, {2, 1, 28}, {2, 2, 238}};
    CSR<double> first {example, 3, 3};
    // Initial approximation
    std::vector<double> x0(3, 1);
    // b vector
    std::vector<double> b {1, 2, 3};
    // Precise solution
    std::vector<double> r {0.0804084117, 0.0000194982, 0.0115891967};
    double accuracy = 1e-12;
    // Result w/ SIM Chebyshev acceleration
    size_t R = 8;
    double eig_min = 11.8;
    double eig_max = 15825.1;
    auto resFast = CG(first, x0, b,  accuracy);
    std::cout << resFast.second.second;
    // Result w/ Steepest descent method
    auto res = Descent_method(first, x0, b, accuracy);
    // Testing results
    // std::cout << res.second.second;
    for (int i = 0; i < r.size(); ++i) {
        ASSERT_NEAR(res.first[i], r[i], 1e-10);
        ASSERT_NEAR(resFast.first[i], r[i], 1e-10);
    }
}

//нет диагонального преобладания
TEST(CG, second_test) {
    std::set<Tri<double>> example{{0, 0, 99.}, {0, 1, 12.}, {0, 2, 10.},
                                    {1, 0, 8.}, {1, 1, 10.9}, {1, 2, 0.1},
                                    {2, 0, 5.}, {2, 1, 4.}, {2, 2, 70.}};
    CSR<double> first(example, 3, 3);

    double tolerance = 1e-12;
    std::vector<double> b = {1., 5., 4.};
    std::vector<double> x = {0.01, 1.2, -0.14};
    std::vector<double> right_solve = {-0.0535106, 0.497691, 0.0325256};

    auto res_from_CG = CG<double>(first, x, b, tolerance);

    for (int i = 0; i < x.size(); ++i) {
        ASSERT_NEAR(res_from_CG.first[i], right_solve[i], 1e-6);
    }
}
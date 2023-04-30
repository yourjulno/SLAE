//
// Created by julia on 30.04.23.
//
#include <gtest/gtest.h>
#include "../src/dense_matrix.hpp"

#include "../src/solve/Descent.hpp"
#include "../src/solve/MPI.hpp"
#include "../src/solve/GMRES.hpp"

TEST(GMRES, FIRST){

    std::vector<double> a = {1, 2, 3, 4};
    std::vector<double> b = {1, 0, 3};
    //auto val_1 = a * b;
    auto first = DenseMatrix<double>(a, 2, 2);
    auto val_2 = first(1, 1);
    std::vector<double> col = {2, 4};
    auto col_from_matr = first[1];
    //
    const auto n = 4;
    std::set<Tri<double>> example2 = {{0,0,1},{0,1,2},
                                      {0,3,3},{1,2,4}, {2, 1, 1},
                                      {2, 3, 11}, {0, 0, 0}};
    std::set<Tri<double>> example = {{0, 0, 12}, {1, 1, 14.}, {2, 2, 16.}, {3, 3, 18}};

    CSR<double> first_(example2, n, n);
    CSR<double> second(example, n, n);
    std::vector<double> free(n, 6);
    std::vector<double> x(n, 0);

    auto res_from_GMRES = GMRES(first_, x, free, n);
    auto res_from_GMRES_ = GMRES(second, x, free, n);
    std::cout << lenght(res_from_GMRES) << " " << lenght(res_from_GMRES_);
    ASSERT_EQ(4, val_2);
    ASSERT_EQ(col, col_from_matr);
}

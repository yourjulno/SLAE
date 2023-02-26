//
// Created by julia on 20.02.23.
//

#include <gtest/gtest.h>
#include "../src/dense_matrix.hpp"
#include "../src/solve/Householder.hpp"
#include <limits>

TEST(DENSE, FIRST){

std::vector<double> a = {1, 2, 3, 4};
std::vector<double> b = {1, 0, 3};
//auto val_1 = a * b;
auto first = DenseMatrix<double>(a, 2, 2);
auto val_2 = first(1, 1);
std::vector<double> col = {2, 4};
auto col_from_matr = first[1];
ASSERT_EQ(4, val_2);
ASSERT_EQ(col, col_from_matr);
}

TEST(DENSE, SECOND){

    std::vector<double> a = {12, -51, 4, 6, 167, -68, -4, 24, -41};
    std::vector<double> b = {13, 7, 4};
//auto val_1 = a * b;
    auto first = DenseMatrix<double>(a, 3, 3);
    auto R = Householder_alg(first);
    std::vector<double> real_R = {-14, -21, 14, 0, -175, 70, 0, 0, -35};
    auto solve_from_func = R.getData();
    auto col_from_matr = first[0];
    for (int i = 0; i < real_R.size(); i++){
        ASSERT_NEAR(real_R[i], solve_from_func[i], 1000*std::numeric_limits<double>::epsilon());
    }

}

//
// Created by julia on 20.02.23.
//

#include <gtest/gtest.h>
#include "../src/dense_matrix.hpp"
#include "../src/solve/Householder.hpp"
#include "../src/solve/Descent.hpp"
#include "../src/solve/MPI.hpp"
#include "../src/solve/GMRES.hpp"
#include <limits>
#include <ctime>

TEST(DENSE, FIRST){

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
std::vector<double> free(n, 6);
std::vector<double> x(n, 0);

auto res_from_arnoldi = GMRES(first_, x, free, n);
std::cout << lenght(res_from_arnoldi);
ASSERT_EQ(4, val_2);
ASSERT_EQ(col, col_from_matr);
}

TEST(DENSE, SECOND){

    std::vector<double> a = {12, -51, 4, 6, 167, -68, -4, 24, -41};
    std::vector<double> b = {-4, 24, -41};
//auto val_1 = a * b;
    auto first = DenseMatrix<double>(a, 3, 3);
    auto R = Householder_alg_R(first);
    std::vector<double> real_R = {-14, -21, 14, 0, -175, 70, 0, 0, -35};
    auto solve_from_func = R.first;
    std::vector<double> real_Q = {-0.85714286,  0.39428571,  0.33142857, -0.42857143, -0.90285714, -0.03428571, 0.28571429, -0.17142857,  0.94285714};
    auto Q = R.second;
    auto row_from_matr = first.getRow(2);
    for (int i = 0; i < real_R.size(); i++){
        ASSERT_NEAR(real_R[i], solve_from_func[i], 1000*std::numeric_limits<double>::epsilon());
    }
    ASSERT_EQ(b, row_from_matr);
    for (int i = 0; i < real_R.size(); i++){
        ASSERT_NEAR(real_Q[i], Q[i], 0.00001);
    }


};

TEST(DENSE, THIRD){
    std::vector<double> a(1000000);
    for (int i = 0; i < 1000000; i++){
        a[i] = static_cast<double>(i);
    }
//    std::vector<double> a = {12, -51, 4, 6, 167, -68, -4, 24, -41};
    std::vector<double> b = {-4, 24, -41};
//auto val_1 = a * b;
    auto first = DenseMatrix<double>(a, 1000, 1000);
    ::srand(time(NULL));
    clock_t start = clock();
    auto R = Householder_alg_R(first);
    clock_t end = clock();
    ASSERT_FLOAT_EQ(0.1, static_cast<double>(end - start)/CLOCKS_PER_SEC);
    std::vector<double> real_R = {-14, -21, 14, 0, -175, 70, 0, 0, -35};
    auto solve_from_func = R.first;
    std::vector<double> real_Q = {-0.85714286,  0.39428571,  0.33142857, -0.42857143, -0.90285714, -0.03428571, 0.28571429, -0.17142857,  0.94285714};
    auto Q = R.second;
    auto row_from_matr = first.getRow(2);
//    for (int i = 0; i < real_R.size(); i++){
//        ASSERT_NEAR(real_R[i], solve_from_func[i], 1000*std::numeric_limits<double>::epsilon());
//    }
//    ASSERT_EQ(b, row_from_matr);
//    for (int i = 0; i < real_R.size(); i++){
//        ASSERT_NEAR(real_Q[i], Q[i], 0.00001);
//    }


}




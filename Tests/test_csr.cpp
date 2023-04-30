//
// Created by julia on 13.02.23.
//

#include <gtest/gtest.h>
#include "../src/dense_matrix.hpp"
#include "../src/sparse/sparse.hpp"
#include "../src/solve/Descent.hpp"
#include "../src/solve/MPI.hpp"
#include "../src/solve/GaussSeidel.hpp"
#include "../src/solve/CG.hpp"
#include "../src/solve/BiSG.hpp"
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
TEST(BiSG, SECOND){
    const int n = 4;

    std::set<Tri<double>> example = {{0, 0, 12}, {1, 1, 14.}, {2, 2, 16.}, {3, 3, 18}};

    CSR<double> first(example, n, n);
    std::vector<double> free(n, 6);
    std::vector<double> x(n, 0);


    auto res_from_bisg = BiSG(first, x, free, 4);
    std::cout << lenght(res_from_bisg);
}
TEST(DESCENT_, FIRST){
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
    auto resFast = MPI_fast(first, x0, b,  accuracy, R, eig_max, eig_min);
    std::cout << resFast.second.second << " ";
    // Result w/ Steepest descent method
    auto res = Descent_method(first, x0, b, accuracy);
    std::cout << res.second.second;
    // Testing results
    // std::cout << res.second.second;
    for (int i = 0; i < r.size(); ++i) {
        ASSERT_NEAR(res.first[i], r[i], 1e-10);
        ASSERT_NEAR(resFast.first[i], r[i], 1e-10);
    }
}


TEST(RK, FIRST____){

    const auto n = 289;
    const auto L = 17;
    std::set<Tri<double>> example;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i == j){
                example.insert({i, j, 19 * 2});
            }
            if (j == i + 1 || i == j + 1){
                example.insert({i, j, 7});
            }
            if (j == L + i || i == L + j){
                example.insert({i, j, 7});
            }

        }
    }
    CSR<double> first(example, n, n);
    std::vector<double> free(n, 4);
    std::vector<double> x(n, 0);
    const auto tolerance = 1e-13;
    const int R = 8;
    const auto lambda_max = max_lambda(first);
    const auto tao = 1 / max_lambda(first);
    const auto lambda_min = 2 * (19 - 2 * 7 * std::cos(M_PI / (17 + 1)));
    //градиентный спуск (мпи)

    auto res_from_MPI = MPI(first, x,free, tolerance, tao);
    auto res_from_optional_parament = Descent_method(first, x, free, tolerance);
    auto res_from_chebyshev_mpi = MPI_fast(first, x, free, tolerance, R, lambda_max, lambda_min);
    auto res_from_symmetrical = GZFast(first, x, free, tolerance, lambda_max);

}
TEST(GRAD, LAMBDA){
    const auto n = 289;
    const auto L = 17;
    std::set<Tri<double>> example;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i == j){
                example.insert({i, j, 19 * 2});
            }
            if (j == i + 1 || i == j + 1){
                example.insert({i, j, 7});
            }
            if (j == L + i || i == L + j){
                example.insert({i, j, 7});
            }

        }
    }
    CSR<double> first(example, n, n);
    std::vector<double> free(n, 4);
    std::vector<double> x(n, 0);
    const auto tolerance = 1e-13;
    const int R = 8;
     auto lambda_max = 2 * (19 + 2 * 7 * std::cos(M_PI / (17 + 1)));
    std::cout << lambda_max;
     auto lambda_min = 2 * (19 - 2 * 7 * std::cos(M_PI / (17 + 1)));
    const auto delta = 1;
    const auto tao = 1 / max_lambda(first);
    std::ofstream outfile;
    outfile.open("/home/julia/CLionProjects/SLAE/src/solve/MPI_fast.txt",
                 std::ofstream::out | std::ofstream::app);
    for (auto i = 1 ; i < 50; i++) {

        auto res_from_chebyshev_mpi = MPI_fast(first, x, free, tolerance, R, lambda_max, lambda_min).second.second;
        outfile << lambda_max << " " << res_from_chebyshev_mpi << std::endl;
        lambda_max +=0.5;

        //auto red = MPI_fast(first, x, free, tolerance, R, lambda_max - i, lambda_min);
    }
}

TEST(test_2, kr){

    const auto n = 4;

    std::set<Tri<double>> example = {{0, 0, 12}, {1, 1, 14.}, {2, 2, 16.}, {3, 3, 18}};

    CSR<double> first(example, n, n);
    std::vector<double> free(n, 6);
    std::vector<double> x(n, 0);
    const auto tolerance = 1e-13;
    const int R = 8;

    const auto tao = 2 * 0.9 / max_lambda(first);
    const auto lambda_max = max_lambda(first);

    const auto lambda_min = 12.;
    const auto opt_param = 2 / (lambda_max + lambda_min);
    //градиентный спуск (мпи)

    auto res_from_MPI = MPI(first, x,free, tolerance, opt_param);
   // auto res_from_optional_parament = Descent_method(first, x, free, tolerance);
    //auto res_from_chebyshev_mpi = MPI_fast(first, x, free, tolerance, R, lambda_max, lambda_min);
    //auto res_from_symmetrical = GZFast(first, x, free, tolerance, lambda_max);
   // auto res_from_sg = CG(first, x, free, tolerance);


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

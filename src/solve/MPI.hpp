//
// Created by julia on 04.03.23.
//

#ifndef SLAE_MPI_HPP
#define SLAE_MPI_HPP
#include "../sparse/sparse.hpp"
#include "../dense_matrix.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
//x - начальное приближение
template <class T>
std::pair<std::vector<T>, std::pair<std::vector<T>, int>> MPI(const CSR<T> &A, const std::vector<T> &x, const std::vector<T> &b, T tolerance, T tau){
    std::vector<T> x_ = x;
    std::vector<T> solve = A * x - b;
    int count = 0;
    std::ofstream outfile;
    outfile.open("/home/julia/CLionProjects/SLAE/src/solve/MPI_fast_opt.txt",
                 std::ofstream::out | std::ofstream::app);

    outfile << x_[0] << " " << x_.back() << std::endl;
    while (lenght(solve) > tolerance){
        x_ = x_ - tau * solve;
        solve =  A * x_ - b;

        count++;

            outfile << x_[0] << " " <<x_.back() << std::endl;


    }
    std::pair<std::vector<T>,int> k = {solve, count};
    return std::make_pair(x_,k);
}

//chebyshev acceleration
template <class T>
T max_lambda(const CSR<T> &A){
    const std::vector<T> r_0(A.getCol(), 1);
    std::vector<T> r_k;
    r_k = r_0;
    T lambda;
    for (std::size_t i = 0; i < 50; i++){
        std::vector<T> c = A * r_k;
        r_k = c / lenght(c);
        lambda = r_k * c / (r_k * r_k);
    }
    return lambda;
}

template <class T>
std::pair<std::vector<T>, std::pair<std::vector<T>, int>> MPI_fast(const CSR<T> &A, const std::vector<T> &x,
                                                const std::vector<T> &b, T tolerance, const int n, const T lambda_max, const T lambda_min){
    const int r = 3;
    const T pi = M_PI;
    std::ofstream outfile;
    outfile.open("/home/julia/CLionProjects/SLAE/src/solve/MPI_fast.txt",
                 std::ofstream::out | std::ofstream::app);
    outfile << x[0] << " " << x.back() << std::endl;
    std::ofstream outfile_;
    outfile_.open("/home/julia/CLionProjects/SLAE/src/solve/MPI_fast_opt.txt");
    const T x0 = cos(pi / (2 * n));
    T sin_betta = sin(pi / (2 * n));
    const T cos_alpha = cos(pi / n);
    const T sin_alpha = sin (pi / n);
    std::vector<T> r_nev = A * x - b;
    std::vector<T> z(n);
    z[0] = x0;



    for (std::size_t i = 1; i < n; i++){
        z[i] = z[i - 1] * cos_alpha - sin_betta * sin_alpha;
        sin_betta = z[i - 1] * sin_alpha + sin_betta * cos_alpha;
        z[i - 1] = (lambda_max - lambda_min) / 2 * z[i - 1] + (lambda_max + lambda_min)/2;

    }

    std::vector<T> x_ = x;
    // form tao
    //std:: cout << lambda_max;
//
//    for (std::size_t i = 0; i < n; i++){
//        z.push_back((lambda_max - lambda_min) / 2 * solve[i] + (lambda_max + lambda_min)/2);
//    }

    std::vector<std::size_t> numbers(n);

    numbers[0] = 0;
    numbers[n/2] = 1;

    for (std::size_t r_now = 1; r_now < r; r_now++){
        for (std::size_t j = 0; j < n; j = j + static_cast<std::size_t>(std::pow(2,r - r_now))){
            numbers[j + static_cast<std::size_t>(std::pow(2, r - r_now - 1))] = static_cast<std::size_t>(std::pow(2, r_now + 1))
                                                                                - 1 - numbers[j];
        }
    }
    std::size_t count = 0;
    while (lenght(r_nev) >= tolerance){

        for (std::size_t i = 0; i < n; i++){

            r_nev = b -  A * x_;
            x_ = x_ + 1/z[numbers[i]] * r_nev;
            //std::cout << lenght(x_) << " ";

//            for (auto k : solve){
//                std:: cout << k << " ";
//            }
//            std:: cout << std::endl;
            count++;
            //std:: cout << lenght(solve) << " ";
            //outfile << x_[0] << " " << x_.back() << std::endl;
            outfile << x_[0] << " " << x_.back() << std::endl;
            if (lenght(r_nev) <  tolerance)
                break;
        }

    }
    //outfile<<"\n";

    std::pair<std::vector<T>,int> k = {r_nev, count};
    return std::make_pair(x_,k);
}
#endif //SLAE_MPI_HPP

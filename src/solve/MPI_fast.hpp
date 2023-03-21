//
// Created by julia on 11.03.23.
//

#ifndef SLAE_MPI_FAST_HPP
#define SLAE_MPI_FAST_HPP

#include "../sparse/sparse.hpp"
#include "../dense_matrix.hpp"

template <class T>
T max_lambda(const CSR<T> &A){
    const std::vector<T> r_0(A.getCol(), 1);
    std::vector<T> r_k;
    r_k = r_0;
    T lambda;
    for (std::size_t i = 0; i < 40; i++){
        std::vector<T> c = A * r_k;
        r_k = c / lenght(c);
        lambda = r_k * c / (r_k * r_k);
    }
    return lambda;
}

template <class T>
std::pair<std::vector<T>, std::size_t> MPI_fast(const CSR<T> &A, const std::vector<T> &x,
                        const std::vector<T> &b, T tolerance, const int n){
    const int r = 3;
    const T pi = 3.14;
    T x0 = cos(pi / (2 * n));
    T sin_betta = sin(pi / (2 * n));
    T cos_alpha = cos(pi / n);
    T sin_alpha = sin (pi / n);
    std::vector<T> solve_ = A * x - b;
    std::vector<T> solve;
    solve.reserve(n);
    solve.push_back(x0);

    for (std::size_t i = 1; i < n; i++){
        solve.push_back(solve[i-1] * cos_alpha - sin_betta * sin_alpha);
        sin_betta = solve[i] * sin_alpha + sin_betta * cos_alpha;
    }

    std::vector<T> x_ = x;
    // form tao

    std::vector<T> z;
    z.reserve(n);

    const T lambda_min = 0.5;
    const T lambda_max = max_lambda(A);

    for (std::size_t i = 0; i < n; i++){
        z.push_back((lambda_max - lambda_min) / 2 * solve[i] + (lambda_max + lambda_min)/2);
    }

    std::vector<int> numbers(n);

    numbers[0] = 0;
    numbers[n/2] = 1;

    for (std::size_t r_now = 1; r_now < r; r_now++){
        for (std::size_t j = 0; j < n; j = j + pow(2,r - r_now)){
            numbers[j + pow(2, r - r_now - 1)] = pow(2, r_now + 1)
                    - 1 - numbers[j];
        }
    }
    std::size_t count = 0;
    while (lenght(solve_) > tolerance){

        for (std::size_t i = 0; i < n; i++){
            x_ = x_ - 1/z[numbers[i]] * solve_;
            solve_ =  A * x_ - b;
            count++;
        }
    }

    std::pair<std::vector<T>, std::size_t> k = {solve_, count};
    return k;
}


#endif //SLAE_MPI_FAST_HPP

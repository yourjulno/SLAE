//
// Created by julia on 04.03.23.
//

#ifndef SLAE_GZ_HPP
#define SLAE_GZ_HPP
#include "../sparse/sparse.hpp"
#include "../dense_matrix.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
template <class T>
std::pair<std::vector<T>,int> GZ(const CSR<T> &A, const std::vector<T> &x, const std::vector<T> b,T tolerance){
    std::vector<T> solve = A * x - b;
    std::vector<T> x_ = x;

    int count = 0;
    T res;
    while (lenght(solve) > tolerance){

        for (int i = 0; i < A.getCol(); i++){
            res = 0;
            for (int j = A.getMatrRows(i); j < A.getMatrRows(i + 1); j++) {

                if (i != A.getColns(j)) {
                    res = res + A.getValues(j)*x_[A.getColns(j)];
                }
                else
                    continue;
            }
            x_[i] = (b[i] - res)/A(i, i);
        }
        solve =  A * x_ - b;
        count++;

    }


    std::pair<std::vector<double>, int> k = {solve, count};
    return k;
}

template <class T>
std::vector<T> iter_for_GZ(const CSR<T> &A, const std::vector<T> &x, const std::vector<T> &b){
    std::vector<T> x_ = x;
    T res;
    //0.5
    for (int i = 0; i < A.getCol(); i++){
        res = 0;
        T d;
        for (int j = A.getMatrRows(i); j < A.getMatrRows(i + 1); j++) {

            if (i != A.getColns(j)) {
                res = res + A.getValues(j)*x_[A.getColns(j)];
            }
            else
                d = A(i, i);
        }
        x_[i] = (b[i] - res)/d;
    }
    //1
    for (int i = A.getCol() - 1; i >= 0; i--){
        res = 0;
        T d;
        for (int j = A.getMatrRows(i); j < A.getMatrRows(i + 1); j++) {

            if (i != A.getColns(j)) {
                res = res + A.getValues(j)*x_[A.getColns(j)];
            }
            else
                d = A(i, i);
        }
        x_[i] = (b[i] - res)/d;
    }
    return x_;
}

template <class T>
std::pair<std::vector<T>, std::size_t> GZFast(const CSR<T> &A, const std::vector<T> &x,
                                      const std::vector<T> &b, T tolerance, T ro){


    std::vector<T> y0 = x;
    std::vector<T> y_1 = iter_for_GZ(A, y0, b);

    std::vector<T> y(x.size());
    std::vector<T> solve = A * y_1 - b;

    T nu0 = 1;
    T nu1 = 1 / ro;
    int count = 0;
    T res;
    T temp;

    while (lenght(solve) > tolerance){

        y_1 = iter_for_GZ(A, y_1, b);
        y = 2 * nu1 / ro * y_1 - nu0 * y0;
        nu0 = 2 / ro * nu1 - nu0;
        y = y / nu0;

        y0 = y_1;
        y_1 = y;

        std::swap(nu0, nu1);


        solve = A * y - b;
        count++;
    }

    std::pair<std::vector<double>, int> k = {solve, count};
    return k;
}

#endif //SLAE_GZ_HPP

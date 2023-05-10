//
// Created by julia on 30.04.23.
//

#ifndef SLAE_BISG_HPP
#define SLAE_BISG_HPP
#include "../sparse/sparse.hpp"
#include "../dense_matrix.hpp"

template <class T>
std::vector<T> BiSG(const CSR<T> &A, const std::vector<T> &x_0, const std::vector<T> &b, const int m, T tolerance){

    std::vector<T> r_0 = A * x_0 - b;
    std::vector<T> x = x_0;

    std::vector<T> p_= r_0;
    std::vector<T> p = r_0;
    std::vector<T> r_ = r_0;
    std::vector<T> r = r_0;
    T q = r_ * r_0 / (r_ * (A * p));
    std::vector<T> z, z_;

    T ro = r_0 * r_0;
    T ro_;

    T theta, theta_;
    for (std::size_t i = 1; i <= 60; ++i){
        ro_ = ro;
        ro = r_ * r;
        if (ro < tolerance) break;
        theta = ro / ro_;
        p = r + theta * p;
        p_ = r_ + theta * p_;
        z = A * p;
        z_ = A.transpose() * p_;
        auto l = A.transpose();
        q = ro / (p_ * z);
        x = x - q * p;
        r = r - q * z;
        r_ = r_ - q * z_;
        std:: cout << i << " ";
        //std::cout << lenght(r) << ' ';
    }
    return x;
}
#endif //SLAE_BISG_HPP

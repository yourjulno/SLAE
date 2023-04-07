//
// Created by julia on 07.04.23.
//

#ifndef SLAE_CG_HPP
#define SLAE_CG_HPP

#include "../sparse/sparse.hpp"
#include "../dense_matrix.hpp"

template <class T>
std::pair<std::vector<T>, std::pair<std::vector<T>, int>> CG(const CSR<T> &A, const std::vector<T> &x,
                                                             const std::vector<T> &b, T tolerance){
    std::vector<T> x_ = x;
    std::vector<T> r = A * x - b;
    std::vector<T> Ad;
    std::vector<T> d = r;
    double alpha;
    double dr;
    int count = 0;
    while (lenght(r) > tolerance) {

        for (int i = 0; i < x.size(); ++i) {
            if (!iszero(lenght(r))) {
                Ad = A * d;

                dr = d * r;

                alpha = dr / (d * Ad);
                //Ax_(i+1) = Ax_i - A * alpha *d
                //Ax_(i+1) - b = Ax_i - b - A * alpha *d
                //r_(i+1) = r_(i) - A * alpha * d
                x_ = x_ - alpha * d;

                r = r - alpha * Ad;
                d = r + (r * r / dr) * d;


                count++;
            } else {
                //return std::make_pair<std::vector<T>, int>{std::pair<std::vector<T>,int>{r, count}};
                std::pair<std::vector<T>, int> k = {r, count};
                return std::make_pair(x_, k);
            }
        }
    }
    std::pair<std::vector<T>,int> k = {r, count};
    return std::make_pair(x_, k);
}
#endif //SLAE_CG_HPP

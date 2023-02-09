//
// Created by julia on 05.02.23.
//
#include <vector>
#include "../ThreeDiagonalMatrix/three_diagonal.h"
#ifndef SLAE_TREEDIAGONALSOLVE_H
#define SLAE_TREEDIAGONALSOLVE_H

class SolveOfTridiagonal {
protected:

    static std::vector<double> solution_data;
public:
    explicit SolveOfTridiagonal() = default;
    template <class T>
    static std::vector<T> find_q_p(const ThirdDiagonalMatrix<T> &start_matrix,
                                        const std::vector<T> &free_);

    template <class T>
    static std::vector<T> find_x(std::vector<T>& p, std::vector<T>& q);
};
#endif //SLAE_TREEDIAGONALSOLVE_H

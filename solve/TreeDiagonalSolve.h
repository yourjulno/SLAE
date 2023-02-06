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

    static std::vector<double> find_q_p(const ThirdDiagonalMatrix &start_matrix,
                                        const std::vector<double> &free_);


    static std::vector<double> find_x(std::vector<double>& p, std::vector<double>& q);
};
#endif //SLAE_TREEDIAGONALSOLVE_H

//
// Created by julia on 05.02.23.
//

#include "TreeDiagonalSolve.h"

std::vector<double> SolveOfTridiagonal::solution_data;
std::vector<double> SolveOfTridiagonal::find_x(std::vector<double> &p, std::vector<double> &q) {


    for (int i = p.size() - 2; i >= 0; i--){
        solution_data[i] = p[i] * solution_data[i + 1]+ q[i];

    }
    return solution_data;
};

std::vector<double> SolveOfTridiagonal::find_q_p(const ThirdDiagonalMatrix &start_matrix,
                                                 const std::vector<double> &free_) {

    unsigned int n = free_.size();
    solution_data.resize(n);
    std::vector<double> p_(n);
    std::vector<double> q_(n);



    const double b_0 = start_matrix(0)[0];
    const double c_0 = start_matrix(0)[1];

    const double p_1 = - c_0 / b_0;
    const double q_1 = free_[0] / b_0;
    p_[0] = p_1;
    q_[0] = q_1;

    for (int i = 1; i < start_matrix.rows() - 1; i++){
        double p = - start_matrix(i)[2]/(start_matrix(i)[0]*p_[i - 1] + start_matrix(i)[1]);
        p_[i] = p;

        double q = (free_[i] - start_matrix(i)[0] * q_[i - 1]) / (start_matrix(i)[0] * p_[i - 1] + start_matrix(i)[1]);
        q_[i] = q;
    }

    double x_n = (free_.back() - (start_matrix(start_matrix.rows() - 1)[1]*q_.back()))/(start_matrix(start_matrix.rows() - 1)[1]*p_.back() + start_matrix(start_matrix.rows() - 1)[2]);
    solution_data[n - 1] = x_n;
    std::vector<double> solution = find_x(p_,q_);
    return solution;
}





//
// Created by julia on 05.02.23.
//

#include "TreeDiagonalSolve.h"

std::vector<double> SolveOfTridiagonal::solution_data;
std::vector<double> SolveOfTridiagonal::find_x(std::vector<double> &p, std::vector<double> &q) {
//    solution_data.resize(p.size());
    for (int i = 0; i != p.size(); i++){
        double x_prev = p[i] * solution_data.back() + q[i];
        solution_data.push_back(x_prev);
    }
    return solution_data;
};

std::vector<double> SolveOfTridiagonal::find_q_p(const ThirdDiagonalMatrix &start_matrix,
                                                 const std::vector<double> &free_) {
//    solution_data.resize(start_matrix.rows());
    std::vector<double> p_;
    std::vector<double> q_;


    const double a_0 = start_matrix.operator()(1, 0);
    const double b_0 = start_matrix.operator()(0, 0);
    const double c_0 = start_matrix.operator()(0, 1);

    const double p_1 = - (c_0 / b_0);
    const double q_1 = free_[0] / a_0;
    p_.push_back(p_1);
    q_.push_back(q_1);

    for (int i = 1; i != start_matrix.rows(); i++){
        double p = - start_matrix.operator()(i, 2)/(start_matrix.operator()(i, 0)*p_.back() + start_matrix.operator()(i, 1));
        p_.push_back(p);

        double q = free_[i] - start_matrix.operator()(i, 0) / (start_matrix.operator()(i, 0) * p_.back() + start_matrix.operator()(i, 1));
        q_.push_back(q);
    }

    double x_n = (free_.back() - (start_matrix.operator()(start_matrix.rows() - 1, 1)*q_.back())) /(start_matrix.operator()(start_matrix.rows() - 1, 1)*p_.back() +start_matrix.operator()(start_matrix.rows() - 1, 2));
    solution_data.push_back(x_n);
    std::vector<double> solution = find_x(p_,q_);
    return solution;
}





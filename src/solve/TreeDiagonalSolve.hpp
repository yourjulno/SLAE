//
// Created by julia on 05.02.23.
//


#ifndef SLAE_TREEDIAGONALSOLVE_H
#define SLAE_TREEDIAGONALSOLVE_H

template <class T>
std::vector<T> solveTridiagonal(const ThirdDiagonalMatrix<T> &start_matrix,
                                            const std::vector<T> &free_) {

    unsigned int n = free_.size();
    std::vector<T> solution_data(n);
    std::vector<T> p_(n);
    std::vector<T> q_(n);

    p_[0] = - start_matrix[0][2] / start_matrix[0][1];
    q_[0] = free_[0] / start_matrix[0][1];

    for (int i = 0; i < start_matrix.rows() - 1; i++){
        p_[i] = - start_matrix[i][2]/(start_matrix[i][0]*p_[i - 1] + start_matrix[i][1]);


        q_[i] = (free_[i] - start_matrix[i][0] * q_[i - 1]) /
                (start_matrix[i][0] * p_[i - 1] + start_matrix[i][1]);

    }

    solution_data[n - 1]  = (free_[n-1] - (start_matrix[n - 1][0]*q_[n-1]))/
            (start_matrix[n - 1][0]*p_[n-1] + start_matrix[n - 1][1]);

    for (int i = p_.size() - 2; i >= 0; i--){
        solution_data[i] = p_[i] * solution_data[i + 1] + q_[i];

    }
    return solution_data;
}

#endif //SLAE_TREEDIAGONALSOLVE_H

//
// Created by julia on 14.02.23.
//
#include "sparse.h"

template <class T>
std::vector<T> MultiplySparseVec(const CSR<T> & sparse, const std::vector<T> &free_){
    int n = sparse.getMatrRows();

    std::vector<T> solution(n);
    for (int i = 0; i != n; i++){
        solution[i] = solution[i] + sparse.getValues(i)*free_[sparse.getCol(i)];
    }
    return solution;
}
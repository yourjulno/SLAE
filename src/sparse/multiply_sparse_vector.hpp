//
// Created by julia on 14.02.23.
//
#include "sparse.h"

template <class T>
std::vector<T> MultiplySparseVec(const CSR<T> & sparse, const std::vector<T> &free_){
    int n = sparse.getRow();
    int m = sparse.getCol();
    int res;
    std::vector<T> solution(n, 0);
    for(int i = 0; i < n; i++){
            res = 0;
            for(int p = 0; p < m; p++) {
                res = res + free_[p] * sparse(i, p);
            }
            solution[i] = res;
    }
    return solution;
}
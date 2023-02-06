//
// Created by julia on 05.02.23.
//


#include "three_diagonal.h"

ThirdDiagonalMatrix::ThirdDiagonalMatrix(const std::vector<line> &matrix) {
    data_ = matrix;
}

double &ThirdDiagonalMatrix::operator()(unsigned int i, unsigned int j) const{
    static double num;
    if (i > data_.size()){
        throw;
    }
    if (j > 2){
        throw;
    }
    if (j == 0){
        num = data_[i].first;
    }
    if (j == 1){
        num = data_[i].second;
    }
    if (j == 2){
        num = data_[i].third;
    }
    return num;

}

unsigned int ThirdDiagonalMatrix::rows() const {
    return data_.size();
}

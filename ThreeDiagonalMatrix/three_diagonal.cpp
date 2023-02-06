//
// Created by julia on 05.02.23.
//


#include "three_diagonal.h"

ThirdDiagonalMatrix::ThirdDiagonalMatrix(unsigned int N) {
    data_.resize(N);
}

double &ThirdDiagonalMatrix::operator()(unsigned int i, unsigned int j) const {
    double number_;
    if (i > data_.size()){
        throw;
    }
    if (j > 2){
        throw;
    }
    if (j == 0){
        number_ = data_[i].first;
    }
    if (j == 1){
        number_ = data_[i].second;
    }
    if (j == 2){
        number_ = data_[i].third;
    }
    return number_;

}

unsigned int ThirdDiagonalMatrix::rows() const {
    return data_.size();
}

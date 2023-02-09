//
// Created by julia on 05.02.23.
//


#include "three_diagonal.h"

ThirdDiagonalMatrix::ThirdDiagonalMatrix(const std::vector<line> &matrix) {
    data_ = matrix;
}

std::array<double, 3> &ThirdDiagonalMatrix::operator()(unsigned int i) const{

    static std::array<double, 3> num_in_lines{};

    num_in_lines[0] = data_[i].first;
    num_in_lines[1] = data_[i].second;
    num_in_lines[2] = data_[i].third;

    return num_in_lines;

}

unsigned int ThirdDiagonalMatrix::rows() const {
    return data_.size();
}

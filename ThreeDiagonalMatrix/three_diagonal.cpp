//
// Created by julia on 05.02.23.
//


#include "three_diagonal.h"

template<class T>
ThirdDiagonalMatrix<T>::ThirdDiagonalMatrix(const std::vector<line<T>> &matrix) {
    data_ = matrix;
}
template<class T>
std::array<T, 3> &ThirdDiagonalMatrix<T>::operator[](unsigned int i) const{

    static std::array<T, 3> num_in_lines{};

    num_in_lines[0] = data_[i].first;
    num_in_lines[1] = data_[i].second;
    num_in_lines[2] = data_[i].third;

    return num_in_lines;

}
template <class T>
unsigned int ThirdDiagonalMatrix<T>::rows() const {
    return data_.size();
}

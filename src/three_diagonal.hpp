//
// Created by julia on 05.02.23.
//

#ifndef SLAE_THIRD_DIAGONAL_H
#define SLAE_THIRD_DIAGONAL_H
#include <vector>
#include <iostream>
#include <string>
#include <array>
namespace SLAE {

    template<class T>
    struct line {
        T first;
        T second;
        T third;
    };
}

template<class T>
class ThirdDiagonalMatrix {
private:

    std::vector<SLAE::line<T>> data_;

public:
    explicit ThirdDiagonalMatrix(const std::vector<SLAE::line<T>> &matrix);
    /* N - size of matix */
    const std::array<T, 3> & operator[](unsigned int i) const;
   /* returns (i, j) of matrix
    * i -- row, j - {0, 1, 2} */
    [[nodiscard]] unsigned int rows() const;
    /* returns size of matrix */

};

template<typename T>
ThirdDiagonalMatrix<T>::ThirdDiagonalMatrix(const std::vector<SLAE::line<T>> &matrix) {
    data_ = matrix;
}
template<class T>
const std::array<T, 3> &ThirdDiagonalMatrix<T>::operator[](unsigned int i) const{

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


#endif //SLAE_THIRD_DIAGONAL_H

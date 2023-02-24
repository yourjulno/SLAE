//
// Created by julia on 20.02.23.
//

#ifndef SLAE_DENSE_MATRIX_H
#define SLAE_DENSE_MATRIX_H
#include <vector>
#include <cmath>
//строка * столбец
template <class T>
T operator*(const std::vector<T> &other, const std::vector<T> &other2){
    T result = 0;
    for (std::size_t i = 0; i != other.size(); i++){
        result = result + other[i] * other2[i];
    }
    return result;
}

template <class T>
std::vector<T> operator-(const std::vector<T> &other, const std::vector<T> &other2){
    std::vector<T> result(other.size());
    for (std::size_t i = 0; i != other.size(); i++){
        result[i] = other[i] - other2[i];
    }
    return result;
}

template <class T>
std::vector<T> operator+(const std::vector<T> &other, const std::vector<T> other2){
    std::vector<T> result(other.size());
    for(std::size_t i = 0; i != other.size(); i++){
        result[i] = other[i] + other2[i];
    }
    return result;
}

template <class T>
std::vector<T> operator*(T number, std::vector<T> other){
    for (auto i : other){
        i = i * number;
    }
    return other;
}

// норма вектора
template <class T>
T lenght (const std::vector<T> &other) {
    T res = 0;
    for (std::size_t i = 0; i != other.size(); i++){
        res = res + other[i]*other[i];
    }
    return res;
}





// плотная матрица
template <class T>
class DenseMatrix{

    int rows;

    int colns;
    std::vector<T> data;

public:

    DenseMatrix(const std::vector<T> &other, int col, int row);
//    DenseMatrix(const std::vector<T> &other, const std::vector<T> &other2);
    std::vector<T> operator*(const std::vector<double> &free) const;
    T operator()(int i, int j) const; // i - row, j - coln
    std::vector<T> operator[](int j) const;
    [[nodiscard]] int GetSize() const{
        return data.size();
    }
    [[nodiscard]] int getRows() const {
        return rows;
    }
    [[nodiscard]] int getColns() const{
        return colns;
    }
    std::vector<T> getData() const{
        return data;
    }
};

// возвращаем столбец матрицы
template<class T>
std::vector<T> DenseMatrix<T>::operator[](int j) const { // j - номер столбца
    std::vector<T> coln(rows);
    for (std::size_t i = 0; i != data.size(); i++){
        coln[i] = data[i * colns + j];
    }
    return coln;
}


template<class T>
T DenseMatrix<T>::operator()(int i, int j) const {
    return data[i * colns + j];
}

template<class T>
DenseMatrix<T>::DenseMatrix(const std::vector<T> &other, int col, int row) {
    data = other;
    colns = col;
    rows = row;
}

// матрица на вектор
template<class T>
std::vector<T> DenseMatrix<T>::operator*(const std::vector<double> &free) const {
    std::vector<T> solution(rows);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < colns; j++){
            solution[i] = solution[i] + data[j]* free[j];
        }
    }
    return solution;
}

// столбец * строка
//template <class T>
//DenseMatrix<T> operator*(const std::vector<T> &other, const std::vector<T> other2){
//    std::vector<T> result(other.size());
//    T val;
//    for(std::size_t i = 0; i != other.size(); i++) { // rows
//        val = other[i] * other2[i];
//        result[i] = val;
//    }
//
//    return DenseMatrix<T>(result, other.size(), other2.size());
//}
#endif //SLAE_DENSE_MATRIX_H

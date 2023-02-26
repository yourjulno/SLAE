//
// Created by julia on 20.02.23.
//

#ifndef SLAE_DENSE_MATRIX_H
#define SLAE_DENSE_MATRIX_H
#include <vector>
#include <cmath>
#include <array>
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
    return sqrt(res);
}

// плотная матрица
template <class T>
class DenseMatrix{

    int rows;
    int colns;
    std::vector<T> data;

public:

    DenseMatrix(const std::vector<T> &other, int col, int row): data(other), colns(col), rows(row){};
    DenseMatrix(int size): colns(size), rows(size), data(std::vector<T>(size * size)){};

    const T& operator()(const int &i, const int &j) const; // i - row, j - coln
    T operator()(const int &i, const int &j);
     std::vector<T> operator[](int i) const;

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

template<class T>
const T &DenseMatrix<T>::operator()(const int &i, const int &j) const {
    return data[i * colns + j];
}

// возвращаем столбец матрицы
template<class T>
std::vector<T> DenseMatrix<T>::operator[](int i) const { // i - номер столбца
    std::vector<T> coln(rows);
    for (std::size_t k = 0; k != rows ; k++){
        coln[k] = data[k * colns + i];
    }
    return coln;
}
//замена столбца матрицы на выбранный столбец


template<class T>
T DenseMatrix<T>::operator()(const int &i, const int &j){
    return data[i * colns + j];
}

template<class T> // n - rows, m - colns
DenseMatrix<T> diag_matrix(int n, int m){
    std::vector<T> data(n * m, 0);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (i == j){
                data[j] = 1;
            }
        }
    }
    return DenseMatrix<T>{data, n, m};
}
// столбец * строка

template <class T>
DenseMatrix<T> coln_row(const std::vector<T> &other, const std::vector<T> &other2){
    int n = other.size(); // rows
    int m = other2.size(); // colns
    std::vector<T> data(n * m);

    for (int i = 0; i < n; i++){ // по строкам
        for (int j = 0; j < m; j++){
            data[i*n + j] = other[i] * other2[j];
        }
    }
    return DenseMatrix<T>{data, n, m};
}


// матрица на вектор
//template<class T>
//std::vector<T> DenseMatrix<T>::operator*(const std::vector<double> &free) const {
//    std::vector<T> solution(rows);
//    for (int i = 0; i < rows; i++){
//        for (int j = 0; j < colns; j++){
//            solution[i] = solution[i] + data[j]* free[j];
//        }
//    }
//    return solution;
//}

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

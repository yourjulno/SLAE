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

    int delta;
    if (other.size() == other2.size()){
        delta = 0;
    }
    else if (other2.size() > other.size()){
        delta = other2.size() - other.size();
    }
    for (std::size_t i = 0; i != other.size(); i++){
        result = result + other[i] * other2[i + delta];
    }
    return result;
}
template <class T>
T operator/(const std::vector<T> &other, const std::vector<T> &other2){
    T result = 0;

    int delta;
    if (other.size() == other2.size()){
        delta = 0;
    }
    else if (other2.size() > other.size()){
        delta = other2.size() - other.size();
    }
    for (std::size_t i = 0; i != other.size(); i++){
        result = result + other[i] / other2[i + delta];
    }
    return result;
}

template <class T>
std::vector<T> operator-(const std::vector<T> &other,  const std::vector<T> &other2){
    int delta = 0;
    if (other.size() > other2.size()){
        delta = other.size() - other2.size();
    }
    std::vector<T> result(other.size());
    for (std::size_t i = 0; i != other.size(); i++){
        result[i] = other[i] - other2[i + delta];
    }
    return result;
}

template <class T>
std::vector<T> operator+(const std::vector<T> &other, const std::vector<T> other2){
#ifndef NDEBUG
    assert(other.size() == other2.size());
#endif
    std::vector<T> result(other.size());
    for(std::size_t i = 0; i != other.size(); i++){
        result[i] = other[i] + other2[i];
    }
    return result;
}

template <class T>
std::vector<T> operator*(T number, const std::vector<T> &other){
    std::vector<T> res(other.size());
    for (int i = 0 ; i < other.size(); i++){
        res[i] = other[i] * number;
    }
    return res;
}
template <class T>
std::vector<T> operator/(const std::vector<T> &other, T number){
    std::vector<T> res(other.size());
    for (int i = 0 ; i < other.size(); i++){
        res[i] = other[i] / number;
    }
    return res;
}


//template <class T>
//std::vector<T> operator*(T number, std::vector<T> other){
//    for (auto i : other){
//        i = i * number;
//    }
//    return other;
//}

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
    using idx_t = int;
    using elm_t = T;
    DenseMatrix(std::vector<T> other, int col, int row): data(other), colns(col), rows(row){};

    std::vector<T> operator*(const std::vector<T> &free_) const;
    const elm_t &operator()(std::size_t i,  std::size_t j) const{
        return data[i * colns+ j];
    } // i - row, j - coln
    elm_t &operator()(const idx_t &i, const idx_t &j) {
         return data[i * colns + j];
    }

     std::vector<T> operator[](int i) const;
    void swap(const idx_t &first, const idx_t &second) {
        for (int i = 0; i < rows; ++i) {
            std::swap(data[first * rows + i], data[second * rows + i]);
        }
    }
    const std::vector<T> &operator*(T num);

    std::vector<T> getRow(int i) const;
    [[nodiscard]] int GetSize() const{
        return data.size();
    }
    [[nodiscard]] int getRows() const {
        return rows;
    }
    [[nodiscard]] int getColns() const{
        return colns;
    }
    const std::vector<T> &getData() const{
        return data;
    }
};

// возвращаем столбец матрицы
template<class T>
std::vector<T> DenseMatrix<T>::operator[](int i) const { // i - номер столбца
    std::vector<T> coln(rows);
    for (std::size_t k = 0; k < rows ; k++){
        coln[k] = data[k * rows + i];
    }
    return coln;
}

template<class T> // n - rows, m - colns
DenseMatrix<T> diag_matrix(int n, int m){
    std::vector<T> data(n * m, 0);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (i == j){
                data[i*m + j] = 1;
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


 //матрица на число
template<class T>
const std::vector<T> &DenseMatrix<T>::operator*(T num) {
    for (int i = 0; i < data.size(); i++){
        data[i] = data[i] * num;
    }
    return data;
}

template<class T>
std::vector<T> DenseMatrix<T>::getRow(int i) const { // i - номер строки
    std::vector<T> row(colns);
    for (std::size_t k = 0; k != colns ; k++){
        row[k] = data[i * colns + k];
    }
    return row;
}

template<class T>
std::vector<T> DenseMatrix<T>::operator*(const std::vector<T> &free_) const {



    std::vector<T> solution(colns, 0);
    for (int i = 0; i < colns; i++){

            solution[i] = solution[i] + data[i]*free_[i];
        }
    return solution;

}


#endif //SLAE_DENSE_MATRIX_H

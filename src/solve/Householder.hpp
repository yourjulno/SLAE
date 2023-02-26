//
// Created by julia on 20.02.23.
//

#ifndef SLAE_HOUSEHOLDER_H
#define SLAE_HOUSEHOLDER_H

#include "../dense_matrix.hpp"

//other - вектор матрицы
//j - номер столбца
//size - размер исходного столбца матрицы
// i - кол-во строк, которые мы пропустили на j-ом шаге
std::vector<double> take_coln_from_data(const std::vector<double> &other, int j, int size, int i){
    std::vector<double> coln(size - i);
    int count = 0;
    for (int k = i; k < size ; k++){
        coln[count] = other[k * size + j];
        count++;
    }
    return coln;
}

template <class T>
DenseMatrix<T> Householder_alg_R(const DenseMatrix<T> &start_matrix) {


    double betta;
    double sigma;

    int m = start_matrix.getColns(); // кол-во столбцов
    int n = start_matrix.getRows(); // кол-во строк

    std::vector<std::vector<T>> Q(m);
    std::vector<T> v(n);
    std::vector<T> data_copy = start_matrix.getData();

    for (int i = 0; i != m; i++) {// проход по столбцам

        if (i == 0){
            v = start_matrix[0];
        }
        else
            v = take_coln_from_data(data_copy, i, n, i);

        //v = v + sign(v[0]) * |v|
        if (v[0] < 0) {
            v[0] = v[0] - lenght(v);
        } else
            v[0] = v[0] + lenght(v);
        Q[i] = v;
        sigma = v * v;
        for (std::size_t j = i; j < m; j++) { // столбец прошли - пошли по всей матрице (тоже постолбцово)
            //std::vector<T> r = take_coln_from_data(data_copy, j, n, i);
            if (i == 0){
                betta = v * start_matrix[j];
            }
            else
                betta = v * take_coln_from_data(data_copy, j, n, i);
            int iter_for_v = 0;

            for ( std::size_t k = i; k < n ; k++) {// обращение к элементам столбца
                //(3, 1, 1, 2, 1, 1), takes (
                data_copy[k*m + j] = data_copy[k*m + j] - (2 * (betta / sigma) * v[iter_for_v]);
                iter_for_v++;

            }

        }
    }
    data_copy.back() = - data_copy.back();
    DenseMatrix<T> res(data_copy, m, n);

    double betta_;
    double gamma;
    DenseMatrix<T> P_1{Q[0], n, m};
    std::vector<T> Q_data = P_1.getData();
    for (int i = 0; i < m; i++){ // идём по строкам
        gamma = lenght(Q[i]);
        for (int j = 0; j < n; j++){ // по столбцам
            betta_ = Q[i][j] * Q_data[i*n + j];

            Q_data[i*n + j] = Q_data[i*n + j] - (2 * (betta_/gamma) * Q[i][j]);
        }
    }
    for (auto i : Q_data){
        std::cout << i << " ";
    }
    return res;


}
//n - строки
//m - столбцы
template <class T>
std::vector<T> compute_Q(const std::vector<std::vector<T>> &other, int n, int m){
    std::vector<T> v(n);
    double betta;
    double gamma;
    DenseMatrix<T> P_1{other[0], n, m};
    std::vector<T> Q_data = P_1.getData();
    for (int i = 0; i < m; i++){ // идём по строкам
        gamma = lenght(other[i]);
       for (int j = 0; j < n; j++){ // по столбцам
           betta = other[i][j] * Q_data[i][j];

           Q_data[i][j] = Q_data[i][j] - (2 * (betta/gamma) * other[i][j]);
       }
    }
    for (auto i : Q_data){
        std::cout << i;
    }
    return Q_data;

}

#endif //SLAE_HOUSEHOLDER_H

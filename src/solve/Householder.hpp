//
// Created by julia on 20.02.23.
//

#ifndef SLAE_HOUSEHOLDER_H
#define SLAE_HOUSEHOLDER_H

#include "../dense_matrix.hpp"
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
DenseMatrix<T> Householder_alg(const DenseMatrix<T> &start_matrix) {
    DenseMatrix<T> copy = start_matrix;

    double betta;
    double sigma;

    int m = start_matrix.getColns(); // кол-во столбцов
    int n = start_matrix.getRows(); // кол-во строк
    std::vector<T> v(n);
   std::vector<T> data_copy = start_matrix.getData();

    for (int i = 0; i != m; i++) {// проход по столбцам

        if (i == 0){
            v = copy[0];
        }
        else
            v = take_coln_from_data(data_copy, i, n, i);

        //v = v + sign(v[0]) * |v|
        if (v[0] < 0) {
            v[0] = v[0] - lenght(v);
        } else
            v[0] = v[0] + lenght(v);

        sigma = v * v;
        for (std::size_t j = i; j < n; j++) { // столбец прошли - пошли по всей матрице
            //std::vector<T> r = take_coln_from_data(data_copy, j, n, i);
            if (i == 0){
                betta = v * start_matrix[j];
            }
            else
                betta = v * take_coln_from_data(data_copy, j, n, i);
            int iter_for_v = 0;

            for ( std::size_t k = i; k < m ; k++) {// обращение к элементам столбца

                data_copy[k*m + j] = data_copy[k*m + j] - (2 * (betta / sigma) * v[iter_for_v]);
                iter_for_v++;

            }

        }
    }
    data_copy.back() = - data_copy.back();
    DenseMatrix<T> res(data_copy, m, n);
    return res;


}

#endif //SLAE_HOUSEHOLDER_H

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
    std::vector<double> coln(size-i);
    int count = 0;
    for (int k = i; k < size ; k++){
        coln[count] = other[k * size + j];
        count++;
    }
    return coln;
}
// i - текущая строка
// k - текущий столбец
std::vector<double> take_row_from_data(const std::vector<double> &other, int size, int i){
    std::vector<double> row(size);
    //int count = 0;
    for (int k = 0; k < size ; k++){
        row[k] = other[i * size + k];
        //count++;
    }
    return row;
}

//get P_1
template <class T>
DenseMatrix<T> computeP1(const std::vector<T> &v, int n, int m){
    DenseMatrix<T> diag = diag_matrix<T>(n, m);
    DenseMatrix<T> from_v = coln_row(v, v);

    std::vector<T> data_from_v = from_v.getData();
    T scalar_ = 2/(v * v);
    std::vector<T> diag_ =  diag.getData();
    data_from_v = scalar_*data_from_v;
    DenseMatrix<T> P1{diag_ - data_from_v, n, m};
    return P1;

}

template <class T>
std::vector<T> computePA(const std::vector<T> &v,
                         int n, int m, std::vector<T> start_data) {

    double betta;
    double sigma;

    sigma = v * v;
    std::vector<T> copy_v = v;
    while (n > copy_v.size()){
        copy_v.insert(copy_v.begin(),0);
    }

    for (std::size_t j = 0; j < m; j++) { // прошли строчку - пошли по всей матрцие(построчно!)
        auto h = take_row_from_data(start_data,   m, j);
        betta = copy_v * take_row_from_data(start_data,  m, j);
        int iter_for_v = 0;

        for ( std::size_t k = 0; k < n ; k++) {// обращение к элементам строки

                start_data[j*m + k] = start_data[j*m + k] - (2 * (betta / sigma) * copy_v[iter_for_v]);

                iter_for_v++;

        }

    }

    return start_data;
}

template <class T>
std::pair<std::vector<T>, std::vector<T>> Householder_alg_R(const DenseMatrix<T> &start_matrix) {


    double betta;
    double sigma;

    int m = start_matrix.getColns(); // кол-во столбцов
    int n = start_matrix.getRows(); // кол-во строк

    DenseMatrix<T> P_1{n, m};
    std::vector<T> v(n, 0);
    std::vector<T> data_copy = start_matrix.getData();
    std::vector<T> pdata;
    for (int i = 0; i != m - 1; i++) {// проход по столбцам

        v = take_coln_from_data(data_copy, i, n, i);
        //v = v + sign(v[0]) * |v|
        if (v[0] < 0) {
            v[0] = v[0] - lenght(v);
        } else
            v[0] = v[0] + lenght(v);

        if (i == 0) {

            P_1 = computeP1(v, n, m); // начальная матрица P1
             pdata = P_1.getData();

        }
        else
            pdata = computePA(v, n, m, pdata);

        sigma = v * v;
        for (std::size_t j = i; j < m; j++) { // столбец прошли - пошли по всей матрице (тоже постолбцово)

            betta = v * take_coln_from_data(data_copy, j, n, i);
            int iter_for_v = 0;

            for ( std::size_t k = i; k < n ; k++) {// обращение к элементам столбца
                //(3, 1, 1, 2, 1, 1), takes (3, 2)
                data_copy[k*m + j] = data_copy[k*m + j] - (2 * (betta / sigma) * v[iter_for_v]);
                iter_for_v++;

            }

        }
    }
    std::pair<std::vector<T>, std::vector<T>> result = {data_copy, pdata};

    return  result;


}

#endif //SLAE_HOUSEHOLDER_H

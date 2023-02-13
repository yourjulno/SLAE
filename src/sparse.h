//
// Created by julia on 13.02.23.
//

#ifndef SLAE_SPARSE_H
#define SLAE_SPARSE_H
#include <vector>
#include <set>

template <class T>
struct Tri{
    T i; // номер строки
    T j; // номер столбца
    T val;
};
template <class T>
class CSR{

    int matr_col; // кол-во столбцов матрицы
    int matr_rows; // кол-во строк матрицы
    std::vector<T> values; // ненулевые элементы матрицы
    std::vector<T> col; // столбцы ненулевых значений
    std::vector<T> rows; // сколько ненулевых элементов в строках до и в нынешней
public:

    CSR(const std::vector<T>& val_, const std::vector<T>& col_,
           const std::vector<T>& rows_){
        values = val_;
        col = col_;
        rows = rows_;
    }
   CSR(const std::set<Tri<T>> & triple, int matr_col_, int matr_rows_){
        matr_col = matr_col_;
        matr_rows = matr_rows_;

        values.resize(triple.size(), 0);
        col.resize(triple.size(), 0);
        rows.resize(matr_rows + 1, 0);

        auto iter = triple.begin();
        auto first_row = 0;
        auto is_in_row = 0;

        for (int k = 0; k != triple.size(); k++){
            values[k] = iter->val;
            col[k] = iter->j;

            while (first_row < iter->i){ // каждый находясь в новом элементе переписывает значения
                // строк в старых
                rows[first_row + 1] = rows[first_row] + is_in_row; // взяли элемент, присвоили то,
                // что было до + 1
                first_row++;
                is_in_row = 0;
            }
            is_in_row++;
            iter = std::next(triple);
        }

    }
    const T &operator()(int i, int j) const;



};

template<class T>
const T &CSR<T>::operator()(int i, int j) const{
        for (int row = 0; row != matr_rows; row++){

        }

}

#endif //SLAE_SPARSE_H

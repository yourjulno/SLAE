//
// Created by julia on 13.02.23.
//

#ifndef SLAE_SPARSE_HPP
#define SLAE_SPARSE_HPP
#include <vector>
#include <set>


template <class T>
struct Tri{
    int i; // номер строки
    int j; // номер столбца
    T val;

    bool operator<(Tri<T> const & other) const
    {
        return this->i < other.i || (this->i == other.i && this->j < other.j);

    }
};

template <class T>
class CSR{

    int matr_col; // кол-во столбцов матрицы
    int matr_rows;


    // кол-во строк матрицы
    std::vector<T> values;
    // ненулевые элементы матрицы
    std::vector<int> col; // столбцы ненулевых значений
    std::vector<int> rows; // сколько ненулевых элементов в строках до и в нынешней
public:
    CSR() = default;
    // если готовая CSR матрица
    [[maybe_unused]] CSR(const std::vector<T>& val_, const std::vector<T>& col_,
           const std::vector<T>& rows_){

        values = val_;
        col = col_;
        rows = rows_;
    }
    //std::vector<T> without_diag(const std::vector<T> &other) const;
    // если подадим сет из структур
   CSR(const std::set<Tri<T>> & triple, int matr_col_, int matr_rows_) {
        matr_col = matr_col_;
        matr_rows = matr_rows_;

        values.resize(triple.size(), 0);
        col.resize(triple.size(), 0);
        rows.resize(matr_rows + 1, triple.size());

        rows[0] = 0;

        auto iter = triple.begin();
        auto is_in_row = 0;
        int res = 0;
        for (int p = 0; p < triple.size(); p++) {
            values[p] = iter->val;
            col[p] = iter->j;
            res++;
            if (iter->i == std::next(iter)->i - 1){
                is_in_row++;
                rows[is_in_row] = res;
            }
            iter = std::next(iter);
        }
    }
    std::vector<T> get_diag() const;

    [[nodiscard]] int getMatrRows(int i) const {
        return rows[i];
    }
    T getValues(int i) const {
        return values[i];
    }
    [[nodiscard]] int getColns(int i) const {
        return col[i];
    }
    [[nodiscard]] int  getRow() const{
        return matr_rows;
    }
    [[nodiscard]] int getCol() const{
        return matr_col;
    }
    std::vector<T> operator*(const std::vector<T> &free_) const;
    T operator()(int row, int coln) const;

};

//template<class T>
//std::vector<T> CSR<T>::without_diag(const std::vector<T> &other) const{
//    std::vector<T> solution(matr_col, 0);
//    for (int i = 0; i < matr_col; i++)
//        for (int j = rows[i]; j < rows[i + 1]; j++) {
//            i = !col[i];
//            if (i) {
//                solution[i] = solution[i] + values[j]*other[col[j]];
//            }
//        }
//    return solution;
//}


template<class T>
 T CSR<T>::operator()(int row, int coln) const{
        T number = 0;
        int currCol;

        for (int pos = rows[row]; pos < rows[row + 1]; ++pos){
            currCol = col[pos];

            if (currCol == coln){
                return values[pos];
            }
            else if (currCol > coln){
                break;
            }
        }
        return number;

}
template<class T>
std::vector<T> CSR<T>::operator*(const std::vector<T> &free_) const {



    std::vector<T> solution(matr_rows, 0);
    for (int i = 0; i < matr_col; i++)
        for (int j = rows[i]; j < rows[i + 1]; j++){
            solution[i] = solution[i] + values[j]*free_[col[j]];
        }
    return solution;

}

//template <class T>
//std::vector<T> without_diag(const CSR<T> &A, const std::vector<T> &x){
//
//    std::vector<T> solution(A.getCol(), 0);
//    for (int i = 0; i < A.getCol(); i++)
//        for (int j = A.getMatrRows(i); j < A.getMatrRows(i + 1); j++) {
//            i = !A.getColns(j);
//            if (i) {
//            solution[i] = solution[i] + A.getValues(j) * x[A.getColns(j)];
//        }
//        }
//    return solution;
//}
template <class T>
std::vector<T> diagonal(const CSR<T> &A){

    std::vector<T> solution(A.getCol(), 0);
    for (int i = 0; i < A.getCol(); i++)
        for (int j = A.getMatrRows(i); j < A.getMatrRows(i + 1); j++){
            if (i == A.getColns(j)){
                solution[i] =  A.getValues(j);
            }

        }
    return solution;
}





#endif //SLAE_SPARSE_HPP

//
// Created by julia on 16.04.23.
//

#ifndef SLAE_GMRES_HPP
#define SLAE_GMRES_HPP
#include "../sparse/sparse.hpp"
#include "../dense_matrix.hpp"

template <class T>
auto tolerance = static_cast<T>(1e-10);
template <class T>
T Tabs(const T &a) {
    if (a < T(0)) return -a;
    else return a;
}

template <class T>
typename DenseMatrix<T>::idx_t col_max(const DenseMatrix<T> &A, const typename DenseMatrix<T>::idx_t &col) {
    using idx_t = typename DenseMatrix<T>::idx_t;
    using elm_t = typename DenseMatrix<T>::elm_t;
    elm_t max = Tabs(A(col, col));
    int maxPos = col;
    for (idx_t i = col + 1; i < A.getRows(); ++i) {     //поиск максимального по модулю элемента в столбце col
        elm_t element = Tabs(A(i, col));
        if (element > max) {
            max = element;
            maxPos = i;
        }
    }
    return maxPos;
}

template <typename T>
T headTriangulation(DenseMatrix<T> &A, std::vector<T> &b) {

    using idx_t = typename DenseMatrix<T>::idx_t;
    using elm_t = typename DenseMatrix<T>::elm_t;

    T oper_count = 0;

    for (idx_t i = 0; i < A.getRows() - 1; ++i) {
        idx_t imax = col_max(A, i); //индекс максимального по модулю элемента под диагональю
        if (Tabs(A(imax, i)) < tolerance<T>) {  //если максимальный равен 0, то пропускаем столбец из рассмотрения
            continue;
        } else {
            if (i != imax) {
                A.swap(i, imax);        //переставляем строку с максимальным по модулю элементом с текущей местами
                std::swap(b[i], b[imax]); //элемент свободного столбца также переставляется
            }

            for (idx_t k = i + 1; k < A.getRows(); ++k) { //проход по всем строкам под текущей
                oper_count += 1;
                elm_t coef = (A(k, i) / A(i, i));
                for (idx_t j = i; j < A.getColns(); ++j) { //проход по всем элементам строки
                    A(k, j) -= A(i, j) *
                               coef;          //вычитание из строки k строки i, умноженной на коэффициент для зануления элементов столбца i
                }
                b[k] -= b[i] * coef; //вычитание свободного члена уравнения
            }
        }
    }

    std::cout << "\n";
    return oper_count;   //возвращаем число перестановок(может потребоваться для поиска определителя)
}
template <typename T>
std::vector<T> backSubstTopTriangula(const DenseMatrix<T> &A, const std::vector<T> &b, size_t SZ) {
    T oper_count = 0;
    std::vector<T> res(b.size());
    res.back() = b.back() / A(SZ - 1, SZ - 1);
    T sum;
    for (int i = int(SZ) - 2; i >= 0; --i) {
        sum = 0;
        for (size_t j = i + 1; j < b.size(); ++j) {
            sum += A(i, j) * res[j];
            ++oper_count;
        }
        res[i] = (b[i] - sum) / A(i, i);
    }
   // std::cout << oper_count << " ";
    return res;
}
template <typename T>
std::vector<T> headGaussMethod(DenseMatrix<T> A,
                               std::vector<T> b) {

    T oper_count = headTriangulation(A, b); //приводим матрицу к верхнетреугольной с выбором главного элемента
    //std::cout << oper_count << " ";
    return backSubstTopTriangula(A, b, oper_count);
}


template <class T>
std::pair<std::vector<T>, std::vector<std::vector<T>>> Givence(const std::vector<T> &h_i,
                                                 std::vector<std::vector<T>>  &turns){


    std::vector<T> h_i_turn = h_i;
    std::vector<T> new_turn(static_cast<std::size_t>(4));
    const std::size_t turns_count = turns.size();
    // turns_count - кол-во поворотов, берем элемент предпоследний и последний у вектора h_i
    const T prev = h_i[turns_count];
    const T next = h_i[turns_count + 1];

    const T coordsqrt = std::sqrt(next * next + prev * prev);
    const T cos_theta = prev / coordsqrt;
    const T sin_theta = next / coordsqrt;

    new_turn = {cos_theta, - sin_theta, sin_theta, cos_theta};
    turns.push_back(new_turn);

    for (std::size_t i = 0; i < turns_count; i++){
        h_i_turn[turns_count - 1] = turns[i][0] * h_i_turn[turns_count] + turns[i][1]*h_i_turn[turns_count + 1];
        h_i_turn[turns_count] = turns[i][2] * h_i_turn[turns_count] + turns[i][3]*h_i_turn[turns_count + 1];
    }

    std::pair<std::vector<T>, std::vector<std::vector<T>>> solve = {h_i_turn, turns};
    return solve;


}
template <class T>
std::pair<DenseMatrix<T>, std::vector<T>> Arnoldi_algorythm(const CSR<T> &A,
                                 const std::vector<T> &r_0, T tolerance, const int i){

    const int n = i;
    std::vector<T> v_0 = r_0 / lenght(r_0);


    const int hes_rows = n + 1;
    const int hes_cols = n;
    const int h_size = n * (n + 1);
    std::vector<T> h(h_size);

    T h_;
    std::vector<T> v_k = A * v_0;;

    for (std::size_t j = 0; j < n; j ++){
        v_0 = A * v_0;
        for (std::size_t k = 0; k <= j; k++){
            h_ = v_0 * v_k;
            v_0 = v_0 - h_ * v_k;
            h[k * hes_cols + j] = h_;

        }

        h_ = lenght(v_0);
        h[(j + 1) * hes_cols + j] = h_;
        if (h_ > tolerance){
            v_k = v_0 / h_;
        }

    }
    DenseMatrix<T> Hessian{h, hes_cols, hes_rows};
    std::pair<DenseMatrix<T>, std::vector<T>> solve = {Hessian, v_k};

    return solve;


}

template <class T>
DenseMatrix<T> convert_from_vector_to_matrix(std::vector<std::vector<T>> & other, const int m) {
    const int cols = m;
    const int rows = m;
    const int data_size = rows*cols;
    std::vector<T> data;
    data.reserve(data_size);
    for (int i = 0; i < other.size(); i++) {
        while (other[i].size() < m) {
            other[i].push_back(static_cast<T>(0));
        }
    }

   for (int i = 0; i < m; i++){
      for (int j = 0; j < other.size(); j++){
          data.push_back(other[j][i]);
      }
   }
    DenseMatrix<T> result{data, cols, rows};
    return result;

}
template <class T>
std::vector<T> get_col_from_hessian(const DenseMatrix<T> &Hes, const int i){
    std::vector<T> res;
    const int rows = Hes.getRows();
    const int colns = Hes.getColns();
    const int Hes_size = colns * rows;

    res.insert(res.end(), Hes.getData().end() - i, Hes.getData().end());
//    for(int j = i + 1; j >= 0; j--){
//        res[j - 1] = Hes.getData()[Hes_size - j - 1];
//    }
    return res;
}
template <class T>
std::vector<T> GMRES(const CSR<T> &A, const std::vector<T> x_0, const std::vector<T> b,
                     const int m, T tolerance){
    std::vector<T> r_0 = A * x_0 - b;
    T norm_r0 = lenght(r_0);
    r_0 = r_0 / norm_r0;

    std::vector<T> h_i;

    std::vector<T> x;
    std::vector<std::vector<T>> turns;
    turns.reserve(x_0.size());
    std::vector<std::vector<T>> R;
    std::vector<T> y = r_0;
    std::vector<T> z;
    std::vector<std::vector<T>> Ql;
    Ql.reserve(m);
    std::vector<T> q;
    std::vector<T> r;

        for (std::size_t i = 1; i < 5; i++) {
                auto res_from_arnoldi = Arnoldi_algorythm(A, r_0, 1e-2, i);
                auto Hessian = res_from_arnoldi.first;
                h_i = get_col_from_hessian(Hessian, i + 1); //i-ый столбец хессиана
                q = res_from_arnoldi.second; //i-ый базисный вектор Крылова
                Ql.push_back(q);
                //вращаем вектор h_i
                auto res_from_givence = Givence(h_i, turns);
                R.push_back(res_from_givence.first);

                //матрица поворотов Q
                auto Q = res_from_givence.second;

                //формируем z_i (по сути столбец b)

                z.push_back(Q[i - 1][0] * norm_r0);
            auto R_convert = convert_from_vector_to_matrix(R, i);
            y = headGaussMethod(R_convert, z);
            auto V = convert_from_vector_to_matrix(Ql, i);
            x = x_0 - V * y;

        }


    return x;
}

#endif //SLAE_GMRES_HPP

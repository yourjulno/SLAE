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


template <class T>
std::vector<T> get_last_coln_from_Hessian(const DenseMatrix<T> &Hes, const int i){
    std::vector<T> coln;

    for(int j = 0; j <= i+1; j++){
        coln.push_back(Hes(j, i));
    }
    return coln;

}

template <class T>
void set_last_coln_to_Hessian(DenseMatrix<T> &Hes, const std::vector<T> &last_hes, const int i){

    for (int j = 0; j < last_hes.size(); j++){
        Hes(j, i) = last_hes[j];
    }
}
template <class T>
int Givence( DenseMatrix<T> &Hes, const int i, std::vector<std::vector<T>>  &turns, int m){


    std::vector<T> h_i = get_last_coln_from_Hessian(Hes, i);
    std::vector<T> new_turn(static_cast<std::size_t>(4));
    const std::size_t turns_count = turns.size();
    // turns_count - кол-во поворотов, берем элемент предпоследний и последний у вектора h_i
    const T prev = h_i[i];
    const T next = h_i[i + 1];

    const T coordsqrt = std::sqrt(next * next + prev * prev);
    const T cos_theta = prev / coordsqrt;
    const T sin_theta = next / coordsqrt;

    new_turn = {cos_theta, sin_theta, -sin_theta, cos_theta};
    turns.push_back(new_turn);

    for (std::size_t k = 0; k <= turns_count; k++){
        auto h_k = turns[k][0] * h_i[k] + turns[k][1]*h_i[k + 1];
        auto h_k_1 = turns[k][2] * h_i[k] + turns[k][3]*h_i[k + 1];
        h_i[k] = h_k;
        h_i[k+1] = h_k_1;
    }

    set_last_coln_to_Hessian(Hes, h_i, i);
    return 0;


}
template <class T>
int Arnoldi_algorythm(const CSR<T> &A, std::vector<std::vector<T>> &Q,
                      DenseMatrix<T> &Hes, const int i, T tolerance){

    const int n = i;
    std::vector<T> v_0 = A * Q[n];
    T h_;
    for (std::size_t j = 0; j <= n; j ++){
        h_ = v_0 * Q[i];
        v_0 = v_0 - h_ * Q[i];
        Hes(j, n) = h_;
        }

        h_ = lenght(v_0);

        if (h_ > tolerance){
            Hes(n + 1, n) = h_;
        }
        Q.push_back(v_0);
  return 0;
}

template <class T>
DenseMatrix<T> convert_from_vector_to_matrix(std::vector<std::vector<T>> & other, const int m) {
    const int cols = m;
    const int rows = m;
    const int data_size = rows*cols;
    std::vector<T> data;
    data.reserve(data_size);

   for (int i = 0; i < m; i++){
      for (int j = 0; j < other.size(); j++){
          data.push_back(other[j][i]);
      }
   }
    DenseMatrix<T> result{data, cols, rows};
    return result;

}

template <class T>
std::vector<T> GMRES(const CSR<T> &A, const std::vector<T> x_0, const std::vector<T> b,
                     const int m, T tolerance){
    std::vector<T> r_0 = A * x_0 - b;
    T norm_r0 = lenght(r_0);
    r_0 = r_0 / norm_r0;


    DenseMatrix<T> H(m + 1, m);
    std::vector<std::vector<T>> turns;
    turns.reserve(x_0.size());

    std::vector<std::vector<T>> Q;
    Q.push_back(r_0);
    std::vector<T> z;
    z.reserve(m + 1);
    z.push_back(norm_r0);
    std::vector<T> y;
    std::vector<T> x;
        for (std::size_t i = 2; i < m; i++) {
            Arnoldi_algorythm(A, Q, H, i - 2, tolerance);
            Givence(H, i - 2, turns, m);
            z.push_back(Q[i - 1][0] * norm_r0);

            y =  backSubstTopTriangula(H, z, i - 1);
            auto V = convert_from_vector_to_matrix(Q, i - 1);
            x = x_0 - V * y;
            if (lenght(x) < tolerance) {
                break;
            }
            std::cout << lenght(x) << " ";
        }


    return x;
}

#endif //SLAE_GMRES_HPP

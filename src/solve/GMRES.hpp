//
// Created by julia on 16.04.23.
//

#ifndef SLAE_GMRES_HPP
#define SLAE_GMRES_HPP
#include "../sparse/sparse.hpp"
#include "../dense_matrix.hpp"


template <typename T>
std::vector<T> backSubstTopTriangular(const DenseMatrix<T> &A, const std::vector<T> &b, size_t SZ) {
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

    return res;
}

template <class T>
int Givence( DenseMatrix<T> &Hes, const int i, std::vector<std::pair<T, T>>  &turns){

    for (std::size_t k = 0; k < turns.size(); ++k){
        auto cos_theta = turns[k].first;
        auto sin_theta = turns[k].second;
        auto h_k = cos_theta * Hes(k, i) + sin_theta * Hes(k + 1, i);
        auto h_k_1 = -sin_theta * Hes(k, i) + cos_theta * Hes(k + 1, i);
        Hes(k, i) = h_k;
        Hes(k + 1, i) = h_k_1;
    }
    const T prev = Hes(i, i);
    const T next = Hes(i + 1, i);

    const T coordSqrt = static_cast<T>(1) / std::sqrt(next * next + prev * prev);
    const T cos_theta = prev * coordSqrt;
    const T sin_theta = next * coordSqrt;

    const T h_k  = cos_theta * prev + sin_theta * next;
    const T h_k_1 = -sin_theta * prev + cos_theta * next;

    Hes(i, i) = h_k;
    Hes(i + 1, i) = h_k_1;

    turns.push_back(std::make_pair(cos_theta, sin_theta));
    return 0;


}
template <class T>
int Arnoldi_algorythm(const CSR<T> &A, std::vector<std::vector<T>> &Q,
                      DenseMatrix<T> &Hes, const int i){

    const int n = i;
    std::vector<T> v_0 = A * Q[n];
    T h_;
    for (std::size_t j = 0; j <= n; ++j){
        h_ = v_0 * Q[j];
        v_0 = v_0 - h_ * Q[j];
        Hes(j, n) = h_;
        }

        h_ = lenght(v_0);
        Hes(n + 1, n) = h_;

        v_0 = v_0 / lenght(v_0);
        Q.push_back(v_0);
  return 0;
}

template <class T>
DenseMatrix<T> convert_from_vector_to_matrix(std::vector<std::vector<T>> & other, const int k) {

    std::vector<T> data;
    data.reserve(k * k);

   for (int i = 0; i < k; i++){
      for (int j = 0; j < other.size(); j++){
          data.push_back(other[i][j]);
      }
   }
   const int n = data.size();
   DenseMatrix<T> result{data, n, n};
    return result;

}

template <class T>
std::vector<T> GMRES(const CSR<T> &A, const std::vector<T> x_0, const std::vector<T> b,
                     const int m){
    std::vector<T> r_0 = A * x_0 - b;
    T norm_r0 = lenght(r_0);
    r_0 = r_0 / norm_r0;

    DenseMatrix<T> H(m + 1, m);
    std::vector<std::pair<T, T>> turns;
    turns.reserve(x_0.size());

    std::vector<std::vector<T>> Q;
    Q.reserve(m);
    Q.push_back(r_0);
    std::vector<T> z(m, 0);
    z[0] = norm_r0;
    std::vector<T> y;
    std::vector<T> x(r_0.size());
        for (std::size_t i = 2; i <= m+1; i++) {
            Arnoldi_algorythm(A, Q, H, i - 2);
            Givence(H, i - 2, turns);
            auto z_i = turns[i - 2].first * z[i - 2] + turns[i - 2].second*z[i - 1];
            auto z_i_1 = -turns[i - 2].second * z[i - 2] + turns[i - 2].first*z[i - 1];
            z[i - 2] = z_i;
            z[i - 1] = z_i_1;
            //z.push_back(Q[i - 2][0] * norm_r0);

//            y =  backSubstTopTriangular(H, z, i - 1);
//
//
//            r_0 = A * x - b;
//            std::cout << lenght(x) << " ";
        }
        y = backSubstTopTriangular(H, z, m - 2);
        auto V = convert_from_vector_to_matrix(Q, m - 2);
    auto Vy = V * y;
    for (std::size_t k = 0; k < x.size(); k++){
        x[k] = x[k] + Vy[k];
    }
    std::cout << lenght(x) << " ";


    return x;
}

#endif //SLAE_GMRES_HPP

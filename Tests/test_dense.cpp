//
// Created by julia on 20.02.23.
//

#include <gtest/gtest.h>
#include "../src/dense_matrix.hpp"
#include "../src/solve/Householder.hpp"

//TEST(DENSE, FIRST){
//
//std::vector<double> a = {1, 2, 3, 4};
//std::vector<double> b = {1, 0, 3};
////auto val_1 = a * b;
//auto first = DenseMatrix<double>(a, 2, 2);
//auto val_2 = first(1, 1);
//std::vector<double> col = {2, 4};
//auto col_from_matr = first[1];
//ASSERT_EQ(4, val_2);
//ASSERT_EQ(col, col_from_matr);
//}

TEST(DENSE, SECOND){

    std::vector<double> a = {13, 7, 4, 7, 9, -3, 4, -3, 9};
    std::vector<double> b = {13, 7, 4};
//auto val_1 = a * b;
    auto first = DenseMatrix<double>(a, 3, 3);
//    auto val_2 = first(1, 1);
   // std::vector<double> col = {7, 9 , -3};
//    double w = col * b;
//    auto len = lenght(col);
//     auto first = DenseMatrix<double>(a, 3, 3);
    auto R = Householder_alg(first);
    
//    auto col_from_matr = first[1];
//    ASSERT_EQ(len, 139);
//    ASSERT_EQ(9, val_2);
//    ASSERT_EQ(col, col_from_matr);
}

//int main(){
//
//    std::vector<double> a = {13, 7, 4, 7, 9, -3, 4, -3, 9};
//    std::vector<double> b = {13, 7, 4};
////auto val_1 = a * b;
//    auto first = DenseMatrix<double>(a, 3, 3);
//    auto R = Householder_alg(first);
//    for (auto i : R.getData()){
//        std::cout << i;
//    }
//}
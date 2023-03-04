//
// Created by julia on 04.03.23.
//
//
// Created by julia on 04.03.23.
//


#include <gtest/gtest.h>
#include "../src/sparse/sparse.hpp"
#include "../src/solve/Jacobi.hpp"
//TEST(MPI, FIRST){
//    std::set<Tri<double>> example = {{0,0,100},{0,1,0.2},
//                                     {1,0,0.2},{1,1,100}};
//    std::vector<double> free = {1000, 999};
//    std::vector<double> x = {0,0};
//
//
//    CSR<double> first(example, 2, 2);
//    std::vector<double> res = MPI(first, x,free, 0.001, 0.002);
//    auto val = first(2, 3);
//    auto val2 = first(0, 2);
//    auto val_1 = first * free;
//    auto v = first(0, 3);
//    ASSERT_EQ(3, v);
//    ASSERT_EQ(0, val2);
//    ASSERT_EQ(11, val);
//    ASSERT_EQ(x, val_1);
//}

int main(){
    std::set<Tri<double>> example = {{0,0,100},{0,1,0.2},
                                     {1,0,0.2},{1,1,100}};
    std::vector<double> free = {1000, 999};
    std::vector<double> x = {0,0};


    CSR<double> first(example, 2, 2);
    std::vector<double> res = Jacobi(first, x,free, 0.001);
    for (auto i : res){
        std::cout << i << " ";
    }
}
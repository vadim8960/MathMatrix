#include <iostream>
#include "Matrix.h"
#include <string>

void test_func(Matrix &m, std::string name) {
    std::cout << name << std::endl;
    std::cout << m << std::endl;
    std::cout << std::endl;
}

int main() {
    double arr1[] = {1, 2,
                     3, 4,
                     5, 6};
    double arr2[] = {1, 2,
                     3, 4};
//    Matrix m;
//    test_func(m, "m");

//    Matrix m1(2);
//    test_func(m1, "m1");

//    Matrix m2(3U, 2U);
//    test_func(m2, "m2");
//
//    Matrix m3(arr2, 2);
////    test_func(m3, "m3");
//
//    Matrix m4(arr1, 3, 2);
////    test_func(m4, "m4");
////
////    Matrix m5(4U, 1.0);
////    test_func(m5, "m5");
////
////    Matrix m6(3, 2, {1, 2, 3, 4, 5, 6});
////    test_func(m6, "m6");
//
//    Matrix m7 = m3;
//    test_func(m7, "m7");
//
//
//    Matrix m8;
//    m8 = m4;
//    test_func(m8, "m8");


    std::cout << " / 1 2 3 \\\n";
    std::cout << "|  1 2 3  |\n";
    std::cout << "|  1 2 3  |\n";
    std::cout << "|  1 2 3  |\n";
    std::cout << " \\ 1 2 3 /\n";

    return 0;
}

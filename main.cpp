#include <iostream>
#include "Matrix.h"

int main() {
    double mat[] = { 1234234.1234, 2.2566,
                     3/123456.0, 4,
                     5, 6 ,7 ,8, 9};
    Matrix m(mat, 1, 9);
//    Matrix::eps = 0.1;
    std::cout << m << std::endl;
    return 0;
}

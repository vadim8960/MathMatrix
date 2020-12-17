#include <iostream>
#include "Matrix.h"

int main() {
    double mat[] = { 1234234.1234, 2.2566,
                     3/123456.0, 4,
                     5, 6 ,
                     7 ,8,
                     9, 10};
    Matrix m(mat, 5, 2);
//    Matrix::eps = 0.1;
    double arr[2] = {};
    m.GetRow(2, arr);
    std::cout << m.ColNumb() << std::endl;
    for (int i = 0; i < 2; ++i)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;
    std::cout << m << std::endl;
    return 0;
}

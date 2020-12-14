#include <iostream>
#include "Matrix.h"

int main() {
//    Matrix m6(3, 4, {1.2, 2.2564, 3.8, 4,
//                               5, 6, 7, 8,
//                               9, 10, 11, 1/12345.0});
    Matrix m6(2, 3, {1, 2, 3,
                     4, 5, 6});
    std::cout << m6 * 2.0 << std::endl;
    m6 *= 2.0;
    std::cout << m6 << std::endl;
    std::cout << 1/2.0 * m6 << std::endl;
    return 0;
}

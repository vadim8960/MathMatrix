#include <iostream>
#include "Matrix.h"

int main() {
    Matrix m6(2, 3, {1, 2, 3,
                     4, 5, 6});
    std::cout << m6 - m6 << std::endl;
    m6  += m6;
    std::cout << m6 << std::endl;
//    m6 *= 2.0;
//    std::cout << m6 << std::endl;
//    std::cout << 1/2.0 * m6 << std::endl;
    return 0;
}
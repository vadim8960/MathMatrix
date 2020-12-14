#include <iostream>
#include "Matrix.h"

int main() {
    Matrix m6(3, 4, {1.2, 2.2564, 3.8, 4,
                               5, 6, 7, 8,
                               9, 10, 11, 1/12345.0});
    std::cout << m6 << std::endl;
    return 0;
}

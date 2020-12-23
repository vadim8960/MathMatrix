#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
    double mat[] = {
            1, 2, 3, 4, 5, 6
    };
    double mat2[] = {
            1, 2, 3, 4, 5, 7
    };
    Matrix m1(mat, 3, 2);
    Matrix m2 = m1;
    Matrix m3(mat2, 3, 2);
    cout << (m1 == m2) << endl;
    cout << (m1 != m2) << endl;
    cout << (m1 != m3) << endl;
    return 0;
}

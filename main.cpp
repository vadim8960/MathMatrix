#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
    double mat1[] = {1, 2,
                    3, 4,
                    5, 6};
    double mat2[] = {5};
    Matrix m1(mat1, 3, 2);
    Matrix m2(mat2, 1, 1);
    Matrix m_empty;
    cout << "a * A" << endl;
    cout << 2 * m1;
    cout << "Error: " << Matrix::err_code << endl;
    cout << endl;
    cout << 2 * m2;
    cout << "Error: " << Matrix::err_code << endl;
    cout << endl;
    cout << 2 * m_empty;
    cout << "Error: " << Matrix::err_code << endl;
    cout << endl;

    cout << "A * a" << endl;
    cout << m1 * 2;
    cout << "Error: " << Matrix::err_code << endl;
    cout << endl;
    cout << m2 * 2;
    cout << "Error: " << Matrix::err_code << endl;
    cout << endl;
    cout << m_empty * 2;
    cout << "Error: " << Matrix::err_code << endl;
    cout << endl;

    cout << "A *= a" << endl;
    m1 *= 2;
    cout << m1;
    cout << "Error: " << Matrix::err_code << endl;
    cout << endl;
    m2 *= 2;
    cout << m2;
    cout << "Error: " << Matrix::err_code << endl;
    cout << endl;
    m_empty *= 2;
    cout << m_empty;
    cout << "Error: " << Matrix::err_code << endl;
    cout << endl;
    return 0;
}

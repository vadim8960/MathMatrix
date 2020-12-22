#include <iostream>
#include "Matrix.h"

using namespace std;

void test1() {
    cout << "A + M" << endl;
    double mat1[] = {1, 3,
                     2, 4};
    double mat2[] = {1, 2,
                     3, 4};
    double mat3[] = {1, 2,
                     3, 4,
                     5, 6};
    Matrix m1(mat1, 2, 2);
    Matrix m2(mat2, 2, 2);
    Matrix m3(mat3, 3, 2);
    Matrix m4(mat3, 2, 3);
    Matrix me;

    cout << m1 + m2;
    cout << Matrix::err_code << endl;

    cout << me + m1;
    cout << Matrix::err_code << endl;

    cout << m1 + me;
    cout << Matrix::err_code << endl;

    cout << m1 + m3;
    cout << Matrix::err_code << endl;

    cout << m1 + m4;
    cout << Matrix::err_code << endl;
}

void test2() {
    cout << "A * M" << endl;
    double mat1[] = {1, 3,
                     2, 4};
    double mat2[] = {1, 2,
                     3, 4};
    double mat3[] = {1, 2,
                     3, 4,
                     5, 6};
    double mat4[] = {1, 2, 3,
                     4, 5, 6};
    double mat5[] = {1, 2, 3,
                     4, 5, 6,
                     7, 8, 9};
    Matrix m1(mat1, 2, 2);
    Matrix m2(mat2, 2, 2);
    Matrix m3(mat3, 3, 2);
    Matrix me;

    Matrix m4(mat4, 2, 3);
    Matrix m5(mat5, 3, 3);

    cout << m4 * m5;
    cout << Matrix::err_code << endl;

    cout << m1 * m2;
    cout << Matrix::err_code << endl;

    cout << me * m1;
    cout << Matrix::err_code << endl;

    cout << m1 * me;
    cout << Matrix::err_code << endl;

    cout << m1 * m3;
    cout << Matrix::err_code << endl;
}

void test3() {
    cout << "A *= M" << endl;
    double mat1[] = {1, 3,
                     2, 4};
    double mat2[] = {1, 2,
                     3, 4};
    double mat3[] = {1, 2,
                     3, 4,
                     5, 6};
    double mat4[] = {1, 2, 3,
                     4, 5, 6};
    double mat5[] = {1, 2, 3,
                     4, 5, 6,
                     7, 8, 9};
    Matrix m1(mat1, 2, 2);
    Matrix m2(mat2, 2, 2);
    Matrix m3(mat3, 3, 2);
    Matrix me;

    Matrix m4(mat4, 2, 3);
    Matrix m5(mat5, 3, 3);

    cout << m4 * m5;
    cout << Matrix::err_code << endl;

    Matrix tmp = m1;
    tmp *= m2;
    cout << tmp;
    cout << Matrix::err_code << endl;

    me *= m1;
    cout << me * m1;
    cout << Matrix::err_code << endl;

    m1 *= me;
    cout << m1 * me;
    cout << Matrix::err_code << endl;

    m1 *= m3;
    cout << m1 * m3;
    cout << Matrix::err_code << endl;
}

int main() {
//    test1();
//    test2();
    test3();
    return 0;
}

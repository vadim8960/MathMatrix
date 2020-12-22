#include <iostream>
#include "Matrix.h"

using namespace std;

void test_multiplyRowByConst() {
    double mat[] = {1, 2,
                    3, 4,
                    5, 6};
    Matrix m(mat, 3, 2);
    Matrix m1;

    m.multiplyRowByConst(1, 5);
    cout << m << endl;
    cout << Matrix::err_code << endl;

    m.multiplyRowByConst(4, 5);
    cout << m << endl;
    cout << Matrix::err_code << endl;

    m1.multiplyRowByConst(1, 5);
    cout << m1 << endl;
    cout << Matrix::err_code << endl;
}

void test_rowSwap() {
    double mat[] = {1, 2,
                    3, 4,
                    5, 6};
    Matrix m(mat, 3, 2);

    m.rowSwap(1, 3);
    cout << m << endl;
    cout << Matrix::err_code << endl;

    m.rowSwap(1, 4);
    cout << m << endl;
    cout << Matrix::err_code << endl;
}

void test_sumRowByConstAndRow() {
    double mat[] = {1, 2,
                    3, 4,
                    5, 6};
    Matrix m(mat, 3, 2);
    Matrix m1;

    m.sumRowByConstAndRow(2, 1, 2);
    cout << m << endl;
    cout << Matrix::err_code << endl;

    m.sumRowByConstAndRow(2, 4, 5);
    cout << m << endl;
    cout << Matrix::err_code << endl;

    m1.sumRowByConstAndRow(2, 1, 2);
    cout << m1 << endl;
    cout << Matrix::err_code << endl;
};

int main() {
    test_multiplyRowByConst();
    cout << "==================" << endl;
    test_rowSwap();
    cout << "==================" << endl;
    test_sumRowByConstAndRow();
    return 0;
}


#ifndef MATHMATRIX_MATRIX_H
#define MATHMATRIX_MATRIX_H

#include <istream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdio>

#if __cplusplus >= 201103L
#include <initializer_list>
#define _NULL nullptr
#else
#define _NULL NULL
#endif

class Matrix {
private:
    double *mat;
    unsigned n;
    unsigned m;
public:
    static double eps;
    static bool simple_copy;
    static unsigned err_code;

    Matrix();
    Matrix(unsigned n);
    Matrix(unsigned n, unsigned m);
    Matrix(double * mat, unsigned n);
    Matrix(double * mat, unsigned n, unsigned m);
    Matrix(unsigned n, double a);
#if __cplusplus >= 201103L
    Matrix(unsigned n, unsigned m, const std::initializer_list<double> & MIl);
#endif
    Matrix(const Matrix & A);
    ~Matrix();

    Matrix &operator=(const Matrix & B);
    friend std::ostream &operator<<(std::ostream & out, const Matrix & A);
};


#endif //MATHMATRIX_MATRIX_H

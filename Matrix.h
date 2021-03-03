
#ifndef MATHMATRIX_MATRIX_H
#define MATHMATRIX_MATRIX_H

#include <istream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cmath>

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
    Matrix(std::ifstream& file);
    Matrix(FILE* file);
#if __cplusplus >= 201103L
    Matrix(unsigned n, unsigned m, const std::initializer_list<double> & MIl);
#endif
    Matrix(const Matrix & A);
    ~Matrix();

    Matrix transpose();
    void multiplyRowByConst(unsigned row, double c);
    void rowSwap(unsigned row1, unsigned row2);
    void sumRowByConstAndRow(unsigned row1, unsigned row2, double k);

    unsigned sizecol() const;
    unsigned sizerow() const;

    void GetRow(unsigned number, double * dest) const;
    void GetCol(unsigned number, double * dest) const;

    Matrix& Concatenation(Matrix &a);

    Matrix &operator=(const Matrix & B);

    Matrix operator-(const Matrix &B);
    Matrix &operator-=(const Matrix &B);
    Matrix &operator+=(const Matrix &B);
    Matrix operator*(double a) const;
    Matrix &operator*=(double a);
    Matrix operator+(const Matrix& M);
    Matrix operator*(const Matrix& M);
    Matrix& operator*=(const Matrix& M);

    bool operator==(const Matrix &B);
    bool operator!=(const Matrix &B);

    double* operator[](unsigned i);

    friend std::ostream &operator<<(std::ostream & out, const Matrix & A);
    friend Matrix operator*(double a, const Matrix & A);
};

#endif //MATHMATRIX_MATRIX_H

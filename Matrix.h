
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

    unsigned ColNumb() const;
    void GetRow(unsigned number, double * dest) const;

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

    friend std::ostream &operator<<(std::ostream & out, const Matrix & A);
    friend Matrix operator*(double a, const Matrix & A);
};

#endif //MATHMATRIX_MATRIX_H

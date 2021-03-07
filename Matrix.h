
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
    double *_mat;
    unsigned _crows;
    unsigned _ccols;
    static double _eps;
    static bool _simple_copy;
public:

    Matrix();
    explicit Matrix(unsigned n);
    Matrix(unsigned n, unsigned m);
    Matrix(double * mat, unsigned n);
    Matrix(double * mat, unsigned n, unsigned m);
    Matrix(unsigned n, double a);
    explicit Matrix(std::ifstream& file);
    explicit Matrix(FILE* file);
#if __cplusplus >= 201103L
    Matrix(unsigned n, unsigned m, const std::initializer_list<double> & MIl);
#endif
    Matrix(const Matrix & A);
    ~Matrix();

    Matrix transpose();
    void mult_row_by_const(unsigned row, double c);
    void swap_rows(unsigned row1, unsigned row2);
    void swap_cols(unsigned col1, unsigned col2);
    void sum_row_by_const_to_row(unsigned dest_row, unsigned mult_row, double c);

    unsigned count_col() const;
    unsigned count_row() const;

    Matrix get_submatrix(unsigned x, unsigned y, unsigned rows, unsigned cols);

    void get_row(unsigned number, double * dest) const;
    void get_col(unsigned number, double * dest) const;

    Matrix concatenation(Matrix &a);

    Matrix& operator=(const Matrix & B);
    Matrix  operator-(const Matrix &B);
    Matrix& operator-=(const Matrix &B);
    Matrix& operator+=(const Matrix &B);
    Matrix  operator*(double a) const;
    Matrix& operator*=(double a);
    Matrix  operator+(const Matrix& M);
    Matrix  operator*(const Matrix& M);
    Matrix& operator*=(const Matrix& M);
    bool    operator==(const Matrix &B);
    bool    operator!=(const Matrix &B);
    double* operator[](unsigned i);

    friend std::ostream &operator<<(std::ostream & out, const Matrix & A);
    friend Matrix operator*(double a, const Matrix & A);
};

#endif //MATHMATRIX_MATRIX_H

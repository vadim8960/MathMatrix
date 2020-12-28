
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

#define ERR_OK                            0
#define ERR_MISSING_FIRST_OPERAND         1
#define ERR_MISSING_SECOND_OPERAND        2
#define ERR_MISMATCH_SIZES_WHEN_PLUS      11
#define ERR_MISMATCH_SIZES_WHEN_MINUS     12
#define ERR_MISMATCH_SIZES_WHEN_MULT      13
#define ERR_MISMATCH_SIZES_WHEN_INIT_LIST 14
#define ERR_NON_EXISTENT_MATRIX_ELEMENT   21
#define ERR_NON_EXISTENT_MATRIX_ROW       22
#define ERR_NON_EXISTENT_MATRIX_COL       23
#define ERR_NON_EXISTENT_SUBMATRIX        24
#define ERR_FILE_NOT_OPEN                 31
#define ERR_NOT_VALID_FILE_DATA           32

class Matrix {
private:
    double *mat;
    unsigned n;
    unsigned m;
    static double eps;
    static bool simple_copy;
public:
    static unsigned err_code;

    Matrix();

    explicit Matrix(unsigned n);

    Matrix(unsigned n, unsigned m);

    Matrix(double *mat, unsigned n);

    Matrix(double *mat, unsigned n, unsigned m);

    Matrix(unsigned n, double a);

    explicit Matrix(std::ifstream &file);

    explicit Matrix(FILE *file);

#if __cplusplus >= 201103L

    Matrix(unsigned n, unsigned m, const std::initializer_list<double> &MIl);

#endif

    Matrix(const Matrix &A);

    ~Matrix();

    Matrix transposeMatrix();

    void multiplyRowByConst(unsigned row, double c);

    void rowSwap(unsigned row1, unsigned row2);

    void sumRowByConstAndRow(unsigned row1, unsigned row2, double k);

#if __cplusplus >= 201103L

    [[nodiscard]] unsigned countCols() const;

#else
    unsigned countCols() const;
#endif

    void GetRow(unsigned number, double *dest) const;

    Matrix &operator=(const Matrix &B);

    Matrix operator-(const Matrix &B);

    Matrix &operator-=(const Matrix &B);

    Matrix &operator+=(const Matrix &B);

    Matrix operator*(double a) const;

    Matrix &operator*=(double a);

    Matrix operator+(const Matrix &M);

    Matrix operator*(const Matrix &M);

    Matrix &operator*=(const Matrix &M);

    bool operator==(const Matrix &B);

    bool operator!=(const Matrix &B);

    friend std::ostream &operator<<(std::ostream &out, const Matrix &A);

    friend Matrix operator*(double a, const Matrix &A);
};

#endif //MATHMATRIX_MATRIX_H

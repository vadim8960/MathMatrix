
#include "Matrix.h"

unsigned Matrix::err_code = 0;
double Matrix::eps = 0.;
bool Matrix::simple_copy = false;

Matrix::Matrix() {
    this->n = 0;
    this->m = 0;
    this->mat = _NULL;
}

Matrix::Matrix(unsigned n) {
    this->n = n;
    this->m = n;
    this->mat = (double *)malloc(n * n * sizeof(double));
}

Matrix::Matrix(unsigned n, unsigned m) {
    this->n = n;
    this->m = m;
    this->mat = (double *)malloc(n * m * sizeof(double));
}

Matrix::Matrix(double *mat, unsigned n) {
    this->n = n;
    this->m = n;
    this->mat = (double *)malloc(n * n * sizeof(double));
    std::memcpy(this->mat, mat, n * n * sizeof(double));
}

Matrix::Matrix(double *mat, unsigned n, unsigned m) {
    this->n = n;
    this->m = m;
    this->mat = (double *)malloc(this->n * this->m * sizeof(double));
    std::memcpy(this->mat, mat, n * m * sizeof(double));
}

Matrix::Matrix(unsigned n, double a) {
    this->n = n;
    this->m = n;
    this->mat = (double *)calloc(n * n, sizeof(double));
    for (double * i = this->mat; i <= this->mat + n * n; i += (n + 1))
        *i = a;
}

#if __cplusplus >= 201103L
Matrix::Matrix(unsigned n, unsigned m, const std::initializer_list<double> &MIl) {
    if (n * m != MIl.size()) {
        Matrix::err_code = 14;
        return;
    }
    this->n = n;
    this->m = m;
    this->mat = (double *)malloc(n * m * sizeof(double));
    auto it = MIl.begin();
    for (double * i = this->mat; i <= this->mat + n * m; ++i, ++it)
        *i = *it;
}
#endif

Matrix::Matrix(const Matrix &A) {
    this->n = A.n;
    this->m = A.m;
    if (A.simple_copy) {
        this->mat = A.mat;
    } else {
        this->mat = (double *)malloc(A.n * A.m * sizeof(double));
        std::memcpy(this->mat, A.mat, A.n * A.m * sizeof(double));
    }
}

Matrix::~Matrix() {
    this->m = 0;
    this->n = 0;
    if (simple_copy)
        return;
    if (this->mat == _NULL)
        return;
    free(this->mat);
    this->mat = _NULL;
}

Matrix &Matrix::operator=(const Matrix &B) {
    this->n = B.n;
    this->m = B.m;
    if (B.simple_copy) {
        this->mat = B.mat;
    } else {
        this->mat = (double *)realloc(this->mat, B.n * B.m * sizeof(double));
        std::memcpy(this->mat, B.mat, B.n * B.m * sizeof(double));
    }
    return (*this);
}

Matrix Matrix::operator-(const Matrix &B) {
    if (mat == _NULL) {
        Matrix::err_code = 1;
        return Matrix();
    } else if (B.mat == _NULL) {
        Matrix::err_code = 2;
        return Matrix();
    } else if (n != B.n or m != B.m) {
        Matrix::err_code = 12;
        return Matrix();
    }
    Matrix tmp(n, m);
    for (double * i = mat, *j = B.mat, *tmp_prt = tmp.mat; i <= mat + n * m; i++, j++, tmp_prt++)
        *tmp_prt = *i - *j;
    return tmp;
}

Matrix &Matrix::operator-=(const Matrix &B) {
    if (mat == _NULL) {
        Matrix::err_code = 1;
        return *this;
    } else if (B.mat == _NULL) {
        Matrix::err_code = 2;
        return *this;
    } else if (n != B.n or m != B.m) {
        Matrix::err_code = 12;
        return *this;
    }
    for (double * i = mat, *j = B.mat; i <= mat + n * m; i++, j++)
        *i -= *j;
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &B) {
    if (mat == _NULL) {
        Matrix::err_code = 1;
        return *this;
    } else if (B.mat == _NULL) {
        Matrix::err_code = 2;
        return *this;
    } else if (n != B.n or m != B.m) {
        Matrix::err_code = 12;
        return *this;
    }
    for (double * i = mat, *j = B.mat; i <= mat + n * m; i++, j++)
        *i += *j;
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Matrix &A) {
    unsigned max_value_len = 0;
    unsigned tmp_len;
    char tmp_str[20];
    for (unsigned i = 0; i < A.n * A.m; ++i) {
        sprintf(tmp_str, "%g", (A.mat[i] < Matrix::eps) ? 0. : A.mat[i]);
        tmp_len = std::strlen(tmp_str);
        if (tmp_len > max_value_len)
            max_value_len = tmp_len;
    }

    for (int i = 0; i < A.n; ++i) {
        for (int j = 0; j < A.m; ++j)
            out << std::setw(static_cast<int>(max_value_len + 1)) << A.mat[i * A.m + j] << ' ';
        out << '\n';
    }
    return out;
}

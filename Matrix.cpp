
#include "Matrix.h"

#include "errs/err.h"

double Matrix::_eps = 0.;
bool Matrix::_simple_copy = false;

Matrix::Matrix() {
    _crows = 0;
    _ccols = 0;
    _mat = _NULL;
}

Matrix::Matrix(unsigned count_rows) {
    _crows = count_rows;
    _ccols = count_rows;
    _mat = (double *) malloc(count_rows * count_rows * sizeof(double));
}

Matrix::Matrix(unsigned count_rows, unsigned count_cols) {
    _crows = count_rows;
    _ccols = count_cols;
    _mat = (double *) malloc(count_rows * count_cols * sizeof(double));
}

Matrix::Matrix(double *mat, unsigned count_rows) {
    _crows = count_rows;
    _ccols = count_rows;
    _mat = (double *) malloc(count_rows * count_rows * sizeof(double));
    std::memcpy(_mat, mat, count_rows * count_rows * sizeof(double));
}

Matrix::Matrix(double *mat, unsigned count_rows, unsigned count_cols) {
    _crows = count_rows;
    _ccols = count_cols;
    _mat = (double *) malloc(_crows * _ccols * sizeof(double));
    std::memcpy(_mat, mat, count_rows * count_cols * sizeof(double));
}

Matrix::Matrix(unsigned count_rows, double a) {
    _crows = count_rows;
    _ccols = count_rows;
    _mat = (double *) calloc(count_rows * count_rows, sizeof(double));
    for (double *i = _mat; i < _mat + count_rows * count_rows; i += (count_rows + 1))
        *i = a;
}

Matrix::Matrix(std::ifstream &file) {
    double a;
    double *x = _NULL;
    unsigned n1, n2;
    if (file.is_open()) {
        file >> n1 >> n2;
        if (file.eof() && (n1 * n2 != 0)) {
            throw std::invalid_argument(errstr(ERR_NOT_VALID_FILE_DATA));
        }
        x = new double[n1 * n2];
        for (unsigned j = 0; j < n1 * n2; j++) {
            file >> a;
            x[j] = a;
            if (file.eof() && (j + 1 != n1 * n2)) {
                throw std::invalid_argument(errstr(ERR_NOT_VALID_FILE_DATA));
            }
        }

        _crows = n1;
        _ccols = n2;
        _mat = (double *) malloc(n1 * n2 * sizeof(double));
        std::memcpy(_mat, x, n1 * n2 * sizeof(double));
    } else {
        throw std::invalid_argument(errstr(ERR_FILE_NOT_OPEN));
    }
}

Matrix::Matrix(FILE *file) {
    unsigned n1, n2;
    double *a = _NULL;
    if (file == _NULL) {
        throw std::invalid_argument(errstr(ERR_FILE_NOT_OPEN));
    } else {
        fscanf(file, "%d", &n1);
        fscanf(file, "%d", &n2);
        if (feof(file) && (n1 * n2 != 0)) {
            throw std::invalid_argument(errstr(ERR_NOT_VALID_FILE_DATA));
        }
        a = new double[n1 * n2];
        for (unsigned j = 0; j < n1 * n2; j++) {
            fscanf(file, "%lf", &a[j]);
            if (feof(file) && (j + 1 != n1 * n2)) {
                throw std::invalid_argument(errstr(ERR_NOT_VALID_FILE_DATA));
            }
        }
        _crows = n1;
        _ccols = n2;
        _mat = (double *) malloc(n1 * n2 * sizeof(double));
        std::memcpy(_mat, a, n1 * n2 * sizeof(double));
    }
}

#if __cplusplus >= 201103L

Matrix::Matrix(unsigned count_rows, unsigned count_cols, const std::initializer_list<double> &MIl) {
    if (count_rows * count_cols != MIl.size()) {
        throw std::invalid_argument(errstr(ERR_MISMATCH_SIZES_WHEN_INIT_LIST));
    }
    _crows = count_rows;
    _ccols = count_cols;
    _mat = (double *) malloc(count_rows * count_cols * sizeof(double));
    auto it = MIl.begin();
    for (double *i = _mat; i < _mat + count_rows * count_cols; ++i, ++it)
        *i = *it;
}

#endif

Matrix::Matrix(const Matrix &A) {
    _crows = A._crows;
    _ccols = A._ccols;
    if (A._simple_copy) {
        _mat = A._mat;
    } else {
        _mat = (double *) malloc(A._crows * A._ccols * sizeof(double));
        std::memcpy(_mat, A._mat, A._crows * A._ccols * sizeof(double));
    }
}

Matrix::~Matrix() {
    _ccols = 0;
    _crows = 0;
    if (_simple_copy)
        return;
    if (_mat == _NULL)
        return;
    free(_mat);
    _mat = _NULL;
}

Matrix Matrix::transpose() {
    if (_mat != _NULL) {
        Matrix a(_ccols, _crows);
        double *dm = _mat;
        double *da = a._mat;
        for (unsigned l = 1; l <= _ccols; l++) {
            for (unsigned d = 0; d < _crows; d++) {
                *(da) = *(dm);
                da++;
                dm += _ccols;
            }
            dm = _mat + l;
        }
        return a;
    } else {
        throw std::invalid_argument(errstr(ERR_MISSING_FIRST_OPERAND));
    }
}

void Matrix::mult_row_by_const(unsigned int row, double c) {
    if (_mat == _NULL) {
        throw std::invalid_argument(errstr(ERR_MISSING_FIRST_OPERAND));
    } else if (row > _crows) {
        throw std::invalid_argument(errstr(ERR_NON_EXISTENT_MATRIX_ROW));
    }
    double *endptr = _mat + (row + 1) * _ccols;
    for (double *i = _mat + row * _ccols; i < endptr; ++i)
        *i *= c;
}

void Matrix::sum_row_by_const_to_row(unsigned int dest_row, unsigned int mult_row, double c) {
    if (_mat == _NULL) {
        throw std::invalid_argument(errstr(ERR_MISSING_FIRST_OPERAND));
    } else if (dest_row > _crows || mult_row > _crows) {
        throw std::invalid_argument(errstr(ERR_NON_EXISTENT_MATRIX_ROW));
    }
    double *endptr = _mat + (dest_row + 1) * _ccols;
    for (double *i1 = _mat + dest_row * _ccols, *i2 = _mat + mult_row * _ccols; i1 < endptr; ++i1, ++i2)
        *i1 += (*i2 * c);
}

void Matrix::swap_rows(unsigned int row1, unsigned int row2) {
    if (_mat == _NULL) {
        throw std::invalid_argument(errstr(ERR_MISSING_FIRST_OPERAND));
    } else if (row1 > _crows || row2 > _crows) {
        throw std::invalid_argument(errstr(ERR_NON_EXISTENT_MATRIX_ROW));
    }
    double *endptr = _mat + (row1 + 1) * _ccols;
    double tmp;
    for (double *i1 = _mat + row1 * _ccols, *i2 = _mat + row2 * _ccols; i1 < endptr; ++i1, ++i2) {
        if (*i1 != *i2) {
            tmp = *i1;
            *i1 = *i2;
            *i2 = tmp;
        }
    }
}

void Matrix::swap_cols(unsigned col1, unsigned col2) {
    if (_mat == _NULL) {
        throw std::invalid_argument(errstr(ERR_MISSING_FIRST_OPERAND));
    } else if (col1 > _ccols || col2 > _ccols) {
        throw std::invalid_argument(errstr(ERR_NON_EXISTENT_MATRIX_COL));
    }
    double r;
    for (unsigned i = 0; i < _crows; i++) {
        r = _mat[i * _ccols + col1];
        _mat[i * _ccols + col1] = _mat[i * _ccols + col2];
        _mat[i * _ccols + col2] = r;
    }
}

unsigned Matrix::count_col() const {
    return _ccols;
}

unsigned Matrix::count_row() const {
    return _crows;
}

void Matrix::get_row(unsigned int number, double *dest) const {
    if (_mat == _NULL)
        throw std::invalid_argument(errstr(ERR_MISSING_FIRST_OPERAND));
    else if (number > _crows)
        throw std::invalid_argument(errstr(ERR_NON_EXISTENT_MATRIX_ROW));
    memcpy(dest, _mat + (number - 1) * _ccols, _ccols * sizeof(double));
}

void Matrix::get_col(unsigned number, double *dest) const {
    if (_mat == _NULL)
        throw std::invalid_argument(errstr(ERR_MISSING_FIRST_OPERAND));
    else if (number > _ccols)
        throw std::invalid_argument(errstr(ERR_NON_EXISTENT_MATRIX_ROW));
    for (unsigned i = 0; i < _crows; ++i)
        dest[i] = _mat[i * _ccols + number];
}

Matrix Matrix::get_submatrix(unsigned n_row, unsigned n_col, unsigned count_rows, unsigned count_cols) {
    if (_mat == _NULL) {
        throw std::invalid_argument(errstr(ERR_MISSING_FIRST_OPERAND));
    } else if (n_row > _crows || n_row > _ccols) {
        throw std::invalid_argument(errstr(ERR_NON_EXISTENT_SUBMATRIX));
    } else if (n_row + count_rows > _crows) {
        throw std::invalid_argument(errstr(ERR_NON_EXISTENT_MATRIX_ROW));
    } else if (n_row + count_cols > _ccols) {
        throw std::invalid_argument(errstr(ERR_NON_EXISTENT_MATRIX_COL));
    }
    Matrix B(count_rows, count_cols);
    for (int i = 0; i < count_rows; i++) {
        for (int j = 0; j < count_cols; j++) {
            B._mat[i * count_cols + j] = _mat[(n_row + i) * _ccols + n_row + j];
        }
    }
    return B;
}

Matrix Matrix::concatenation(Matrix &a) {
    double *tmp_mat = (double *) malloc((_ccols + a._ccols) * _crows * sizeof(double));
    bool state = true;
    unsigned counter = 0;
    for (double *tmp = tmp_mat; tmp < tmp_mat + (_ccols + a._ccols) * _crows;) {
        if (state) {
            std::memcpy(tmp, _mat + counter * _ccols, _ccols * sizeof(double));
            tmp += _ccols;
            state = false;
        } else {
            std::memcpy(tmp, a._mat + counter * a._ccols, a._ccols * sizeof(double));
            tmp += a._ccols;
            ++counter;
            state = true;
        }
    }
    Matrix retv(tmp_mat, _crows, _ccols + a._ccols);
    return retv;
}

Matrix &Matrix::operator=(const Matrix &B) {
    if (this != &B) {
        _crows = B._crows;
        _ccols = B._ccols;
        if (B._simple_copy) {
            _mat = B._mat;
        } else {
            _mat = (double *) realloc(_mat, B._crows * B._ccols * sizeof(double));
            std::memcpy(_mat, B._mat, B._crows * B._ccols * sizeof(double));
        }
    }
    return (*this);
}

Matrix Matrix::operator-(const Matrix &B) {
    if (_mat == _NULL) {
        throw std::invalid_argument(errstr(ERR_MISSING_FIRST_OPERAND));
    } else if (B._mat == _NULL) {
        throw std::invalid_argument(errstr(ERR_MISSING_SECOND_OPERAND));
    } else if (_crows != B._crows || _ccols != B._ccols) {
        throw std::invalid_argument(errstr(ERR_MISMATCH_SIZES_WHEN_MINUS));
    }
    Matrix tmp(_crows, _ccols);
    double *endptr = _mat + _crows * _ccols;
    for (double *i = _mat, *j = B._mat, *tmp_prt = tmp._mat; i < endptr; i++, j++, tmp_prt++)
        *tmp_prt = *i - *j;
    return tmp;
}

Matrix Matrix::operator+(const Matrix &B) {
    if (_mat == _NULL) {
        throw std::invalid_argument(errstr(ERR_MISSING_FIRST_OPERAND));
    } else if (B._mat == _NULL) {
        throw std::invalid_argument(errstr(ERR_MISSING_SECOND_OPERAND));
    } else if (_crows != B._crows || _ccols != B._ccols) {
        throw std::invalid_argument(errstr(ERR_MISMATCH_SIZES_WHEN_PLUS));
    }
    Matrix tmp(_crows, _ccols);
    double *endptr = _mat + _crows * _ccols;
    for (double *i = _mat, *j = B._mat, *tmp_prt = tmp._mat; i < endptr; i++, j++, tmp_prt++)
        *tmp_prt = *i + *j;
    return tmp;
}
Matrix Matrix::operator*(const Matrix &B) {
    if (_mat == _NULL) {
        throw std::invalid_argument(errstr(ERR_MISSING_FIRST_OPERAND));
    } else if (B._mat == _NULL) {
        throw std::invalid_argument(errstr(ERR_MISSING_SECOND_OPERAND));
    } else if (_ccols != B._crows) {
        throw std::invalid_argument(errstr(ERR_MISMATCH_SIZES_WHEN_MULT));
    }
    Matrix retv(_crows, B._ccols);
    for (int i = 0; i < _crows; ++i) {
        for (int j = 0; j < B._ccols; ++j) {
            *(retv._mat + i * _ccols + j) = 0;
            for (int k = 0; k < _ccols; ++k)
                *(retv._mat + i * _ccols + j) += (*(_mat + i * _ccols + k) * *(B._mat + k * B._ccols + j));
        }
    }
    return retv;
}

Matrix Matrix::operator*(double a) const {
    if (_mat == _NULL) {
        throw std::invalid_argument(errstr(ERR_MISSING_FIRST_OPERAND));
    }
    Matrix tmp(_crows, _ccols);
    double *end_ptr = _mat + _crows * _ccols;
    for (double *i = _mat, *dest = tmp._mat; i < end_ptr; ++i, ++dest)
        *dest = *i * a;
    return tmp;
}

Matrix &Matrix::operator-=(const Matrix &B) {
    Matrix retv = *this - B;
    *this = retv;
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &B) {
    Matrix retv = *this + B;
    *this = retv;
    return *this;
}

Matrix &Matrix::operator*=(double a) {
    if (_mat == _NULL) {
        throw std::invalid_argument(errstr(ERR_MISSING_FIRST_OPERAND));
    }
    double *end_ptr = _mat + _crows * _ccols;
    for (double *i = _mat; i < end_ptr; ++i)
        *i *= a;
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &B) {
    Matrix retv = *this * B;
    *this = retv;
    return *this;
}

bool Matrix::operator==(const Matrix &B) {
    if (_crows != B._crows || _ccols != B._ccols)
        return false;
    double *endptr = _mat + _crows * _ccols;
    for (double *a1 = _mat, *a2 = B._mat; a1 < endptr; ++a1, ++a2)
        if (*a1 != *a2)
            return false;
    return true;
}

bool Matrix::operator!=(const Matrix &B) {
    return !(*this == B);
}

double *Matrix::operator[](unsigned i) {
    return &_mat[i * _ccols];
}

std::ostream &operator<<(std::ostream &out, const Matrix &A) {
    char tmp_str[20];
    out << A._crows << " x " << A._ccols << '\n';
    for (int i = 0; i < A._crows; ++i) {
        for (int j = 0; j < A._ccols; ++j) {
            sprintf(tmp_str, "%2.12g ", fabs(A._mat[i * A._ccols + j]) < A._eps ? 0. : A._mat[i * A._ccols + j]);
            out << tmp_str;
        }
        out << '\n';
    }
    return out;
}

Matrix operator*(double a, const Matrix &A) {
    if (A._mat == _NULL) {
        throw std::invalid_argument(errstr(ERR_MISSING_SECOND_OPERAND));
    }
    return A * a;
}

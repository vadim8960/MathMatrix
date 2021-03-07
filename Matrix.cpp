
#include "Matrix.h"

unsigned Matrix::err_code = 0;
double Matrix::eps = 0.;
bool Matrix::simple_copy = false;

Matrix::Matrix() {
    this->_crows = 0;
    this->_ccols = 0;
    this->_mat = _NULL;
}

Matrix::Matrix(unsigned n) {
    this->_crows = n;
    this->_ccols = n;
    this->_mat = (double *) malloc(n * n * sizeof(double));
}

Matrix::Matrix(unsigned n, unsigned m) {
    this->_crows = n;
    this->_ccols = m;
    this->_mat = (double *) malloc(n * m * sizeof(double));
}

Matrix::Matrix(double *mat, unsigned n) {
    this->_crows = n;
    this->_ccols = n;
    this->_mat = (double *) malloc(n * n * sizeof(double));
    std::memcpy(this->_mat, mat, n * n * sizeof(double));
}

Matrix::Matrix(double *mat, unsigned n, unsigned m) {
    this->_crows = n;
    this->_ccols = m;
    this->_mat = (double *) malloc(this->_crows * this->_ccols * sizeof(double));
    std::memcpy(this->_mat, mat, n * m * sizeof(double));
}

Matrix::Matrix(unsigned n, double a) {
    this->_crows = n;
    this->_ccols = n;
    this->_mat = (double *) calloc(n * n, sizeof(double));
    for (double *i = this->_mat; i <= this->_mat + n * n; i += (n + 1))
        *i = a;
}

Matrix::Matrix(std::ifstream& file) {
    Matrix::err_code = 0;
    double a;
    double *x = _NULL;
    unsigned n1, n2;
    if (file.is_open()) {
        file >> n1 >> n2;
        if (file.eof() && (n1 * n2 != 0)) {
            Matrix::err_code = 32;
            n1 = 0;
            n2 = 0;
            x = _NULL;
        }
        x = new double[n1 * n2];
        for (unsigned j = 0; j < n1 * n2; j++) {
            file >> a;
            x[j] = a;
            if (file.eof() && (j + 1 != n1 * n2)) {
                Matrix::err_code = 32;
                n1 = 0;
                n2 = 0;
                x = _NULL;
                break;
            }
        }

        this->_crows = n1;
        this->_ccols = n2;
        this->_mat = (double *) malloc(n1 * n2 * sizeof(double));
        std::memcpy(this->_mat, x, n1 * n2 * sizeof(double));
    } else {
        Matrix::err_code = 31;
        this->_crows = 0;
        this->_ccols = 0;
        this->_mat = _NULL;
    }
}

Matrix::Matrix(FILE *file) {
    Matrix::err_code = 0;
    unsigned n1, n2;
    double *a = _NULL;
    if (file == _NULL) {
        Matrix::err_code = 31;
        this->_crows = 0;
        this->_ccols = 0;
        this->_mat = _NULL;
    } else {
        fscanf(file, "%d", &n1);
        fscanf(file, "%d", &n2);
        if (feof(file) && (n1 * n2 != 0)) {
            Matrix::err_code = 32;
            n1 = 0;
            n2 = 0;
            a = _NULL;
        }
        a = new double[n1 * n2];
        for (unsigned j = 0; j < n1 * n2; j++) {
            fscanf(file, "%lf", &a[j]);
            if (feof(file) && (j + 1 != n1 * n2)) {
                Matrix::err_code = 32;
                n1 = 0;
                n2 = 0;
                a = _NULL;
                break;
            }
        }
        this->_crows = n1;
        this->_ccols = n2;
        this->_mat = (double *) malloc(n1 * n2 * sizeof(double));
        std::memcpy(this->_mat, a, n1 * n2 * sizeof(double));
    }
}

#if __cplusplus >= 201103L

Matrix::Matrix(unsigned n, unsigned m, const std::initializer_list<double> &MIl) {
    Matrix::err_code = 0;
    if (n * m != MIl.size()) {
        Matrix::err_code = 14;
        return;
    }
    this->_crows = n;
    this->_ccols = m;
    this->_mat = (double *) malloc(n * m * sizeof(double));
    auto it = MIl.begin();
    for (double *i = this->_mat; i <= this->_mat + n * m; ++i, ++it)
        *i = *it;
}

#endif

Matrix::Matrix(const Matrix &A) {
    this->_crows = A._crows;
    this->_ccols = A._ccols;
    if (A.simple_copy) {
        this->_mat = A._mat;
    } else {
        this->_mat = (double *) malloc(A._crows * A._ccols * sizeof(double));
        std::memcpy(this->_mat, A._mat, A._crows * A._ccols * sizeof(double));
    }
}

Matrix::~Matrix() {
    this->_ccols = 0;
    this->_crows = 0;
    if (simple_copy)
        return;
    if (this->_mat == _NULL)
        return;
    free(this->_mat);
    this->_mat = _NULL;
}

Matrix &Matrix::concatenation(Matrix &a) {
    double *tmp_mat = (double *) malloc((this->_ccols + a._ccols) * this->_crows * sizeof(double));
    bool state = true;
    unsigned counter = 0;
    for (double *tmp = tmp_mat; tmp < tmp_mat + (this->_ccols + a._ccols) * this->_crows;) {
        if (state) {
            std::memcpy(tmp, this->_mat + counter * this->_ccols, this->_ccols * sizeof(double));
            tmp += this->_ccols;
            state = false;
        } else {
            std::memcpy(tmp, a._mat + counter * a._ccols, a._ccols * sizeof(double));
            tmp += a._ccols;
            ++counter;
            state = true;
        }
    }
    free(this->_mat);
    this->_mat = tmp_mat;
    this->_ccols += a._ccols;
    return (*this);
}

Matrix Matrix::transpose() {
    Matrix::err_code = 0;
    if (this->_mat != _NULL) {
        Matrix a(this->_ccols, this->_crows);
        double *dm = this->_mat;
        double *da = a._mat;
        for (unsigned l = 1; l <= this->_ccols; l++) {
            for (unsigned d = 0; d < this->_crows; d++) {
                *(da) = *(dm);
                da++;
                dm += this->_ccols;
            }
            dm = this->_mat + l;
        }
        return a;
    } else {
        Matrix::err_code = 1;
        return Matrix();
    }
}

void Matrix::mult_row_by_const(unsigned int row, double c) {
    Matrix::err_code = 0;
    if (_mat == _NULL) {
        Matrix::err_code = 1;
        return;
    } else if (row > _crows) {
        Matrix::err_code = 22;
        return;
    }
    double *pfin = _mat + (row + 1) * _ccols;
    for (double *i = _mat + row * _ccols; i < pfin; ++i)
        *i *= c;
}

void Matrix::swap_rows(unsigned int row1, unsigned int row2) {
    Matrix::err_code = 0;
    if (row1 > _crows || row2 > _crows) {
        Matrix::err_code = 22;
        return;
    }
    double *pfin = _mat + (row1 + 1) * _ccols;
    double tmp;
    for (double *i1 = _mat + row1 * _ccols, *i2 = _mat + row2 * _ccols; i1 < pfin; ++i1, ++i2) {
        if (*i1 != *i2) {
            tmp = *i1;
            *i1 = *i2;
            *i2 = tmp;
        }
    }
}

void Matrix::swap_cols(unsigned col1, unsigned col2){
    Matrix::err_code = 0;
    if(_mat == _NULL){
        Matrix::err_code = 1;
        return;
    }else if(col1 > _ccols || col2 > _ccols){
        Matrix::err_code = 23;
        return;
    }
    double r;
    for(unsigned i = 0; i < _crows; i ++){
        r = _mat[i * _ccols + col1];
        _mat[i * _ccols + col1]= _mat[i * _ccols + col2];
        _mat[i * _ccols + col2] = r;
    }
}

void Matrix::sum_row_by_const_to_row(unsigned int dest_row, unsigned int mult_row, double c) {
    Matrix::err_code = 0;
    if (_mat == _NULL) {
        Matrix::err_code = 1;
        return;
    } else if (dest_row > _crows || mult_row > _crows) {
        Matrix::err_code = 22;
        return;
    }
    double *pfin = _mat + (dest_row + 1) * _ccols;
    for (double *i1 = _mat + dest_row * _ccols, *i2 = _mat + mult_row * _ccols; i1 < pfin; ++i1, ++i2)
        *i1 += (*i2 * c);
}

Matrix &Matrix::operator=(const Matrix &B) {
    if (this != &B) {
        this->_crows = B._crows;
        this->_ccols = B._ccols;
        if (B.simple_copy) {
            this->_mat = B._mat;
        } else {
            this->_mat = (double *) realloc(this->_mat, B._crows * B._ccols * sizeof(double));
            std::memcpy(this->_mat, B._mat, B._crows * B._ccols * sizeof(double));
        }
    }
    return (*this);
}

Matrix Matrix::operator-(const Matrix &B) {
    Matrix::err_code = 0;
    if (_mat == _NULL) {
        Matrix::err_code = 1;
        return Matrix();
    } else if (B._mat == _NULL) {
        Matrix::err_code = 2;
        return Matrix();
    } else if (_crows != B._crows || _ccols != B._ccols) {
        Matrix::err_code = 12;
        return Matrix();
    }
    Matrix tmp(_crows, _ccols);
    double *pfin = _mat + _crows * _ccols;
    for (double *i = _mat, *j = B._mat, *tmp_prt = tmp._mat; i < pfin; i++, j++, tmp_prt++)
        *tmp_prt = *i - *j;
    return tmp;
}

Matrix &Matrix::operator-=(const Matrix &B) {
    Matrix::err_code = 0;
    if (_mat == _NULL) {
        Matrix::err_code = 1;
        return *this;
    } else if (B._mat == _NULL) {
        Matrix::err_code = 2;
        return *this;
    } else if (_crows != B._crows || _ccols != B._ccols) {
        Matrix::err_code = 12;
        return *this;
    }
    double *pfin = _mat + _crows * _ccols;
    for (double *i = _mat, *j = B._mat; i < pfin; i++, j++)
        *i -= *j;
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &B) {
    Matrix::err_code = 0;
    if (_mat == _NULL) {
        Matrix::err_code = 1;
        return *this;
    } else if (B._mat == _NULL) {
        Matrix::err_code = 2;
        return *this;
    } else if (_crows != B._crows || _ccols != B._ccols) {
        Matrix::err_code = 11;
        return *this;
    }
    double *pfin = _mat + _crows * _ccols;
    for (double *i = _mat, *j = B._mat; i < pfin; i++, j++)
        *i += *j;
    return *this;
}

Matrix Matrix::operator*(double a) const {
    Matrix::err_code = 0;
    if (_mat == _NULL) {
        Matrix::err_code = 1;
        return Matrix();
    }
    Matrix tmp(_crows, _ccols);
    double *end_ptr = _mat + _crows * _ccols;
    for (double *i = _mat, *dest = tmp._mat; i < end_ptr; ++i, ++dest)
        *dest = *i * a;
    return tmp;
}

Matrix &Matrix::operator*=(double a) {
    Matrix::err_code = 0;
    if (_mat == _NULL) {
        Matrix::err_code = 1;
        return *this;
    }
    double *end_ptr = _mat + _crows * _ccols;
    for (double *i = _mat; i < end_ptr; ++i)
        *i *= a;
    return *this;
}

Matrix Matrix::operator+(const Matrix &B) {
    Matrix::err_code = 0;
    if (_mat == _NULL) {
        Matrix::err_code = 1;
        return Matrix();
    } else if (B._mat == _NULL) {
        Matrix::err_code = 2;
        return Matrix();
    } else if (_crows != B._crows || _ccols != B._ccols) {
        Matrix::err_code = 11;
        return Matrix();
    }
    Matrix tmp(_crows, _ccols);
    double *pfin = _mat + _crows * _ccols;
    for (double *i = _mat, *j = B._mat, *tmp_prt = tmp._mat; i < pfin; i++, j++, tmp_prt++)
        *tmp_prt = *i + *j;
    return tmp;
}

Matrix Matrix::operator*(const Matrix &B) {
    Matrix::err_code = 0;
    if (_mat == _NULL) {
        Matrix::err_code = 1;
        return Matrix();
    } else if (B._mat == _NULL) {
        Matrix::err_code = 2;
        return Matrix();
    } else if (_ccols != B._crows) {
        Matrix::err_code = 13;
        return Matrix();
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

Matrix &Matrix::operator*=(const Matrix &B) {
    Matrix retv = *this * B;
    *this = retv;
    return *this;
}

bool Matrix::operator==(const Matrix &B) {
    if (_crows != B._crows || _ccols != B._ccols)
        return false;
    double *pfin = _mat + _crows * _ccols;
    for (double *a1 = _mat, *a2 = B._mat; a1 < pfin; ++a1, ++a2)
        if (*a1 != *a2)
            return false;
    return true;
}

bool Matrix::operator!=(const Matrix &B) {
    return !(*this == B);
}

double *Matrix::operator[](unsigned i) {
    return &this->_mat[i * this->_ccols];
}

std::ostream &operator<<(std::ostream &out, const Matrix &A) {
    char tmp_str[20];
    out << A._crows << " x " << A._ccols << '\n';
    for (int i = 0; i < A._crows; ++i) {
        for (int j = 0; j < A._ccols; ++j) {
            sprintf(tmp_str, "%2.12g ", fabs(A._mat[i * A._ccols + j]) < A.eps ? 0. : A._mat[i * A._ccols + j]);
            out << tmp_str;
        }
        if (A._ccols % 8 == 0)
            out << '\\';
        out << '\n';
    }
    return out;
}

Matrix operator*(double a, const Matrix &A) {
    Matrix::err_code = 0;
    if (A._mat == _NULL) {
        Matrix::err_code = 2;
        return Matrix();
    }
    return A * a;
}

unsigned Matrix::count_col() const {
    Matrix::err_code = 0;
    if (_mat == _NULL)
        Matrix::err_code = 1;
    return _ccols;
}

unsigned Matrix::count_row() const {
    Matrix::err_code = 0;
    if (_mat == _NULL)
        Matrix::err_code = 1;
    return _crows;
}

void Matrix::get_row(unsigned int number, double *dest) const {
    Matrix::err_code = 0;
    if (_mat == _NULL)
        Matrix::err_code = 1;
    else if (number > _crows)
        Matrix::err_code = 22;
    memcpy(dest, _mat + (number - 1) * _ccols, _ccols * sizeof(double));
}

void Matrix::get_col(unsigned number, double *dest) const {
    Matrix::err_code = 0;
    if (_mat == _NULL)
        Matrix::err_code = 1;
    else if (number > _ccols)
        Matrix::err_code = 22;
    for (unsigned i = 0; i < this->_crows; ++i)
        dest[i] = this->_mat[i * this->_ccols + number];
}

Matrix Matrix::get_submatrix(unsigned x, unsigned y, unsigned rows, unsigned cols) {
    Matrix::err_code = 0;
    if (_mat == _NULL) {
        Matrix::err_code = 1;
        return Matrix();
    } else if (x > _crows || y > _ccols) {
        Matrix::err_code = 24;
        return Matrix();
    } else if (x - 1 + rows > this->_crows) {
        Matrix::err_code = 22;
        return Matrix();
    } else if (y - 1 + cols > this->_ccols) {
        Matrix::err_code = 23;
        return Matrix();
    }
    Matrix B(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            B._mat[i * cols + j] = this->_mat[(x + i) * _ccols + y + j];
        }
    }
    return B;
}

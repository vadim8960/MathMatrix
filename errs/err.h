//
// Created by vadim on 08.03.2021.
//

#ifndef METHGAUSS_ERR_H
#define METHGAUSS_ERR_H

#include <stdexcept>
#include <string>

enum Err_e {
    ERR_OK                            = 0,
    ERR_MISSING_FIRST_OPERAND         = 1,
    ERR_MISSING_SECOND_OPERAND        = 2,
    ERR_MISMATCH_SIZES_WHEN_PLUS      = 3,
    ERR_MISMATCH_SIZES_WHEN_MINUS     = 4,
    ERR_MISMATCH_SIZES_WHEN_MULT      = 5,
    ERR_MISMATCH_SIZES_WHEN_INIT_LIST = 6,
    ERR_NON_EXISTENT_MATRIX_ELEMENT   = 7,
    ERR_NON_EXISTENT_MATRIX_ROW       = 8,
    ERR_NON_EXISTENT_MATRIX_COL       = 9,
    ERR_NON_EXISTENT_SUBMATRIX        = 10,
    ERR_FILE_NOT_OPEN                 = 11,
    ERR_NOT_VALID_FILE_DATA           = 12,
    ERR_MISMATCH_SIZES_WHEN_INVERT    = 13
};

std::string errstr(Err_e err_code) {
    switch (err_code) {
        case ERR_OK:
            return "Matrix: success";

        case ERR_MISSING_FIRST_OPERAND:
            return "Matrix: the first or only operand is missing";

        case ERR_MISSING_SECOND_OPERAND:
            return "Matrix: the second operand is missing";

        case ERR_MISMATCH_SIZES_WHEN_PLUS:
            return "Matrix: mismatch of sizes when performing operations + or +=";

        case ERR_MISMATCH_SIZES_WHEN_MINUS:
            return "Matrix: mismatch of sizes when performing operations - or -=";

        case ERR_MISMATCH_SIZES_WHEN_MULT:
            return "Matrix: mismatch of sizes when performing operations * or *=";

        case ERR_MISMATCH_SIZES_WHEN_INIT_LIST:
            return "Matrix: mismatch of sizes when initializing a matrix from the std::initializer_list";

        case ERR_NON_EXISTENT_MATRIX_ELEMENT:
            return "Matrix: an attempt to obtain or interact with a non-existent matrix element";

        case ERR_NON_EXISTENT_MATRIX_ROW:
            return "Matrix: trying to get or interact with a non-existent matrix row";

        case ERR_NON_EXISTENT_MATRIX_COL:
            return "Matrix: trying to get or interact with a non-existent matrix column";

        case ERR_NON_EXISTENT_SUBMATRIX:
            return "Matrix: attempt to obtain a non-existent submatrix";

        case ERR_FILE_NOT_OPEN:
            return "Matrix: file not open";

        case ERR_NOT_VALID_FILE_DATA:
            return "Matrix: lack of data to read the required matrix from the file";

        case ERR_MISMATCH_SIZES_WHEN_INVERT:
            return "Matrix: when looking for an inverse matrix, you need a square matrix";
    }
    return "Matrix: undefined error";
}

#endif //METHGAUSS_ERR_H

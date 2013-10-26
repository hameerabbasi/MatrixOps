#ifndef MATRIXLL_H
#define MATRIXLL_H

#include "Matrix.h"
#include "SquareMatrix.h"

class MatrixLL
{
private:
    struct MatrixLLElem
    {
        Matrix elem;
        MatrixLLElem* next;
        MatrixLLElem(const Matrix& m1): elem(m1), next(NULL)
        { }
    };
    MatrixLLElem* start;
public:
    MatrixLL();
    Matrix& elem(const int index);
    int getlength();
    void append(const Matrix& m1);
    void deleteelem(const int index);
    ~MatrixLL();
};

#endif

// SquareMatrix.h
// Basic definition of the SquareMatrix class.

#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "Matrix.h"

class SquareMatrix: public Matrix
{
public:
    SquareMatrix(int dimension);
    SquareMatrix();
    SquareMatrix(const SquareMatrix& sm);
    SquareMatrix(const Matrix& m1);
    inline int getdimension() const;
    static SquareMatrix identityMatrix(int dimension);
    SquareMatrix& operator =(const SquareMatrix& sm);
    SquareMatrix& operator =(const Matrix& m1);
    SquareMatrix inverse() const;
    complex<double> det() const;
};

#endif

#include "SquareMatrix.h"
#include <complex>

SquareMatrix::SquareMatrix(int dimension):
Matrix(dimension, dimension) { }

SquareMatrix::SquareMatrix()
{
    // Cannot create matrix without dimension
    throw "Square Matrix must have dimension";
}

SquareMatrix::SquareMatrix(const SquareMatrix& sm):
Matrix(sm){ }

SquareMatrix::SquareMatrix(const Matrix& m1): Matrix(m1)
{
    // Check that the rows and cols are equal
    if(m1.getrows() != m1.getcols())
        throw "Matrix isn't square";
}

inline int SquareMatrix::getdimension() const
{
    return getrows();
}

SquareMatrix SquareMatrix::identityMatrix(int dimension)
{
    SquareMatrix temp(dimension);
    
    for(int i = 1; i <= dimension; i++)
    {
        for(int j = 1; j <= dimension; j++)
        {
            temp.elem(i, j) = ((i == j) ? 1.0 : 0.0);
        }
    }
    
    return SquareMatrix(temp);
}

SquareMatrix& SquareMatrix::operator =(const SquareMatrix& sm)
{
    Matrix::operator =(sm);

    return *this;
}

SquareMatrix& SquareMatrix::operator =(const Matrix& m1)
{
    if(m1.getrows() != m1.getcols())
        throw "Cannot assign non-square Matrix to a SquareMatrix";

    Matrix::operator =(m1);

    return *this;
}

SquareMatrix SquareMatrix::inverse() const
{
    Matrix temp(augment(SquareMatrix::identityMatrix(getdimension())));

    temp = temp.rowreduce();

    if(temp.getelem(getdimension(), getdimension()) == 0.0)
        throw "Matrix is singular";

    return SquareMatrix(temp.extract(getdimension() + 1, false));
}

complex<double> SquareMatrix::det() const
{
    complex<double> determinant = 1.0;
    SquareMatrix temp(*this);
    int lead = 0;
    for(int r = 0; r < getrows(); r++)
    {
        if(getcols() <= lead)
            goto stop;

        int i = r;

        while(temp.getelem(i + 1, lead + 1) == 0.0)
        {
            i++;
            if(getrows() == i)
            {
                i = r;
                lead++;
                if(getcols() == lead)
                    goto stop;
            }
        }
        if(i != r)
        {
            temp.rowreplace(i + 1, r + 1);
            determinant *= -1.0;
        }

        determinant *= temp.getelem(r + 1, lead + 1);
        temp.rowdiv(r + 1, temp.getelem(r + 1, lead + 1));

        for(i = r + 1; i < getrows(); i++)
        {
            temp.rowmuladd(i + 1, r + 1, -temp.getelem(i + 1, lead + 1));
        }

        lead++;
    }

    stop:
    if(temp.getelem(getdimension(), getdimension()) == 0.0)
        return 0.0;
    else
        return determinant;
}
// Matrix.cpp
// The basic functions and operators of the Matrix class.

#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include <complex>

using namespace std;

Matrix::Matrix(const int nrows, const int ncols):
    rows(nrows), cols(ncols)
{
    // Check dimensions before creating matrix.
    if(nrows < 1)
        throw "Number of rows must be greater than 0.";
    if(ncols < 1)
        throw "Number of cols must be greater than 0.";
    
    // Create dynamic 2-dimensional complex<double> array
    mat = new complex<double>*[nrows];
    
    for(int i = 0; i < nrows; i++)
    {
        *(mat + i) = new complex<double>[ncols];
    }
}

Matrix::Matrix(const Matrix& m1):
    rows(m1.getrows()), cols(m1.getcols())
{
    // Create new Matrix with rows and columns the same as the
    // supplied Matrix, and set elements equal to the supplied
    // Matrix.

    mat = new complex<double>*[m1.getrows()];
    
    for(int i = 0; i < m1.getrows(); i++)
    {
        *(mat + i) = new complex<double>[m1.getcols()];

        for(int j = 0; j < m1.getcols(); j++)
        {
            // Use (i + 1, j + 1) as the loop runs from 0 to
            // (rows - 1) and 0 to (cols - 1) whereas we set
            // elements from 1 to rows and 1 to cols.
            elem(i + 1, j + 1) = m1.getelem(i + 1, j + 1);
        }
    }
}

Matrix::Matrix():
    rows(0), cols(0)
{
    // Must provide dimensions for a matrix, so we exit if
    // they aren't provided.
    mat = 0;
    // Used as default constructor always exists, and may
    // initialize to invalid values.
    throw "Cannot create matrix without order";
}

Matrix::~Matrix()
{
    // Free up memory for complex<double> arrays
    for(int i = 0; i < rows; i++)
    {
        delete [] *(mat + i);
        *(mat + i) = 0;
    }

    // Free up memory for original complex<double>* array
    delete [] mat;
    mat = 0;
}

inline int Matrix::getrows() const
{
    return rows;
}

inline int Matrix::getcols() const
{
    return cols;
}

inline complex<double>& Matrix::elem(const int row, const int col)
{
    // Check dimensions before returning element
    if(row > getrows() || row < 1)
        throw "Row out of bounds.";
    if(col > getcols() || col < 1)
        throw "Col out of bounds.";

    // Keep it so that the first element is (1, 1).
    return *(*(mat + row - 1) + col - 1); 
}

inline complex<double> Matrix::getelem(const int row, const int col) const
{
    if(row > getrows() || row < 1)
        throw "Row out of bounds.";
    if(col > getcols() || col < 1)
        throw "Col out of bounds.";

    return *(*(mat + row - 1) + col - 1); 
}

void Matrix::rowreplace(const int row1, const int row2)
{
    // Check that both rows are within range and not equal.
    if(row1 > getrows() || row1 < 1)
        throw "Row1 out of bounds.";
    if(row2 > getrows() || row2 < 1)
        throw "Row2 out of bounds.";
    if(row1 == row2)
        throw "Row1 cannot be equal to row2.";

    // Swap each element in rows.
    complex<double> temp;
    for(int i = 1; i <= getcols(); i++)
    {
        temp = getelem(row1, i);
        elem(row1, i) = getelem(row2, i);
        elem(row2, i) = temp;
    }
}

void Matrix::rowdiv(const int row, const complex<double> c)
{
    // Check row is in range and c isn't 0.
    if(row > getrows() || row < 1)
        throw "Row out of bounds.";
    if(c == 0.0)
        throw "C cannot be 0.";

    // Multiply each element in row by c.
    complex<double> temp, element;
    for(int i = 1; i <= getcols(); i++)
    {
        temp = getelem(row, i) / c;
        element = getelem(row, i);
        if((element != 0.0) && (abs((temp - 1.0)/element) <= 1.0E-7))
        {
            elem(row, i) = 1.0;
        }
        else
        {
            elem(row, i) = temp;
        }
    }
}

void Matrix::rowmuladd(const int row1, const int row2, const complex<double> c)
{
    // Check both rows are in range, not equal, and c isn't 0.
    if(row1 > getrows() || row1 < 1)
        throw "Row1 out of bounds.";
    if(row2 > getrows() || row2 < 1)
        throw "Row2 out of bounds.";
    if(row1 == row2)
        throw "Row1 cannot be equal to row2.";

    // Add constant multiple of each element on one row to
    // another
    complex<double> temp, element;
    for(int i = 1; i <= getcols(); i++)
    {
        temp = getelem(row1, i) + (c * getelem(row2, i));
        if(getelem(row1, i) != 0.0)
            element = getelem(row1, i);
        else if(getelem(row2, i) != 0.0)
            element = getelem(row2, i);
        else
            element = 0.0;
        if(element != 0.0)
        {
            if(abs(temp/element) <= 1.0E-7)
            {
                elem(row1, i) = 0.0;
            }
            else if(abs((temp - 1.0)/element) <= 1.0E-7)
            {
                elem(row1, i) = 1.0;
            }
            else
            {
                elem(row1, i) = temp;
            }
        }
        else
        {
            elem(row1, i) = 0.0;
        }
    }
}

Matrix& Matrix::operator =(const Matrix& m1)
{
    // If addresses are equal, do nothing
    if(this != &m1)
    {
        // If order isn't equal, make it equal
        if((getrows() != m1.getrows()) || (getcols() != m1.getcols()))
        {
            // Delete original array
            for(int i = 0; i < getrows(); i++)
            {
                delete [] *(mat + i);
                *(mat + i) = 0;
            }

            delete [] mat;
            mat = 0;
            
            // Forcefully change value of rows and cols.
            *(const_cast<int*>(&rows)) = m1.getrows();
            *(const_cast<int*>(&cols)) = m1.getcols();
            
            // Declare a new matrix with the same dimensions
            // dimensions as m1.
            mat = new complex<double>*[getrows()];
    
            for(int i = 0; i < getrows(); i++)
            {
                *(mat + i) = new complex<double>[getcols()];
            }
        }

        // After dimensions are made equal, if necessary,
        // copy the elements of m1 into the Matrix on the
        // left side of the = sign.
        for(int i = 1; i <= getrows(); i++)
        {
            for(int j = 1; j <= getcols(); j++)
            {
                elem(i, j) = m1.getelem(i, j);
            }
        }
    }
    return *this;
}

Matrix& Matrix::operator +=(const Matrix& m1)
{
    // Check dimensions are equal.
    if((getrows() != m1.getrows()) || (getcols() != m1.getcols()))
        throw "Incompatible dimensions for addition.";

    // Add one matrix's elements to the other.
    for(int i = 1; i <= getrows(); i++)
    {
        for(int j = 1; j <= getcols(); j++)
        {
            elem(i, j) += m1.getelem(i, j);
        }
    }
    return *this;
}

Matrix& Matrix::operator -=(const Matrix& m1)
{
    if((getrows() != m1.getrows()) || (getcols() != m1.getcols()))
        throw "Incompatible dimensions for subtraction.";

    for(int i = 1; i <= getrows(); i++)
    {
        for(int j = 1; j <= getcols(); j++)
        {
            elem(i, j) -= m1.getelem(i, j);
        }
    }
    return *this;
}

Matrix& Matrix::operator *=(const complex<double> c)
{
    // Multiply each element of matrix by constant.
    for(int i = 1; i <= getrows(); i++)
    {
        for(int j = 1; j <= getcols(); j++)
        {
            elem(i, j) *= c;
        }
    }
    return *this;
}

bool Matrix::operator ==(const Matrix& m1) const
{
    if(this == &m1)
    {
        return true;
    }
    else if((getrows() != m1.getrows()) || (getcols() != m1.getcols()))
    {
        return false;
    }
    else
    {
        for(int i = 1; i <= getrows(); i++)
        {
            for(int j = 1; j <= getcols(); j++)
            {
                if(getelem(i, j) != m1.getelem(i, j))
                {
                    return false;
                }
            }
        }

        return true;
    }
}

bool Matrix::operator !=(const Matrix& m1) const
{
    if(this == &m1)
    {
        return false;
    }
    else if((getrows() != m1.getrows()) || (getcols() != m1.getcols()))
    {
        return true;
    }
    else
    {
        for(int i = 1; i <= getrows(); i++)
        {
            for(int j = 1; j <= getcols(); j++)
            {
                if(getelem(i, j) != m1.getelem(i, j))
                {
                    return true;
                }
            }
        }

        return false;
    }
}

Matrix Matrix::operator +(const Matrix& m1) const
{
    // Check compatibility for addition.
    if((getrows() != m1.getrows()) || (getcols() != m1.getcols()))
        throw "Incompatible dimensions for addition.";

    // Declare temporary Matrix and set each of its elements
    // equal to the sum of the corresponding elements of the
    // supplied matrices
    Matrix temp(m1.getrows(), m1.getcols());
    for(int i = 1; i <= m1.getrows(); i++)
    {
        for(int j = 1; j <= m1.getcols(); j++)
        {
            temp.elem(i, j) = getelem(i, j) + m1.getelem(i, j);
        }
    }

    // Return the temporary matrix.
    return Matrix(temp);
}

Matrix Matrix::operator -(const Matrix& m1) const
{
    if((getrows() != m1.getrows()) || (getcols() != m1.getcols()))
        throw "Incompatible dimensions for subtraction.";

    Matrix temp(m1.getrows(), m1.getcols());
    for(int i = 1; i <= m1.getrows(); i++)
    {
        for(int j = 1; j <= m1.getcols(); j++)
        {
            temp.elem(i, j) = getelem(i, j) - m1.getelem(i, j);
        }
    }

    return Matrix(temp);
}

Matrix Matrix::operator *(const Matrix& m1) const
{
    // Check compatibility for matrix multiplication.
    if(getcols() != m1.getrows())
        throw "Incompatible dimensions for matrix multiplication.";

    // Multiply matrices in the usual manner.
    Matrix temp(getrows(), m1.getcols());
    for(int i = 1; i <= getrows(); i++)
    {
        for(int j = 1; j <= m1.getcols(); j++)
        {
            temp.elem(i, j) = 0.0;
            for(int k = 1; k <= getcols(); k++)
            {
                temp.elem(i, j) += getelem(i, k) * m1.getelem(k, j);
            }
        }
    }

    return Matrix(temp);
}

Matrix Matrix::operator *(const complex<double> c) const
{
    Matrix temp(getrows(), getcols());

    for(int i = 1; i <= getrows(); i++)
    {
        for(int j = 1; j <= getcols(); j++)
        {
            temp.elem(i, j) = c * getelem(i, j);
        }
    }

    return Matrix(temp);
}

Matrix Matrix::rowreduce() const
{
    Matrix temp(*this);
    int lead = 0;
    for(int r = 0; r < getrows(); r++)
    {
        if(getcols() <= lead)
            return Matrix(temp);

        int i = r;

        while(temp.getelem(i + 1, lead + 1) == 0.0)
        {
            i++;
            if(getrows() == i)
            {
                i = r;
                lead++;
                if(getcols() == lead)
                    return Matrix(temp);
            }
        }
        if(i != r)
            temp.rowreplace(i + 1, r + 1);

        temp.rowdiv(r + 1, temp.getelem(r + 1, lead + 1));

        for(i = 0; i < getrows(); i++)
        {
            if(i != r)
            {
                temp.rowmuladd(i + 1, r + 1, -temp.getelem(i + 1, lead + 1));
            }
        }

        lead++;
    }

    return Matrix(temp);
}

Matrix Matrix::augment(const Matrix& m1) const
{
    // Check that rows are equal
    if(getrows() != m1.getrows())
        throw "Invalid dimensions for augmentation";

    // Calculate total columns, and create temporary matrix.
    int ncols = getcols() + m1.getcols();
    Matrix temp(getrows(), ncols);

    // Augment the matrices
    for(int i = 1; i <= getrows(); i++)
    {
        for(int j = 1; j <= ncols; j++)
        {
            // If the cols are low enough,
            if(j <= getcols())
            {
                // take elements from the first matrix
                temp.elem(i, j) = getelem(i, j);
            }
            else
            {
                // otherwise from the second matrix
                temp.elem(i, j) = m1.getelem(i, j - getcols());
            }
        }
    }

    return Matrix(temp);
}

Matrix Matrix::extract(const int col, const bool start) const
{
    // Check if column is valid.
    if((col > getcols()) || (col < 1))
        throw "Invalid col for extraction";

    // Extract the start or end?
    if(start)
    {
        // If the start is extracted, extract elements simply
        // till the correct column, then return the matrix.
        Matrix temp(getrows(), col);

        for(int i = 1; i <= getrows(); i++)
        {
            for(int j = 1; j <= col; j++)
            {
                temp.elem(i, j) = getelem(i, j);
            }
        }

        return temp;
    }
    else
    {
        // Else, extract from the end of the matrix.
        Matrix temp(getrows(), getcols() - col + 1);

        for(int i = 1; i <= getrows(); i++)
        {
            for(int j = 1; j <= (getcols() - col + 1); j++)
            {
                temp.elem(i, j) = getelem(i, col + j - 1);
            }
        }

        return Matrix(temp);
    }
}

Matrix Matrix::extractCol(const int col) const
{
	if((col > getcols()) || (col < 1))
		throw "Col out of range.";

	Matrix temp(getrows(), 1);
	for(int i = 1; i <= getrows(); i++)
	{
		temp.elem(i, 1) = getelem(i, col);
	}

	return Matrix(temp);
}

Matrix Matrix::basis() const
{
	Matrix rref = rowreduce();
	int nonzerorows = 0;
    bool nonzerorow = true;
    Matrix* pbasis;
	for(int i = 1; i <= getrows() ; i++)
	{
        nonzerorow = false;
        int foundcol = 0;
        for(int j = 1; j <= getcols() && !nonzerorow; j++)
        {
            nonzerorow = (rref.getelem(i, j) != 0.0) || nonzerorow;
            if(nonzerorow)
                foundcol = j;
        }
        
        if(nonzerorow)
        {
            nonzerorows++;
            if(nonzerorows == 1)
            {
                pbasis = new Matrix(extractCol(i));
            }
            else if(nonzerorows != 0)
            {
                *pbasis = (*pbasis).augment(extractCol(foundcol));
            }

        }
	}

    if(nonzerorows == 0)
        throw "Basis is an empty set.";

    return Matrix(*pbasis);
}

int Matrix::rank() const
{
    Matrix rref = rowreduce();
	int nonzerorows = 0;
    bool nonzerorow = true;
	for(int i = 1; i <= getrows() ; i++)
	{
        nonzerorow = false;
        for(int j = 1; j <= getcols() && !nonzerorow; j++)
        {
            nonzerorow = (rref.getelem(i, j) != 0.0) || nonzerorow;
        }
        
        if(nonzerorow)
            nonzerorows++;
	}

    return nonzerorows;
}

Matrix Matrix::transpose() const
{
    Matrix temp(getcols(), getrows());

    for(int i = 1; i <= temp.getrows(); i++)
    {
        for(int j = 1; j <= temp.getcols(); j++)
        {
            temp.elem(i, j) = getelem(j, i);
        }
    }

    return Matrix(temp);
}

Matrix Matrix::conjtranspose() const
{
    Matrix temp(getcols(), getrows());

    for(int i = 1; i <= temp.getrows(); i++)
    {
        for(int j = 1; j <= temp.getcols(); j++)
        {
            temp.elem(i, j) = conj(getelem(j, i));
        }
    }

    return Matrix(temp);
}

void Matrix::input(const char name[])
{
	cout << "\nEnter values for matrix " << name << ":\n\n";

    for(int i = 1; i <= getrows(); i++)
    {
        for(int j = 1; j <= getcols(); j++)
        {
            
            cout << "Enter value of " << name << "("
                 << setw(5) << i << ", " << setw(5) << j
                 << "): ";
            
            cin >> elem(i, j);
        }

        cout << endl;
    }
}

void Matrix::inputCol(const char name[])
{
    cout << "\nEnter values for matrix " << name << ":\n\n";

    for(int i = 1; i <= getcols(); i++)
    {
        for(int j = 1; j <= getrows(); j++)
        {
            cout << "Enter value of " << name << "("
                 << setw(5) << j << ", " << setw(5) << i
                 << "): ";
            
            cin >> elem(j, i);
        }

        cout << endl;
    }
}

void Matrix::output(const char name[]) const
{
    cout << endl << name << " =\n\n";

    for(int i = 1; i <= getrows(); i++)
    {
        cout << '[';

        for(int j = 1; j <= getcols(); j++)
        {
            if(getelem(i, j).imag() == 0.0)
                cout << setw(14) << getelem(i, j).real();
            else
                cout << setw(14) << getelem(i, j);

            if(j != getcols())
            {
                cout << ' ';
            }
        }

        cout << "]\n";
    }
}
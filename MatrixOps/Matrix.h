// Matrix.h
// Basic definition file of the Matrix class.

#ifndef MATRIX_H
#define MATRIX_H
#include <complex>

using namespace std;

class Matrix
{
private:
    const int rows, cols;
    complex<double>** mat;
public:
    Matrix(const int nrows, const int ncols);
    Matrix(const Matrix& m1);
    Matrix();
    inline int getrows() const;
    inline int getcols() const;
    inline complex<double>& elem(const int row, const int col);
    inline complex<double> getelem(const int row, const int col) const;
    void rowreplace(const int row1, const int row2);
    void rowdiv(const int row, const complex<double> c);
    void rowmuladd(const int row1, const int row2, const complex<double> c);
    Matrix& operator =(const Matrix& m1);
    Matrix& operator +=(const Matrix& m1);
    Matrix& operator -=(const Matrix& m1);
    Matrix& operator *=(const complex<double> c);
    Matrix operator +(const Matrix& m1) const;
    Matrix operator -(const Matrix& m1) const;
    Matrix operator *(const Matrix& m1) const;
    Matrix operator *(const complex<double> c) const;
    bool operator ==(const Matrix& m1) const;
    bool operator !=(const Matrix& m1) const;
    Matrix rowreduce() const;
    Matrix augment(const Matrix& m1) const;
    Matrix extract(const int col, const bool start) const;
    Matrix extractCol(const int col) const;
    Matrix basis() const;
    int rank() const;
    Matrix transpose() const;
    Matrix conjtranspose() const;
    void input(const char name[]);
    void inputCol(const char name[]);
    void output(const char name[]) const;
    ~Matrix();
};

#endif

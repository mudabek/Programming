#include "matrix.h"
#include "math.h"
#include <vector>
#include <iostream>



namespace task
{

task::Matrix::Matrix()
{
    rows = 1;
    cols = 1;
    mat[rows * cols] = {1.0};
}

task::Matrix::~Matrix()
{
    delete[] mat;
    mat = NULL;
}


task::Matrix::Matrix(size_t rows, size_t cols)
{
    this->rows = rows;
    this->cols = cols;
    if (rows == cols)
        mat[rows * cols] = {1};
    else
    {
        mat[rows * cols] = {0};
        for (int r = 0; r < rows; ++ r)
        {
            for (int c = 0; c < cols; ++ c)
            {
                if (r == c)
                    mat[(rows - 1) * r + c] = 1;
            }
        }
    }
}


task::Matrix::Matrix(const task::Matrix& copy)
{
    mat = copy.mat;
    rows = copy.rows;
    cols = copy.cols;
}



task::Matrix &task::Matrix::operator=(const task::Matrix& a)
{
    delete[] mat;

    mat = a.mat;
    rows = a.rows;
    cols = a.cols;

    return *this;
}


double& task::Matrix::get(size_t row, size_t col)
{
    return mat[(rows - 1) * (row - 1) + (col - 1)];
}


const double& task::Matrix::get(size_t row, size_t col) const
{
    return mat[(rows - 1) * (row - 1) + (col - 1)];
}


void task::Matrix::set(size_t row, size_t col, const double& value)
{
    mat[(rows - 1) * (row - 1) + (col - 1)] = value;
}


void task::Matrix::resize(size_t new_rows, size_t new_cols)
{
    Matrix new_mat = Matrix(new_rows, new_cols);

    for (int r = 0; r < new_rows; ++ r)
    {
        for (int c = 0; c < new_cols; ++ c)
        {
            if (r <= rows & c <= cols)
                new_mat.set(r, c, this->get(r, c));
            else
                new_mat.set(r, c, 0.0);
        }
    }

    *this = new_mat;
}


double* task::Matrix::operator[](size_t row)
{
    double* pRow = mat + row * cols;
    return pRow;
}

const double* task::Matrix::operator[](size_t row) const
{
    const double* pRow = mat + row * cols;
    return pRow;
}


task::Matrix task::Matrix::operator+(const task::Matrix& a) const
{
    if (a.rows != rows | a.cols != cols)
        throw OutOfBoundsException();

    Matrix newMat = Matrix(rows, cols);
    double val;

    for (int r = 0; r < rows; ++ r)
    {
        for (int c = 0; c < cols; ++ c)
        {
            val = this->get(r, c) + a.get(r, c);
            newMat.set(r, c, val);
        }
    }

    return newMat;
}


task::Matrix &task::Matrix::operator+=(const task::Matrix&a)
{
    return *this = *this + a;
}

task::Matrix task::Matrix::operator-(const task::Matrix& a) const
{
    if (a.rows != rows | a.cols != cols)
        throw OutOfBoundsException();

    Matrix newMat = Matrix(rows, cols);
    double val;

    for (int r = 0; r < rows; ++ r)
    {
        for (int c = 0; c < cols; ++ c)
        {
            val = this->get(r, c) - a.get(r, c);
            newMat.set(r, c, val);
        }
    }

    return newMat;
}


task::Matrix& task::Matrix::operator-=(const task::Matrix&a)
{
    return *this = *this - a;
}



task::Matrix task::Matrix::operator*(const task::Matrix& a) const
{
    if (cols != a.rows)
        throw SizeMismatchException();

    Matrix newMat = Matrix(rows, cols);
    double val;

    for (int r = 0; r < rows; ++ r)
    {
        for (int c = 0; c < a.cols; ++ c)
        {
            for (int k = 0; k < a.rows; ++ k)
            {
                val += this->get(r, k) - a.get(k, c);
            }
            newMat.set(r, c, val);
        }
    }

    return newMat;
}


task::Matrix &task::Matrix::operator*=(const task::Matrix&a)
{
    return *this = *this * a;
}



task::Matrix task::Matrix::operator*(const double& a) const
{
    Matrix newMat = Matrix(rows, cols);
    double val;

    for (int r = 0; r < rows; ++ r)
    {
        for (int c = 0; c < cols; ++ c)
        {
            val = this->get(r,c) * a;
            newMat.set(r, c, val);
        }
    }

    return newMat;
}


task::Matrix &task::Matrix::operator*=(const double& number)
{
    return *this = *this * number;
}


task::Matrix task::Matrix::operator-() const
{
    Matrix newMat = *this * -1.0;
    return newMat;
}


task::Matrix task::Matrix::operator+() const
{
    return *this;
}

double Matrix::Det()
{
    if (rows != cols)
    {
        throw(DIMERR());
    }

    double cofactor;
    int    col(0);
    bool   done(false);
    int    maxZeroRow(0);
    double minor(0.0);
    int    prevZeroCnt(0);
    double result(0.0);
    int    row(0);
    double sign(0.0);
    int    zeroCnt(0);

    //
    // Handle trivial cases.
    //
    if (rows == 1)
    {
        result = *pData;
        done = true;
    }

    if (!done)
    {
        if (rows == 2)
        {
            result = (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
            done = true;
        }
    }

    if (!done)
    {
        //
        // Find the row with the most zero elements.
        //
        for (row = 0; row < rows; ++row)
        {
            zeroCnt = 0.0;
            for (col = 0; col < cols; ++col)
            {
                if (WithinTolerance((*this)[row][col],  0.0))
                {
                    ++zeroCnt;
                }
            }
            if (zeroCnt == cols)
            {
                result = 0.0;
                done = true;
                break;  // exit loop for (row = 0; row < rows; ++row)
            }
            else if (zeroCnt > prevZeroCnt)
            {
                maxZeroRow = row;
                prevZeroCnt = zeroCnt;
            }
        }

        row = maxZeroRow;

    } // end if (!done)

    //
    // Sum the products of the selected row elements and their cofactors.
    //
    if (!done)
    {
        for (col = 0; col < cols; ++col)
        {
            if (!WithinTolerance(pData[row*cols+col], 0.0))
            {
                //
                // Odd powers of -1 are negative 1, even powers are positive 1.
                //
                sign = (row + col) % 2 == 0 ? 1.0 : -1.0;

                minor = Minor(row, col);

                cofactor = sign * pData[row*cols+col] * minor;

                result += cofactor;
            }
        }
    }  // end if (!done)

    return result;
}

void task::Matrix::transpose()
{
    task::Matrix transp = task::Matrix(cols, rows);

    for (int r = 0; r < rows; ++ r)
    {
        for (int c = 0; c < cols; ++ c)
        {
            transp.set(c, r, this->get(r, c));
        }
    }

    *this = transp;
}


task::Matrix task::Matrix::transposed() const
{
    task::Matrix transp = task::Matrix(cols, rows);

    for (int r = 0; r < rows; ++ r)
    {
        for (int c = 0; c < cols; ++ c)
        {
            transp.set(c, r, this->get(r, c));
        }
    }

    return transp;
}


double task::Matrix::trace() const
{
    if (rows != cols)
        throw SizeMismatchException();

    double trac = 0;

    for (int r = 0; r < rows; ++ r)
    {
        trac += this->get(r, r);
    }

    return trac;
}


std::vector<double> task::Matrix::getRow(size_t row)
{
    std::vector<double> rower;

    for (int c = 0; c < cols; ++ c)
        rower.push_back(this->get(row, c));

    return rower;
}

std::vector<double> task::Matrix::getColumn(size_t column)
{
    std::vector<double> columner;

    for (int r = 0; r < rows; ++ r)
        columner.push_back(this->get(r, column));

    return columner;
}


bool task::Matrix::operator==(const task::Matrix& a) const
{
    if (cols != a.cols | rows != a.rows)
        return false;

    for (int r = 0; r < rows; ++ r)
    {
        for (int c = 0; c < cols; ++ c)
        {
            if (this->get(r, c) != a.get(r, c))
                return false;
        }
    }
    return true;
}


bool task::Matrix::operator!=(const task::Matrix& a) const
{
    return !(*this == a);
}





std::ostream& operator<<(std::ostream& output, const task::Matrix& matrix)
{
    for (int r = 0; r < matrix.rows; ++ r)
    {
        for (int c = 0; c < matrix.cols; ++ c)
        {
            output << matrix.get(r, c) << " ";
        }
    }

    output << std::endl;

    return output;
}


std::istream& operator>>(std::istream& input, task::Matrix& matrix)
{
    double temp;
    int rw, cln;

    input >> rw >> cln;

    for (int r = 0; r < rw; ++ r)
    {
        for (int c = 0; c < cln; ++ c)
        {
            input >> temp;
            matrix.set(r, c, temp);
        }
    }
}


task::Matrix operator*(const double& a, const task::Matrix& b)
{
    task::Matrix newMat = task::Matrix(b.rows, b.cols);

    for (int r = 0; r < b.rows; ++ r)
    {
        for (int c = 0; c < b.cols; ++ c)
        {
            newMat.set(r, c, a * b.get(r, c));
        }
    }
    return newMat;
}
}



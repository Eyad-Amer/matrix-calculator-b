/**
 * Implementation of the functions
 *
 * Author: Eyad Amer
 * Since : 2022-04
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace std;

#include "Matrix.hpp"
using namespace zich;

namespace zich
{
    // constructor
    Matrix::Matrix(vector<double> mat, int row, int col)
    {
        // the row and the column must be a positive number
        if (row <= 0 || col <= 0)
        {
            throw invalid_argument("illegal inputs - the number of the row or columns are Negetave number!");
        }

        // check if the size of the vector are the same of the matrix size
        if (mat.size() != (row * col))
        {
            throw invalid_argument("illegal inputs - the size of the vector are the same of the matrix size!");
        }

        vector<double> v;
        this->rows = row;
        this->cols = col;

        for (unsigned int i = 0; i < row * col; i++)
        {
            v.push_back(mat[i]);
            if (col == v.size())
            {
                this->matrix.push_back(v);
                v.resize(0);
            }
        }
    }

    // copy constructor
    Matrix::Matrix(const Matrix &other)
    {
        // the row and the column must be a positive number
        if (other.rows <= 0 || other.cols <= 0)
        {
            throw invalid_argument("illegal inputs - the number of the row or columns are Negetave number!");
        }

        this->rows = other.rows;
        this->cols = other.cols;
        this->matrix = other.matrix;
    }

    // get the rows
    int Matrix::getMatrixRows() const
    {
        return this->rows;
    }

    // get the columns
    int Matrix::getMatrixcols() const
    {
        return this->cols;
    }

    // check if the Matrices are the same size
    void checkSize(const Matrix &matrix1, const Matrix &matrix2)
    {
        if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols)
        {
            throw invalid_argument("illegal");
        }
    }

    // get the sum of the matrix members
    double SumOfMatrix(const Matrix &matrix1)
    {
        double sum = 0;
        Matrix matrix = matrix1;
        int row = matrix.getMatrixRows();
        int col = matrix.getMatrixcols();
        for (unsigned int i = 0; i < row; i++)
        {
            for (unsigned int j = 0; j < col; j++)
            {
                sum += matrix.matrix[i][j];
            }
        }
        return sum;
    }

    // Accounting operators: +, +=, +(onry), -, -=, -(onry)

    // plus
    Matrix Matrix::operator+(const Matrix &other)
    {
        checkSize(*this, other);

        Matrix mat = other;
        int row = mat.getMatrixRows();
        int col = mat.getMatrixcols();
        vector<double> vec;
        for (unsigned int i = 0; i < row; i++)
        {
            for (unsigned int j = 0; j < col; j++)
            {
                vec.push_back(this->matrix[i][j] + other.matrix[i][j]);
            }
        }
        Matrix plusMat{vec, row, col};

        return plusMat;
    }

    // add
    Matrix &Matrix::operator+=(const Matrix &other)
    {
        Matrix mat = *this;
        checkSize(*this, other);

        mat = mat + other;
        this->matrix = mat.matrix;

        return *this;
    }

    // plus onry
    Matrix Matrix::operator+()
    {
        Matrix mat = *this;
        int row = mat.getMatrixRows();
        int col = mat.getMatrixcols();
        vector<double> vec;

        for (unsigned int i = 0; i < row; i++)
        {
            for (unsigned int j = 0; j < col; j++)
            {
                vec.push_back(this->matrix[i][j]);
            }
        }
        Matrix onry{vec, row, col};

        return onry;
    }

    // minus
    Matrix Matrix::operator-(const Matrix &other)
    {
        checkSize(*this, other);

        Matrix mat = other;
        int row = mat.getMatrixRows();
        int col = mat.getMatrixcols();
        vector<double> vec;
        for (unsigned int i = 0; i < row; i++)
        {
            for (unsigned int j = 0; j < col; j++)
            {
                vec.push_back(this->matrix[i][j] - other.matrix[i][j]);
            }
        }
        Matrix minusMat{vec, row, col};

        return minusMat;
    }

    // reduction
    Matrix &Matrix::operator-=(const Matrix &other)
    {
        Matrix mat = *this;
        checkSize(*this, other);

        mat = mat - other;
        this->matrix = mat.matrix;

        return *this;
    }

    // minus onry
    Matrix Matrix::operator-()
    {
        Matrix mat = *this;
        int row = mat.getMatrixRows();
        int col = mat.getMatrixcols();
        vector<double> vec;

        for (unsigned int i = 0; i < row; i++)
        {
            for (unsigned int j = 0; j < col; j++)
            {
                vec.push_back(-this->matrix[i][j]);
            }
        }
        Matrix onry{vec, row, col};

        return onry;
    }

    // help function
    bool comp(const Matrix &a, const Matrix &b, const string &s)
    {
        checkSize(a, b);
        double mat1 = SumOfMatrix(a);
        double mat2 = SumOfMatrix(b);

        if (s == "<")
        {
            return (mat1 < mat2);
        }

        if (s == "<=")
        {
            return (mat1 <= mat2);
        }

        if (s == ">")
        {
            return (mat1 > mat2);
        }

        if (s == ">=")
        {
            return (mat1 >= mat2);
        }

        if (s == "!=")
        {
            return (mat1 != mat2);
        }
        return false;
    }

    // Comparison operators: <, <=, >, >=, =, !=
    bool operator<(const Matrix &matrix1, const Matrix &matrix2)
    {
        string s = "<";
        return (comp(matrix1, matrix2, s));
    }

    bool operator<=(const Matrix &matrix1, const Matrix &matrix2)
    {
        string s = "<=";
        return (comp(matrix1, matrix2, s));
    }

    bool operator>(const Matrix &matrix1, const Matrix &matrix2)
    {
        string s = ">";
        return (comp(matrix1, matrix2, s));
    }

    bool operator>=(const Matrix &matrix1, const Matrix &matrix2)
    {
        string s = ">=";
        return (comp(matrix1, matrix2, s));
    }

    bool operator==(const Matrix &matrix1, const Matrix &matrix2)
    {
        checkSize(matrix1, matrix2);
        Matrix mat = matrix1;
        int row = mat.getMatrixRows();
        int col = mat.getMatrixcols();
        bool flag = true;

        for (unsigned int i = 0; i < row; i++)
        {
            for (unsigned int j = 0; j < col; j++)
            {
                if (matrix1.matrix[i][j] != matrix2.matrix[i][j])
                {
                    flag = false;
                }
            }
        }
        return flag;
    }

    bool operator!=(const Matrix &matrix1, const Matrix &matrix2)
    {
        string s = "!=";
        return (comp(matrix1, matrix2, s));
    }

    // Increase or decrease by 1 all the members of the matrix befor the number
    Matrix &Matrix::operator++()
    {
        for (unsigned int i = 0; i < rows; i++)
        {
            for (unsigned int j = 0; j < cols; j++)
            {
                this->matrix[i][j] += 1;
            }
        }
        return (*this);
    }

    Matrix &Matrix::operator--()
    {
        for (unsigned int i = 0; i < rows; i++)
        {
            for (unsigned int j = 0; j < cols; j++)
            {
                this->matrix[i][j] -= 1;
            }
        }
        return (*this);
    }

    // Increase or decrease by 1 all the members of the matrix after the number
    Matrix Matrix::operator++(int num)
    {
        Matrix mat = *this;
        int row = mat.getMatrixRows();
        int col = mat.getMatrixcols();

        for (unsigned int i = 0; i < row; i++)
        {
            for (unsigned int j = 0; j < col; j++)
            {
                this->matrix[i][j] += 1;
            }
        }
        return mat;
    }

    Matrix Matrix::operator--(int num)
    {
        Matrix mat = *this;
        int row = mat.getMatrixRows();
        int col = mat.getMatrixcols();

        for (unsigned int i = 0; i < row; i++)
        {
            for (unsigned int j = 0; j < col; j++)
            {
                this->matrix[i][j] -= 1;
            }
        }
        return mat;
    }

    // Matrix doubling in scalar
    Matrix Matrix::operator*(double num)
    {
        Matrix mat = *this;
        int row = mat.getMatrixRows();
        int col = mat.getMatrixcols();

        for (unsigned int i = 0; i < row; i++)
        {
            for (unsigned int j = 0; j < col; j++)
            {
                mat.matrix[i][j] *= num;
            }
        }
        return mat;
    }

    Matrix &Matrix::operator*=(double num)
    {
        Matrix mat = *this;
        int row = mat.getMatrixRows();
        int col = mat.getMatrixcols();

        for (unsigned int i = 0; i < row; i++)
        {
            for (unsigned int j = 0; j < col; j++)
            {
                this->matrix[i][j] *= num;
            }
        }
        return (*this);
    }

    // Matrix multiplication in the matrix
    Matrix operator*(double num, const Matrix &other)
    {
        Matrix mat = other;
        int row = mat.getMatrixRows();
        int col = mat.getMatrixcols();

        for (unsigned int i = 0; i < row; i++)
        {
            for (unsigned int j = 0; j < col; j++)
            {
                mat.matrix[i][j] *= num;
            }
        }
        return mat;
    }

    Matrix Matrix::operator*(const Matrix &other)
    {
        checkSize(*this, other);
        Matrix mat = other;
        int row1 = mat.getMatrixRows();
        int col1 = mat.getMatrixcols();

        int row2 = this->rows;
        int col2 = this->cols;

        vector<double> vec;

        if (col2 != row1)
        {
            throw invalid_argument("error!");
        }

        for (unsigned int i = 0; i < row2; i++)
        {
            for (unsigned int j = 0; j < col1; j++)
            {
                vec.push_back(0);
            }
        }
        unsigned int k = 0;
        for (unsigned int i = 0; i < row2; i++)
        {
            for (unsigned int j = 0; j < col1; j++, k++)
            {
                for (unsigned int t = 0; t < col2; t++)
                {
                    vec[k] += this->matrix[i][t] * other.matrix[t][j];
                }
            }
        }
        Matrix multMat{vec, row2, col1};

        return multMat;
    }

    Matrix &Matrix::operator*=(const Matrix &other)
    {
        checkSize(*this, other);

        *this = ((*this) * other);
        return (*this);
    }

    // input and output operator
    std::istream &operator>>(std::istream &input, Matrix &other)
    {
        {
            return input;
        }
    }

    std::ostream &operator<<(std::ostream &output, const Matrix &other)
    {
        {
            for (unsigned int i = 0; i < other.rows; i++)
            {
                output << "[";
                for (unsigned int j = 0; j < other.cols; j++)
                {
                    if (j < other.cols - 1)
                    {
                        output << other.matrix[i][j] << " ";
                    }
                    else
                    {
                        output << other.matrix[i][j];
                    }
                }
                output << "]";
                if (i < other.rows - 1)
                {
                    output << "\n";
                }
            }
            return output;
        }
    }
}
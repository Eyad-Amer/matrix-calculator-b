/**
 * Heading for the function
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

namespace zich{
    class Matrix{
        private:
            int rows; // the rows of the matrix
            int cols; // the columns of the matrix
            vector <vector <double>> matrix; // vector of vectors to create matrix

        public:

            // constructor
            Matrix(vector<double> mat, int row, int col);
            Matrix(const Matrix &other);

            // get the rows
            int getMatrixRows() const;

            // get the columns
            int getMatrixcols() const;

            // get the matrix
            //vector <vector <double>> getMatrix();

            // check if the Matrices are the same size
            friend void checkSize(const Matrix &matrix1, const Matrix &matrix2);

            // get the sum of the matrix members
            friend double SumOfMatrix(const Matrix &matrix1);

            // help function
            friend bool comp(const Matrix &a, const Matrix &b, const string &s);

            // Accounting operators: +, +=, +(onry), -, -=, -(onry)
            Matrix operator+(const Matrix &other); // plus
            Matrix &operator+=(const Matrix &other); // add
            Matrix operator+(); // plus onry
            Matrix operator-(const Matrix &other); // minus
            Matrix &operator-=(const Matrix &other); // reduction
            Matrix operator-(); // minus onry

            // Comparison operators: <, <=, >, >=, =, !=
            friend bool operator<(const Matrix &matrix1, const Matrix &matrix2);
            friend bool operator<=(const Matrix &matrix1, const Matrix &matrix2);

            friend bool operator>(const Matrix &matrix1, const Matrix &matrix2);
            friend bool operator>=(const Matrix &matrix1, const Matrix &matrix2);

            friend bool operator==(const Matrix &matrix1, const Matrix &matrix2);
            friend bool operator!=(const Matrix &matrix1, const Matrix &matrix2);

            // Increase or decrease by 1 all the members of the matrix befor the number
            Matrix &operator++();
            Matrix &operator--();

            // Increase or decrease by 1 all the members of the matrix after the number
            Matrix operator++(int num);
            Matrix operator--(int num);

            // Matrix doubling in scalar
            Matrix operator*(double num);
            Matrix &operator*=(double num);

            // Matrix multiplication in the matrix
            friend Matrix operator*(double num, const Matrix &other);
            //friend Matrix operator*(const Matrix &other, double num);
            Matrix operator*(const Matrix &other);
            Matrix &operator*=(const Matrix &other);

            // input and output operator
            friend std::istream &operator>>(std::istream &input, Matrix &other);
            friend std::ostream &operator<<(std::ostream &output, const Matrix &other);   
    };
};
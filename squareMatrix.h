#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "Matrix.h"
#pragma once

class SquareMatrix: public Matrix{
public:
    SquareMatrix(){}
    // makes the mxm zero-matrix (default) or identity matrix.
    SquareMatrix(int m, bool Identity=false);

    SquareMatrix(std::initializer_list<std::initializer_list<double> > i);
    SquareMatrix(const Matrix &m);
private:
    // modifies *this. So always use the .det() method with no arguments. Anyways private.
    double det(int start_row, int start_col);
public:
    int order() const;

    double det() const;

    SquareMatrix inverse() const;
};

inline double det(const SquareMatrix &s){
    return s.det();
}

#endif
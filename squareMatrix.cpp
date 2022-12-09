#include "squareMatrix.h"

SquareMatrix::SquareMatrix(int m, bool Identity=false): Matrix{m,m}
{
    if (Identity)
        for (int i = 0; i < m; i++) 
            at(i, i) = 1;
}
SquareMatrix::SquareMatrix(std::initializer_list<std::initializer_list<double> > i): Matrix{i}
{
    if(Matrix::order().first != Matrix::order().second)
    {
        std::cerr<<"invalid initializer_list for square matrix"<<std::endl;
        throw 1;
    }
}
SquareMatrix::SquareMatrix(const Matrix &m): Matrix{m}
{
    if(Matrix::order().first != Matrix::order().second)
    {
        std::cerr<<"Matrix is not square, cannot convert to SquareMatrix"<<std::endl;
        throw 1;
    }
}

// modifies *this. So always use the .det() method with no arguments. Anyways private.
double SquareMatrix::det(int start_row, int start_col){
    if (start_row == at(0).size() || start_col == size())
    {
        double x{1};
        for(int i{0};i< Matrix::order().first;i++)
        {
            x*=at(i,i);
        }
        return x;
    }
    bool allzero = true;
    for (int column = start_col; column < size(); column++)
        if (std::abs(at(start_row, column)) > EPSILON){
            allzero = false;
            std::swap(at(start_col), at(column));
            break;
        }
    if (allzero) return 0;
    double x = at(start_row, start_col);
    for (int column = start_col + 1; column < size(); column++)
        at(column) -= (at(start_row, column) * at(start_col))/x;
    return det(start_col + 1, start_row + 1);
}

int SquareMatrix::order() const{
    // return Matrix::order().first;
    return mat.size();
}
double SquareMatrix::det() const{
    SquareMatrix scpy{*this};
    return scpy.det(0, 0);
}

SquareMatrix SquareMatrix::inverse() const{
    Matrix scpy{*this};
    scpy.augment_modify(SquareMatrix(order(), true)); // augment identity to M.
    scpy.rref(true);

    for (int i = 0; i < order(); i++)
        if (scpy.at(i).isZero()) throw "non-invertible matrix";
    
    // else rref is I and hence the right side of scpy is M^{-1}.
    SquareMatrix ans(order());
    for (int i = 0; i < order(); i++)
        ans.at(i) = scpy.at(order() + i);
    return ans;
}
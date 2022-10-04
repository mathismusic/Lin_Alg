#include "Matrix.h"

class SquareMatrix: public Matrix{
public:
    SquareMatrix(){}
    SquareMatrix(int m): Matrix{m,m}
    {}
    SquareMatrix(std::initializer_list<std::initializer_list<double> > i): Matrix{i}
    {
        if(order().first!=order().second)
        {
            std::cerr<<"invalid initializer_list for square matrix"<<std::endl;
            throw 1;
        }
    }
private:
    double det(int start_row = 0, int start_col = 0){
        if (start_row == at(0).size() || start_col == size())
        {
            double x{1};
            for(int i{0};i<order().first;i++)
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
public:
    friend inline double det(const SquareMatrix &s);
};

inline double det(const SquareMatrix &s){
    SquareMatrix scpy{s};
    return scpy.det();
}

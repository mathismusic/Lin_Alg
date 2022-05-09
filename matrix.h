#include <iostream>
#include <vector>
#include "Vector.h"


class Matrix : public std::vector<Vector>{
public:
    Matrix(){}
    Matrix(int m, int n): vector<Vector>(n,Vector(m))
    {}
    Matrix(std::initializer_list<std::initializer_list<double> > init, bool byColumns=true){
        if (init.size() == 0) 
            return;

        for (auto &column: init)
            if (column.size() != init.begin()->size()){
                std::cerr << "Invalid matrix - All sublists must have same size\n";
                throw 0;
            }

        if (byColumns)
            for (auto &column: init){
                push_back(Vector(column));
            }
        else
            for (int column_no = 0; column_no < init.begin()->size(); column_no++){
                Vector current_column;
                for (auto &row: init)
                    current_column.push_back(*(row.begin() + column_no));
                push_back(current_column);
            }          
    }

    std::pair<int,int> order() const
    {
        if(size()==0)
            return std::pair<int,int> (0,0);
        return std::pair<int,int> (at(0).size(), size());
    }
    double& at(int i, int j)
    {
        if(i<0||i>=at(0).size()||j<0||j>=size())
        {
            std::cerr<<"index out of bounds"<<std::endl;
            throw 0;
        }
        return at(j).at(i);
    }
    using std::vector<Vector>::at;
    Matrix operator *(Matrix m)
    {
        if(order().second!=m.order().first)
        {
            std::cerr<<"Matrices incompatible for multiplication"<<std::endl;
            throw 0;
        }
        Matrix product(order().first,m.order().second);
        for(int i{0};i<order().first;i++)
        {
            for(int j{0};j<m.order().second;j++)
            {
                for(int k{0};k<order().second;k++)
                {
                    product.at(i,j)+=at(i,k)*m.at(k,j);
                }
            }
        }
        return move(product);
    }
    Matrix transpose(bool modify = false)
    {
        Matrix m(order().second, order().first);
        for(int i{0};i<order().first;i++)
            for(int j{0};j<order().second;j++)
                m.at(j,i) = at(i,j);
        if(modify)
            *this = m;
        return move(m);
    }
};

inline void print(const Matrix &m){
    if (m.size() == 0) return;
    for (int i = 0; i < m.at(0).size(); i++){
        std::cout << '[';
        for(int j = 0; j < m.size(); j++){
            std::cout << m.at(j).at(i);
            if (j != m.size() - 1) 
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
}
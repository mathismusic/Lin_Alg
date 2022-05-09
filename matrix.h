#include <iostream>
#include <vector>
#include "Vector.h"


class Matrix : public std::vector<Vector>{
public:
    Matrix(){}
    Matrix(int m, int n): vector<Vector>(n,Vector(m))
    {}
    Matrix(std::initializer_list<std::initializer_list<double> > init){
        for (int i = 0; i < init.size(); i++)
            push_back(Vector(*(init.begin() + i)));
    }
    std::pair<int,int> order()
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
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
            at(i) = Vector(*(init.begin() + i));
    }
    std::pair<int,int> order()
    {
        if(size()==0)
            return std::pair<int,int> (0,0);
        return std::pair<int,int> (at(0).size(), size());
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
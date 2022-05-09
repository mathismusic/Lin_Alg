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
};
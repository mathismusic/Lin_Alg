#include <iostream>
#include <vector>
#include "Vector.h"


class Matrix : public std::vector<Vector>{
public:
    Matrix(){}
    Matrix(int m, int n): vector<Vector>(n,Vector(m))
    {}
};
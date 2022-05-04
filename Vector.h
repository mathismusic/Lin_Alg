#include <iostream>
#include <vector>
#include <cmath>

#define EPSILON = pow(10,-10)

//template <class T>
class Vector : public std::vector<double>{
public:
    Vector(){}
    Vector(std::initializer_list<double> init): std::vector<double>{init}
    {}
    Vector(int n): std::vector<double>(n){}
    
    double dot(const Vector &v)
    {
        if (this->size()!=v.size())
        {
            std::cerr<<"Invalid dot product"<<std::endl;
            throw 0;
        }
        double pdt{0};
        for(int i{0};i<v.size();i++)
            pdt+=(this->at(i))*(v.at(i));
        return pdt;
    }

    inline double norm(int k=2){
        double res = 0;
        for (int i = 0; i < size(); i++)
            res += std::pow(at(i), k);
        return pow(res, 1.0/k);
    }
};

inline void print(const Vector &v){
    std::cout<<'[';
    for(auto it = v.begin(); it != v.end(); it++)
    {
        std::cout << *it;
        if(it + 1 != v.end())
            std::cout << ", ";
    }
    std::cout<<']'<< std::endl;
}

inline int len(const Vector &v){ return v.size(); }
inline int dim(const Vector &v){ return v.size(); }
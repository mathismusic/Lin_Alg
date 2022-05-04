#include <iostream>
#include <vector>
#include <cmath>

#define EPSILON 1e-10

//template <class T>
class Vector : public std::vector<double>{
public:
    Vector(){}
    Vector(std::initializer_list<double> init): std::vector<double>{init}
    {}
    Vector(int n): std::vector<double>(n){}
    
    double dot(const Vector &v) const
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

    inline double norm(int k=2) const{
        double res = 0;
        for (int i = 0; i < size(); i++)
            res += std::pow(at(i), k);
        return pow(res, 1.0/k);
    }
    inline bool isZero() const{ return (std::abs(norm()) < EPSILON); }

    Vector normalize(int k=2) const{
        Vector res(size());
        double norm_ = norm(k);
        for (int i = 0; i < size(); i++)
            res[i] = at(i)/norm_;
        return res;
    }

    Vector operator + (const Vector &v)
    {
        if (size()!=v.size())
        {
            std::cerr<<"Invalid addition"<<std::endl;
            throw 0;
        }
        Vector sum(size());
        for(int i{0};i<size();i++)
        {
            sum.at(i) = at(i)+v.at(i);
        }
        return sum;
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
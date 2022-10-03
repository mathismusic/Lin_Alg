#include "Vector.h"

#define EPSILON 1e-10

// check the move constructors. Whether or not to add move

// Arithmetic operations
Vector Vector::operator + (const Vector &v) const
{
    if (size()!=v.size())
    {
        std::cerr<<"Invalid addition"<<std::endl;
        throw std::invalid_argument("Vectors incompatible for addition.");
    }

    Vector sum(size());
    for(int i{0};i<size();i++)
    {
        sum.at(i) = at(i)+v.at(i);
    }
    return sum;
}

Vector Vector::operator - (const Vector &v) const
{
    if (size()!=v.size())
    {
        std::cerr<<"Invalid subtraction"<<std::endl;
        throw std::invalid_argument("Vectors incompatible for subtraction.");
    }
    Vector diff(size());
    for(int i{0};i<size();i++)
    {
        diff.at(i) = at(i)-v.at(i);
    }
    return diff;
}

Vector Vector::operator * (const double &d) const
{
    Vector v(size());
    for (int i{0};i<size();i++)
        v.at(i) = d * at(i);
    return v;
}

Vector Vector::operator / (double d) const
{
    if (std::abs(d) < EPSILON)
    {
        std::cerr<<"Division by 0"<<std::endl;
        throw std::invalid_argument("Cannot divide by 0");
    }
    return (*this)*(1/d);
}

const Vector &Vector::operator+=(const Vector &v){
    if (size()!=v.size())
    {
        std::cerr<<"Invalid addition"<<std::endl;
        throw 0;
    }
    for (int i = 0; i < size(); i++)
        at(i) = at(i) + v.at(i);
    return *this;
}

const Vector &Vector::operator-=(const Vector &v){
    if (size()!=v.size())
    {
        std::cerr<<"Invalid subtraction"<<std::endl;
        throw 0;
    }
    for (int i = 0; i < size(); i++)
        at(i) = at(i) - v.at(i);
    return *this;
}

const Vector &Vector::operator*=(const double &factor){
    for (auto &elem: vec)
        elem = elem * factor;
    return *this;
}

const Vector &Vector::operator/=(double factor){
    if (std::abs(factor)<EPSILON)
    {
        std::cerr<<"Division by 0"<<std::endl;
        throw 0;
    }
    for (int i = 0; i < size(); i++)
        at(i) = at(i) / factor;
    return *this;
}

// inner products and norm
double Vector::dot(const Vector &v) const
{
    if (this->size()!=v.size())
    {
        std::cerr<<"Invalid dot product"<<std::endl;
        throw std::invalid_argument("Vectors do not have the same dimension. Cannot take dot product.");
    }
    double pdt{0};
    for(int i{0};i<v.size();i++)
        pdt += at(i) * v.at(i);
    return pdt;
}

double Vector::norm(int k) const{
    double res = 0;
    for (int i = 0; i < size(); i++)
        res += std::pow(at(i), k);
    return pow(res, 1.0/k);
}

Vector Vector::normalized(bool modify, int k){
    Vector res(size());
    double norm_ = norm(k);
    if (std::abs(norm_) < EPSILON)
        throw "Cannot normalize zero vector";
    for (int i = 0; i < size(); i++)
        res[i] = at(i)/norm_;
    if (modify)
        *this = res;
    return res;
}


// special function, required for reduced matrix forms
Vector Vector::set_component_to_1(int index, bool modify){
        if (std::abs(at(index)) < EPSILON){
            std::cerr << "Element is 0 - cannot scale to 1\n";
            throw std::invalid_argument("Element is 0 - cannot scale to 1\n");
        }

        Vector res(size());
        for (int i = 0; i < size(); i++)
            res[i] = at(i)/at(index);
        if (modify)
            *this = res;
        return std::move(res);
}

// ===================== Global functions ============================= //

inline std::ostream& operator<<(std::ostream &ost, const Vector &v){
    if (v.size() == 0){
        ost << "[]";
        return ost;
    }

    ost << '[';
    for(auto it = v.begin(); it != v.end(); it++)
    {
        ost << *it;
        if(it + 1 != v.end())
            ost << ", ";
    }
    std::cout<<"]";
    return ost;
}


#include <iostream>
#include <vector>
#include <cmath>

#define EPSILON 0.0000000000000000000000001

class Polynomial
{
    //Contains a polynomial in the form of a std::vector<double>, in the ascending order of powers of the variable
protected:
    std::vector<double> vec;
    char variable;
public:
    Polynomial(std::initializer_list<double> i, char x = 'x'): vec{i}, variable{x}
    {}
    Polynomial(char x = 'x'): variable{x}
    {}
    Polynomial(double d): variable{x}, vec{d}
    {}
    int degree () const
    {
        if(vec.size()==0)
        {
            std::cerr<<"undefined degree of zero polynomial"<<std::endl;
            throw 0;
        }
        return vec.size()-1;
    }
    Polynomial operator + (const Polynomial p) const 
    {
        Polynomial temp;
        if(degree()>=p.degree())
        {
            for (int i{0};i<=p.degree();i++)
            {
                temp.vec.push_back(vec.at(i)+p.vec.at(i));
            }
            for(int i{0};i<degree()-p.degree();i++)
            {
                temp.vec.push_back(vec.at(i+p.degree()+1));
            }
        }
        else
        {
            for (int i{0};i<=degree();i++)
            {
                temp.vec.push_back(vec.at(i)+p.vec.at(i));
            }
            for(int i{0};i<p.degree()-degree();i++)
            {
                temp.vec.push_back(p.vec.at(i+degree()+1));
            }
        }
        return std::move(temp);
    }

    Polynomial operator - (const Polynomial p) const 
    {
        Polynomial temp;
        if(degree()>=p.degree())
        {
            for (int i{0};i<=p.degree();i++)
            {
                temp.vec.push_back(vec.at(i)-p.vec.at(i));
            }
            for(int i{0};i<degree()-p.degree();i++)
            {
                temp.vec.push_back(vec.at(i+p.degree()+1));
            }
        }
        else
        {
            for (int i{0};i<=degree();i++)
            {
                temp.vec.push_back(vec.at(i)-p.vec.at(i));
            }
            for(int i{0};i<p.degree()-degree();i++)
            {
                temp.vec.push_back(-p.vec.at(i+degree()+1));
            }
        }
        return std::move(temp);
    }

    friend inline Polynomial operator -(const Polynomial p);
    friend inline void print(const Polynomial, int, bool);
};

inline Polynomial operator -(const Polynomial p)
{
    Polynomial temp;
    for(int i{0};i<p.degree()+1;i++)
    {
        temp.vec.push_back(-p.vec.at(i));
    }
    return std::move(temp);
}

void inline print (const Polynomial p, int prec = 2, bool fix = false)
{
    if(fix)
        std::cout<<std::fixed;
    std::cout.precision(prec);
    for(int i{p.degree()};i>0;i--)
    {
        if(p.vec.at(i)<0)
            std::cout<<'\b';
        std::cout<<p.vec.at(i)<<p.variable<<'^'<<i<<'+';
    }
    if(p.vec.at(0)<0)
        std::cout<<'\b';
    std::cout<<p.vec.at(0)<<std::endl;
}

int main()
{
    Polynomial p, q{1,2,3,4};
    Polynomial z=p+q;
    print(z);
    print(q-p);
    p=-p;
    print(p);
}

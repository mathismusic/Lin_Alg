#include <iostream>
#include <vector>


//template <class T>
class Vector : public std::vector<double>{
};

inline void print(const Vector &v){
    std::cout<<'[';
    for(auto i: v)
    {
        std::cout<<i;
        if(&i+1!=v.end())
            std::cout<<',';
    }
    std::cout<<']'<<endl;
}
#include <iostream>
#include <vector>


//template <class T>
class Vector : public std::vector<double>{
};

inline void print(Vector &v){
    std::cout<<'[';
    for(auto i: v)
    {
        std::cout<<i<<',';
    }
    std::cout<<']'<<endl;
}
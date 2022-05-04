#include <iostream>
#include <vector>


//template <class T>
class Vector : public std::vector<double>{




};

inline void print(const Vector &v){
    std::cout<<'[';
    for(auto it = v.begin(); it != v.end(); it++)
    {
        std::cout << *it;
        if(it + 1 != v.end())
            std::cout << ", ";
    }
    std::cout<<']'<<endl;
}

inline int len(const Vector &v){ return size(); }
inline int dimension(const Vector &v){ return size(); }
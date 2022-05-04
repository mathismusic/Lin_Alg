#include <iostream>
#include <vector>


//template <class T>
class Vector : public std::vector<double>{

};

inline void print(const Vector &v){
//    std::cout << std::fixed;
//    std::cout.precision(6);
    for (const double &component : v.vec){
        std::cout.width(12); // need to set after every << call else default(of 0)is taken
        std::cout << component;
    }
    std::cout << std::endl;
}
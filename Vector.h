#include <iostream>
#include <vector>


//template <class T>
class Vector : public std::vector<double>{

};

inline void print(const Vector &v){
    for (const double &component : v){
        std::cout.width(12); // need to set after every << call else default(of 0)is taken
        std::cout << component;
    }
    std::cout << std::endl;
}
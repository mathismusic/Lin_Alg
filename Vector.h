#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>
#include <cmath>
#include <exception>

#define EPSILON 1e-10

// check the move constructors. Whether or not to add

#define print(x) std::cout << (x);
#define println(x) std::cout << (x) << std::endl;

//template <class T>
class Vector{
    std::vector<double> vec;
public:
    // constructors

    /**
     * @brief Construct a new empty Vector object
     * 
     */
    Vector(){}

    /**
     * @brief Construct a new Vector object from an initializer list
     * 
     * @param init The initializer list from where to construct the vector
     */
    Vector(std::initializer_list<double> init): vec(init){}

    /**
     * @brief Construct a new Vector object and initialize it to the n-dimensional zero vector.
     * 
     * @param n the dimension of the vector
     */
    Vector(int n): vec(n){}
    
    /**
     * @brief Default destructor
     */
    ~Vector(){}


    // basic accessor and container operations

    /**
     * @brief Check if the vector is a zero vector
     * 
     * @return true if the vector is zero
     * @return false otherwise
     */
    inline bool isZero() const{ return (std::abs(norm()) < EPSILON); }
    
    /**
     * @brief returns the dimension/length/size of the vector.
     * @note see also len and dim.
     * @return int. The dimension of the vector
     */
    inline int size() const{ return vec.size(); }
    
    /**
     * @brief access the element at the index-th index of the vector. Throws out_of_range error if the index is invalid.
     * 
     * @param index index of the required value.
     * @return double&. the element at the required index.
     */
    inline double &operator[](int index){
        if (index < 0 || index >= size()){
            std::cerr << "Index out of range";
            throw std::out_of_range("Index out of range");
        }
        return vec[index];
    }

    /**
     * @brief access (read-only) the element at the index-th index of the vector. Throws out_of_range error if the index is invalid.
     * 
     * @param index index of the required value.
     * @return const double&. A non-modifiable reference to the element at the required index.
     */
    inline const double &operator[](int index) const{
        if (index < 0 || index >= size()){
            std::cerr << "Index out of range";
            throw std::out_of_range("Index out of range");
        }
        return vec[index];
    }

    /**
     * @brief access the element at the index-th index of the vector. Throws out_of_range error if the index is invalid.
     * 
     * @param index index of the required value.
     * @return double&. the element at the required index.
     */
    inline double &at(int index){
       return (*this)[index]; 
    }

    /**
     * @brief access (read-only) the element at the index-th index of the vector. Throws out_of_range error if the index is invalid.
     * 
     * @param index index of the required value.
     * @return const double&. A const reference to the element at the required index.
     */
    inline const double &at(int index) const{
        return (*this)[index];
    }

    
    // Arithmetic operations

    /**
     * @brief computes the sum of self and Vector v.
     * 
     * @param v The Vector to add
     * @return Vector. The result of addition.
     */
    Vector operator + (const Vector &v) const;

    /**
     * @brief computes the difference of self and Vector v.
     * 
     * @param v The Vector to subtract
     * @return Vector. The result of subtraction.
     */
    Vector operator - (const Vector &v) const;

    /**
     * @brief computes the product of self and double d.
     * 
     * @param v The multiplying factor
     * @return Vector. The result of multiplication.
     */
    Vector operator * (const double &d) const;

    /**
     * @brief returns the vector obtained by dividing self by double d. Throws an exception if d is zero.
     * 
     * @param v The (nonzero)factor to divide by
     * @return Vector. The result of division.
     */
    Vector operator / (double d) const;

    /**
     * @brief adds Vector v to self. Returns a const reference to self for chaining like so: v2 += (v1 += v);
     * 
     * @param v The vector that is to be added to self
     * @return const Vector&.
     */
    const Vector &operator+=(const Vector &v);
    
    /**
     * @brief subtracts Vector v from self. Returns a const reference to self for chaining like so: v2 += (v1 -= v);
     * 
     * @param v The vector that is to be subtracted from self
     * @return const Vector&.
     */
    const Vector &operator-=(const Vector &v);
    
    /**
     * @brief multiplies self by factor. Returns a const reference to self for chaining like so: v2 = (v1 *= 3);
     * 
     * @param v The double that is to be multiplied to self
     * @return const Vector&.
     */
    const Vector &operator*=(const double &factor);
    
    /**
     * @brief divides self by factor. Returns a const reference to self for chaining like so: v2 = (v1 /= 3);
     * 
     * @param v The double by which self is to be divided
     * @return const Vector&.
     */
    const Vector &operator/=(double factor);
    

    // inner products and norms

    /**
     * @brief Computes the dot product of Vectors self and v. Raises invalid_argument error if the dimensions do not match.
     * 
     * @param v The vector to compute the dot product with.
     * @return double. The computed dot product
     */
    double dot(const Vector &v) const;

    /**
     * @brief Computes the k-norm of the Vector.
     * 
     * @param k. The norm required. Defaults to 2.
     * @return double. The computed norm.
     */
    inline double norm(int k=2) const;

    /**
     * @brief Normalizes the Vector according to its k-norm. throws invalid_argument exception when the k-norm is 0.
     * 
     * @param modify if true, normalizes self itself. Otherwise returns a new normalized Vector.
     * @param k The type of norm required.
     * @return Vector. Either self(if modify is true) or a new Vector. In each case the returned Vector is normalized.
     */
    Vector normalized(bool modify=false, int k = 2);


    // special function, required for reduced matrix forms
    
    /**
     * @brief scales the vector such that the element at the index is now 1. Throws an exception if the element at the index is 0.
     * 
     * @param index The index to set to 1
     * @param modify modifies the vector itself to be the scaled version if true. Returns a copy of the scaled object otherwise. 
     * @return Vector 
     */
    Vector set_component_to_1(int index, bool modify=false);

    // iterators. We use the std::vector<double>::iterator as the underlying iterator, all operations on the iterators are done on the container vector's iterator object.

    std::vector<double>::iterator begin(){ return vec.begin(); }
    std::vector<double>::iterator end(){ return vec.end(); }
};

/**
 * @brief multiplies v by factor and returns the result
 * 
 * @param factor the scalar to multiply v by
 * @param v The Vector to be multiplied
 * @return Vector. The result of the multiplication
 */
Vector operator*(const double &factor, const Vector &v){
    return v * factor;
}

/**
 * @brief Utility function to print the Vector in a Python-style list format.
 * 
 * @param ost The std::ostream stream to print to
 * @param v The Vector to print.
 */
inline void operator<<(std::ostream &ost, const Vector &v);

/**
 * @brief returns the dimension/length/size of the vector.
 * @note see also dim and Vector::size.
 * @return int. The dimension of the vector
 */
inline int len(const Vector &v){ return v.size(); }

/**
 * @brief returns the dimension/length/size of the vector.
 * @note see also len and Vector::size.
 * @return int. The dimension of the vector
 */
inline int dim(const Vector &v){ return v.size(); }

#endif
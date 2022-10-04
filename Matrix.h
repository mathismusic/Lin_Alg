#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <exception>
#include "Vector.h"

// General:
// change ref to not scale to 1.
// functions to perform ERMs
// rank. add, subtr, scalar mult, solving linear equations, Gram Schmidt

// class for Square: inherit from General
// Determinant from ref storing the sign for swaps
// inverse by rref(A|I)
// adjugate from inverse if rank=n, if rank<n-1 then 0, rank = n-1 -> calculate each coeff, O(n^5)
// 

class Matrix;
inline std::ostream& operator << (std::ostream& c, const Matrix&);
/**
 * @brief Class implementing a 2D matrix.
 * 
 * @note All indices start from 0.
 * @note An empty matrix has order (0,0).
 * 
 */
class Matrix{
    std::vector<Vector> mat;
public:
    /**
     * @brief Construct a new empty Matrix object
     * 
     */
    Matrix(){}
    /**
     * @brief Construct a new Matrix object with dimensions m*n
     * 
     * @param m Number of rows in the matrix
     * @param n Number of columns in the matrix
     */
    Matrix(int m, int n): mat{n,Vector(m)}{}
    /**
     * @brief Construct a new Matrix object from the given initializer list
     * 
     * @example Matrix({{1,2},{3,4},{5,6}}) 
     * creates a 3*2 matrix when byColumns is false and a 2*3 matrix when byColumns is true.
     * 
     * @param init Initializer list used to create the matrix.
     * @param byColumns True if the initializer list contains columns of the matrix, and false otherwise.
     */
    Matrix(std::initializer_list<std::initializer_list<double> > init, bool byColumns=false);
    /**
     * @brief Gives the dimensions of the matrix as the std::pair {num_rows, num_columns}.
     * 
     * @return std::pair<int,int> 
     */
    std::pair<int,int> order() const
    {
        if(mat.size()==0)
            return std::pair<int,int> (0,0);
        return std::pair<int,int> (mat.at(0).size(), mat.size());
    }
    /**
     * @brief Returns a const reference to the (i,j)th element of the matrix
     * 
     * @param i row number of the required element
     * @param j column number of the required element
     * @return const double& 
     */
    const double& at(int i, int j) const
    {
        if(i<0||i>=mat.at(0).size()||j<0||j>=mat.size())
        {
            std::cerr<<"index out of bounds"<<std::endl;
            throw std::out_of_range("index out of bounds");
        }
        return mat.at(j).at(i);
    }
    /**
     * @brief Returns a reference to the (i,j)th element of the matrix
     * 
     * @param i row number of the required element
     * @param j column number of the required element
     * @return const double& 
     */
    double& at(int i, int j){
        if(i<0||i>=mat.at(0).size()||j<0||j>=mat.size())
        {
            std::cerr<<"index out of bounds"<<std::endl;
            throw std::out_of_range("index out of bounds");
        }
        return mat.at(j).at(i);
    }
    /**
     * @brief Returns a reference to the ith column of the matrix
     * 
     * @param i index of the column
     * @return const std::vector<Vector>& 
     */
    const Vector& at(int i) const{
        return mat.at(i);
    }

    Vector& at(int i){
        return mat.at(i);
    }
    /**
     * @brief Returns the product of two matrices
     * 
     * @return Matrix Product of the two matrices 
     */
    Matrix operator *(const Matrix &m);
    /**
     * @brief Returns a new matrix which is the transpose of the original matrix
     * 
     * @param modify if modify is true, then the given matrix is changed to its transpose
     * @return Matrix transpose of the given matrix
     */
    Matrix transpose(bool modify = false){
        Matrix m(order().second, order().first);
        for(int i{0};i<order().first;i++)
            for(int j{0};j<order().second;j++)
                m.at(j,i) = at(i,j);
        if(modify)
            *this = m;
        return std::move(m);
    }
    /**
     * @brief Returns one possible column echelon form of the given matrix
     * 
     * @param modify if modify is true, then the given matrix is changed to its column echelon form
     * @return Matrix one possible column echelon form of the given matrix
     */
    Matrix cef(bool modify = false){ 
        Matrix res(*this);
        res.cef(0, 0);
        if (modify) 
            *this = res;
        return std::move(res); 
    }
    /* to test */
    /**
     * @brief Returns one possible column echelon form of the given matrix
     * 
     * @param modify throws an exception if modify is true, since a const matrix cannot be modified 
     * @return Matrix one possible column echelon form of the given matrix
     */
    Matrix cef(bool modify=false) const{
        if (modify){
            std::cerr << "error in cef: cannot modify const matrix.\n";
            throw 4;
        }
        Matrix res(*this);
        res.cef(0, 0);
        return std::move(res); 
    }
protected: //change to private if not needed
    Matrix &cef(int start_row, int start_col);
public:
    /**
     * @brief Returns the reduced column echelon form of the given matrix
     * 
     * @param modify if modify is true, then the given matrix is changed to its reduced column echelon form
     * @return Matrix one possible reduced column echelon form of the given matrix
     */
    Matrix rcef(bool modify = false){ 
        Matrix res(*this);
        res.rcef(0, 0);
        if (modify) 
            *this = res;
        return std::move(res); 
    }
protected: //change to private if not needed
    Matrix &rcef(int start_row, int start_col);
protected:
//returns the number if columns in the matrix
    int size(){
        return mat.size();
    }
public:
    /**
     * @brief Returns the reduced row echelon form of the given matrix
     * 
     * @param modify if modify is true, then the given matrix is changed to its reduced row echelon form
     * @return Matrix one possible reduced row echelon form of the given matrix
     */
    Matrix rref(bool modify=false){
        Matrix res(this->transpose());
        res.rcef(0, 0).transpose(true);
        if (modify)
            *this = res;
        return std::move(res);
    }
    /**
     * @brief Runs the Gram-Schmidt algorithm on the columns of a copy of the given matrix.
     * 
     * @param modify if true, then the given matrix is modified.
     * @return Matrix 
     */
    Matrix GramSchmidt(bool modify=false);

    /**
     * @brief Multiplies a given row/column at the jth index of the matrix with a nonzero scalar c.
     * @param j index of the row/column
     * @param c Scalar which is to be multiplied
     * @param columnOperation Multiplies the jth column by c if true, else multiplies the jth row by c.
     */
    inline void Mj(int j, double c, bool columnOperation=false);
    /**
     * @brief Swaps the row/column at index j with the row/column at index k
     * 
     * @param j 
     * @param k 
     * @param columnOperation If true, then the jth and kth columns are swapped, otherwise rows are swapped.
     */
    inline void Pjk(int j, int k, bool columnOperation=false){
        if (columnOperation)
            std::swap(at(j), at(k));
        else 
        for (int i = 0; i < mat.size(); i++){
            // for each i(column), do the following.
            auto tmp = at(j, i);
            at(j, i) = at(k, i);
            at(k, i) = tmp;
        }
    }
    /**
     * @brief C_j = C_j+lambda*C_k (if columnOperation is true), R_j = R_j+lambda*R_k otherwise
     * 
     * @param j 
     * @param k 
     * @param lambda 
     * @param columnOperation 
     */
    inline void Ejk(int j, int k, double lambda, bool columnOperation=false);

    /**
     * @brief 
     * 
     * @param type 
     * @param j 
     * @param k 
     * @param lambda 
     */
    inline void elementaryColumnOperation(const std::string &type, int j, int k, double lambda=0);
    /**
     * @brief 
     * 
     * @param type 
     * @param j 
     * @param k 
     * @param lambda 
     */
    inline void elementaryRowOperation(const std::string &type, int j, int k, double lambda=0);
    /* to check */
    inline int rank() const{
        int r = 0;
        Matrix cef_ = cef();
        for (const auto &col: cef_.mat)
            if (!(col.isZero())) r++;
        return r;
    }

    //finding the QR decomposition of any matrix
    std::pair<Matrix, Matrix> QR();
};

inline std::ostream& operator << (std::ostream& c, const Matrix& m){
    if (m.order().first == 0) c<<"[]";
    else{
        for (int i = 0; i < m.at(0).size(); i++){
            c << '[';
            for(int j = 0; j < m.order().first; j++){
                c << m.at(j).at(i);
                if (j != m.order().first - 1) 
                    c << ", ";
            }
            c << "]\n";
        }
    }
    c<<'\b';
    return c;
}

#endif
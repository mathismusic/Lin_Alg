#include <iostream>
#include <vector>
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
inline void print(const Matrix&);

class Matrix : public std::vector<Vector>{
public:
    Matrix(){}
    Matrix(int m, int n): vector<Vector>(n,Vector(m))
    {}
    Matrix(std::initializer_list<std::initializer_list<double> > init, bool byColumns=false){
        if (init.size() == 0) 
            return;

        for (auto &column: init)
            if (column.size() != init.begin()->size()){
                std::cerr << "Invalid matrix - All sublists must have same size\n";
                throw 0;
            }

        if (byColumns)
            for (auto &column: init){
                push_back(Vector(column));
            }
        else
            for (int column_no = 0; column_no < init.begin()->size(); column_no++){
                Vector current_column;
                for (auto &row: init)
                    current_column.push_back(*(row.begin() + column_no));
                push_back(current_column);
            }          
    }

    std::pair<int,int> order() const
    {
        if(size()==0)
            return std::pair<int,int> (0,0);
        return std::pair<int,int> (at(0).size(), size());
    }

    const double& at(int i, int j) const
    {
        if(i<0||i>=at(0).size()||j<0||j>=size())
        {
            std::cerr<<"index out of bounds"<<std::endl;
            throw 0;
        }
        return at(j).at(i);
    }

    double& at(int i, int j){
        if(i<0||i>=at(0).size()||j<0||j>=size())
        {
            std::cerr<<"index out of bounds"<<std::endl;
            throw 0;
        }
        return at(j).at(i);
    }

    using std::vector<Vector>::at;
    
    Matrix operator *(const Matrix &m)
    {
        if(order().second!=m.order().first)
        {
            std::cerr<<"Matrices incompatible for multiplication"<<std::endl;
            throw 0;
        }
        Matrix product(order().first,m.order().second);
        for(int i{0};i<order().first;i++)
        {
            for(int j{0};j<m.order().second;j++)
            {
                for(int k{0};k<order().second;k++)
                {
                    product.at(i,j)+=at(i,k)*m.at(k,j);
                }
            }
        }
        return move(product);
    }
    Matrix transpose(bool modify = false)
    {
        Matrix m(order().second, order().first);
        for(int i{0};i<order().first;i++)
            for(int j{0};j<order().second;j++)
                m.at(j,i) = at(i,j);
        if(modify)
            *this = m;
        return move(m);
    }

    Matrix cef(bool modify = false){ 
        Matrix res(*this);
        res.cef(0, 0);
        if (modify) 
            *this = res;
        return move(res); 
    }
    /* to test */
    Matrix cef(bool modify=false) const{
        if (modify){
            std::cerr << "error in cef: cannot modify const matrix.\n";
            throw 4;
        }
        Matrix res(*this);
        res.cef(0, 0);
        return move(res); 
    }

    Matrix &cef(int start_row, int start_col){
        print(*this);
        std::cout << std::endl;
        if (start_row == at(0).size() || start_col == size()) return *this; // do nothing more
        bool allzero = true;
        for (int column = start_col; column < size(); column++)
            if (std::abs(at(start_row, column)) > EPSILON){
                allzero = false;
                at(start_col).swap(at(column));
                break;
            }
        if (allzero) return cef(start_row + 1, start_col);

        at(start_col).set_component_to_1(start_row, true);
        for (int column = start_col + 1; column < size(); column++)
            at(column) -= (at(start_row, column) * at(start_col));
        return cef(start_col + 1, start_row + 1);
    }

    Matrix rcef(bool modify = false){ 
        Matrix res(*this);
        res.rcef(0, 0);
        if (modify) 
            *this = res;
        return move(res); 
    }

    Matrix &rcef(int start_row, int start_col){
        print(*this);
        std::cout << std::endl;
        if (start_row == at(0).size() || start_col == size()) return *this; // do nothing more
        bool allzero = true;
        for (int column = start_col; column < size(); column++)
            if (std::abs(at(start_row, column)) > EPSILON){
                allzero = false;
                at(start_col).swap(at(column));
                break;
            }
        if (allzero) return rcef(start_row + 1, start_col);

        at(start_col).set_component_to_1(start_row, true);
        for (int column = 0; column < size(); column++){ // only change from cef -> rcef
            if (column == start_col) 
                continue;
            at(column) -= (at(start_row, column) * at(start_col));
        }
        return rcef(start_col + 1, start_row + 1);
    }

    Matrix rref(bool modify=false){
        Matrix res(this->transpose());
        res.rcef(0, 0).transpose(true);
        if (modify)
            *this = res;
        return move(res);
    }

    Matrix GramSchmidt(bool modify=false){
        Matrix res;
        for (int i = 0; i < order().first; i++){
            Vector vn{at(i)};
            for(auto &k:res)
            {
                vn-=(vn.dot(k))*k;
            }
            try{
                vn.normalize(true);
            }
            catch(...)
            {}
            res.push_back(vn);
        }
        if (modify)
            *this = res;
        return move(res);
    }


    inline void Mj(int j, double c, bool columnOperation=false){
        if (std::abs(c) < EPSILON){
            std::cerr << "error in Mj: M_j(0) is not allowed.\n";
            throw 2;
        }
        if (columnOperation)
            at(j) *= c;
        // must modify that row's elem in every column - visualize, the columns are strewn somewhere on the heap and are reined in by a vector of pointers(the data of a Vector), also on the heap.
        else for (int i = 0; i < size(); i++) 
            at(j, i) *= c;
    }

    inline void Pjk(int j, int k, bool columnOperation=false){
        if (columnOperation)
            at(j).swap(at(k));
        else 
        for (int i = 0; i < size(); i++){
            // for each i(column), do the following.
            auto tmp = at(j, i);
            at(j, i) = at(k, i);
            at(k, i) = tmp;
        }
    }

    inline void Ejk(int j, int k, double lambda, bool columnOperation=false){
        if (std::abs(lambda) < EPSILON)
            return; // do nothing in this case.
        if (columnOperation) 
            at(j) += lambda * at(k);
        else
        for (int i = 0; i < size(); i++)
            at(j, i) += lambda * at(k, i);
    }

    inline void elementaryColumnOperation(const std::string &type, int j, int k, double lambda=0){
        if (j < 0 || j >= size() || k < 0 || k >= size()){
            std::cerr << "error in column operation: invalid input indices.\n";
            throw 3;
        }
        if (type == "M")
            Mj(j, k, true);
        else if (type == "P")
            Pjk(j, k, true);
        else if (type == "E")
            Ejk(j, k, lambda, true);
        else{
            std::cerr << "Invalid argument to column operation: first argument must be P/E/M.\n";
            throw 3;
        }
    }
    inline void elementaryRowOperation(const std::string &type, int j, int k, double lambda=0){
        if (j < 0 || j >= order().first || k < 0 || k >= order().first){
            std::cerr << "error in row operation: invalid input indices.\n";
            throw 3;
        }
        if (type == "M")
            Mj(j, k);
        else if (type == "P")
            Pjk(j, k);
        else if (type == "E")
            Ejk(j, k, lambda);
        else{
            std::cerr << "Invalid argument to row operation: first argument must be P/E/M.\n";
            throw 3;
        }
    }
    /* to check */
    inline int rank() const{
        int r = 0;
        Matrix cef_ = cef();
        for (const auto &col: cef_)
            if (!(col.isZero())) r++;
        return r;
    }
};

inline void print(const Matrix &m){
    if (m.size() == 0) return;
    for (int i = 0; i < m.at(0).size(); i++){
        std::cout << '[';
        for(int j = 0; j < m.size(); j++){
            std::cout << m.at(j).at(i);
            if (j != m.size() - 1) 
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
}

class SquareMatrix: public Matrix{
public:
    SquareMatrix(){}
    SquareMatrix(int m): Matrix{m,m}
    {}
    SquareMatrix(std::initializer_list<std::initializer_list<double> > i): Matrix{i}
    {
        if(order().first!=order().second)
        {
            std::cerr<<"invalid initializer_list for square matrix"<<std::endl;
            throw 1;
        }
    }
private:
    double det(int start_row = 0, int start_col = 0){
        if (start_row == at(0).size() || start_col == size())
        {
            double x{1};
            for(int i{0};i<order().first;i++)
            {
                x*=at(i,i);
            }
            return x;
        }
        bool allzero = true;
        for (int column = start_col; column < size(); column++)
            if (std::abs(at(start_row, column)) > EPSILON){
                allzero = false;
                at(start_col).swap(at(column));
                break;
            }
        if (allzero) return 0;
        double x = at(start_row, start_col);
        for (int column = start_col + 1; column < size(); column++)
            at(column) -= (at(start_row, column) * at(start_col))/x;
        return det(start_col + 1, start_row + 1);
    }
public:
    friend inline double det(const SquareMatrix &s);
};

inline double det(const SquareMatrix &s){
    SquareMatrix scpy{s};
    return scpy.det();
}

#include<iostream>
#include "Matrix.h"
using namespace std;

//implement arithmatic operations

Matrix::Matrix(std::initializer_list<std::initializer_list<double> > init, bool byColumns){
    if (init.size() == 0) 
        return;

    for (auto &column: init)
        if (column.size() != init.begin()->size()){
            std::cerr << "Invalid matrix - All sublists must have same size\n";
            throw std::invalid_argument("Invalid matrix - All sublists must have same size\n");
        }

    if (byColumns)
        for (auto &column: init){
            mat.push_back(Vector(column));
        }
    else
        for (int column_no = 0; column_no < init.begin()->size(); column_no++){
            Vector current_column;
            for (auto &row: init)
                current_column.push_back(*(row.begin() + column_no));
            mat.push_back(current_column);
        }          
}

Matrix Matrix::operator *(const Matrix &m){
    if(order().second!=m.order().first)
    {
        std::cerr<<"Matrices incompatible for multiplication"<<std::endl;
        throw std::invalid_argument("Matrices incompatible for multiplication");
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
    return std::move(product);
}

Matrix &Matrix::cef(int start_row, int start_col){
    if (start_row == at(0).size() || start_col == mat.size()) return *this; // do nothing more
    bool allzero = true;
    for (int column = start_col; column < mat.size(); column++)
        if (std::abs(at(start_row, column)) > EPSILON){
            allzero = false;
            std::swap(at(start_col), at(column));
            break;
        }
    if (allzero) return cef(start_row + 1, start_col);

    at(start_col).set_component_to_1(start_row, true);
    for (int column = start_col + 1; column < mat.size(); column++)
        at(column) -= (at(start_row, column) * at(start_col));
    return cef(start_col + 1, start_row + 1);
}

Matrix &Matrix::rcef(int start_row, int start_col){
    if (start_row == at(0).size() || start_col == mat.size()) return *this; // do nothing more
    bool allzero = true;
    for (int column = start_col; column < mat.size(); column++)
        if (std::abs(at(start_row, column)) > EPSILON){
            allzero = false;
            std::swap(at(start_col), at(column));
            break;
        }
    if (allzero) return rcef(start_row + 1, start_col);

    at(start_col).set_component_to_1(start_row, true);
    for (int column = 0; column < mat.size(); column++){ // only change from cef -> rcef
        if (column == start_col) 
            continue;
        at(column) -= (at(start_row, column) * at(start_col));
    }
    return rcef(start_col + 1, start_row + 1);
}

Matrix Matrix::GramSchmidt(bool modify){
    Matrix res;
    for (int i = 0; i < order().second; i++){ //recheck
        Vector vn{at(i)};
        for(auto &k:res.mat)
        {
            vn-=(vn.dot(k))*k;
        }
        try{
            vn.normalized(true);
        }
        catch(...)
        {}
        res.mat.push_back(vn);
    }
    if (modify)
        *this = res;
    return std::move(res);
}

inline void Matrix::Mj(int j, double c, bool columnOperation){
    if (std::abs(c) < EPSILON){
        std::cerr << "error in Mj: M_j(0) is not allowed.\n";
        throw std::invalid_argument("error in Mj: M_j(0) is not allowed.\n");
    }
    if (columnOperation)
        at(j) *= c;
    // must modify that row's elem in every column - visualize, the columns are strewn somewhere on the heap and are reined in by a vector of pointers(the data of a Vector), also on the heap.
    else for (int i = 0; i < mat.size(); i++) 
        at(j, i) *= c;
}

inline void Matrix::Ejk(int j, int k, double lambda, bool columnOperation){
    if (std::abs(lambda) < EPSILON)
        return; // do nothing in this case.
    if (columnOperation) 
        at(j) += lambda * at(k);
    else
    for (int i = 0; i < mat.size(); i++)
        at(j, i) += lambda * at(k, i);
}

inline void Matrix::elementaryColumnOperation(const std::string &type, int j, int k, double lambda){
    if (j < 0 || j >= mat.size() || k < 0 || k >= mat.size()){
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

inline void Matrix::elementaryRowOperation(const std::string &type, int j, int k, double lambda){
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

std::pair<Matrix, Matrix> Matrix::QR(){
    Matrix Q = GramSchmidt();
    Matrix R{order().second, order().second};
    for(int i{0}; i<order().second; i++){
        for(int j{i}; j<order().second; j++){
            R.at(i,j) = at(j).dot(Q.at(i));
        }
    }
    return {Q, R};
}
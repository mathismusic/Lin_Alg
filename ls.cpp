#include "ls.h"

std::vector<Vector> LS_Solver::solve(const Matrix &A, const Vector &b){
    Matrix Ab = A.augment(b);
    Ab.rref(true);
    std::vector<bool> isPivotal(Ab.order().second); 
    int temp = 0;
    for(int i{0}; i<Ab.order().second; i++){
        
    }
}


Vector LS_Solver::retrieve(const std::vector<bool> &isPivotal, int non_pivotal_col, const Vector &b){
    Vector res(isPivotal.size()); // isPivotal.size() = number of columns = size of x
    res[non_pivotal_col] = 1;
    for (int i = 0; i < isPivotal.size(); i++){
        if (isPivotal[i])
    }
}

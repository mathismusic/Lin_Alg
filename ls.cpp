#include "ls.h"

std::vector<Vector> LS_Solver::solve(const Matrix &A, const Vector &b){
    Matrix Ab = A.augment(b);
    Ab.rref(true);
    std::vector<bool> isPivotal(Ab.order().second); 
    //find the pivotal columns
    int last_zero = -1;
    for(int i{0}; i<Ab.order().second; i++){
        isPivotal.at(i) = (std::abs(Ab.at(i, last_zero+1)) > EPSILON);
        while((last_zero < Ab.order().first - 1) && (std::abs(Ab.at(i, last_zero + 1)) > EPSILON)) 
            last_zero++;
    }
    //no solution if the last column is pivotal
    if (isPivotal.at(Ab.order().first - 1))
        return std::vector<Vector>(0);
    std::vector<Vector> ans(0);
    for(int i{0}; i<Ab.order().second - 1; i++){
        if (isPivotal.at(i)) continue;
        ans.push_back(retrieve(isPivotal, i, b));
    }
    return ans;
}


Vector LS_Solver::retrieve(const std::vector<bool> &isPivotal, int non_pivotal_col, const Vector &b){
    int n = isPivotal.size(); // isPivotal.size() = number of columns n = size of x as well
    Vector res(n);
    res[non_pivotal_col] = 1;
    int j = 0;
    for (int i = 0; i < isPivotal.size(); i++){
        if (isPivotal.at(i)){
            res[i] = b[j]; j++;
        }
    }
    return res;
}

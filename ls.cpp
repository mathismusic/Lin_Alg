#include "ls.h"

std::vector<Vector> LS_Solver::solve(const Matrix &A, const Vector &b){
    Matrix Ab = A.augment(b);
    Ab.rref(true);
    std::vector<bool> isPivotal(Ab.order().second); 
    // to find the pivotal columns, essentially we must find the 1s in the pivotal rows, the corresponding columns are what we need. 
    // so we iterate in a one-dimensional fashion always moving to the right starting on the first row, 
    // and if we meet a 1 on that row we update the pivotal columns then move down to the next row *starting from the next column* - due to the rref invariant. 
    int i = 0, j = 0;
    while (i < Ab.order().first && j < Ab.order().second){
        if (std::abs(Ab.at(i, j)) > EPSILON){
            isPivotal.at(j) = true; i++; j++;
        }
        else {
            j++;
        }
    }

    // no solution if the last column is pivotal
    if (isPivotal.at(Ab.order().first - 1))
        return std::vector<Vector>();
    std::vector<Vector> ans;
    for(int i{0}; i<Ab.order().second - 1; i++){
        if (isPivotal.at(i)) continue;
        ans.push_back(retrieve(isPivotal, i, b - Ab.at(i)));
    }
    return ans;
}


Vector LS_Solver::retrieve(const std::vector<bool> &isPivotal, int non_pivotal_col, const Vector &b){
    int n = isPivotal.size(); // isPivotal.size() = number of columns n = size of 'x' as well
    Vector res(n);
    res[non_pivotal_col] = 1;
    int j = 0;
    for (int i = 0; i < n; i++){
        if (isPivotal.at(i)){
            res[i] = b[j]; j++;
        }
    }
    return res;
}

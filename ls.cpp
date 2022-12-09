#include "ls.h"

std::pair<Vector, std::vector<Vector>> LS_Solver::solve(const Matrix &A, const Vector &b){
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

    for (int i = 0; i < Ab.order().second; i++) std::cout << isPivotal.at(i) << " ";
    std::cout << std::endl;

    // no solution if the last column is pivotal
    if (isPivotal.at(Ab.order().second - 1))
        return {Vector(), std::vector<Vector>()};
    std::vector<Vector> ans;

    const Vector& rref_b = Ab.at(Ab.order().second - 1);
    for(int i{0}; i<Ab.order().second - 1; i++){
        if (isPivotal.at(i)) continue;
        std::cout << i << std::endl;
        ans.push_back(retrieve(rref_b, i, Ab.at(i), isPivotal));
    }

    int n = isPivotal.size() - 1; // isPivotal.size() = number of columns of Ab = n + 1
    Vector mu(n); // the mean solution
    // extending rref_b to the right dimension setting all non-pivotal columns to 0.
    int row = 0;
    for (int j = 0; j < n; j++){
        if (isPivotal.at(j)){
            mu[j] = rref_b[row]; row++;
        }
    }
    return {mu, ans};
}


Vector LS_Solver::retrieve(const Vector &b, int non_pivotal_col_index, const Vector &non_pivotal_col, const std::vector<bool> &isPivotal){
    int n = isPivotal.size() - 1; // isPivotal.size() = number of columns of Ab = n + 1
    Vector res(n);
    res[non_pivotal_col_index] = 1;
    int row = 0;
    for (int j = 0; j < n; j++){
        if (isPivotal.at(j)){
            res[j] = b[row] - non_pivotal_col[row]; // think about it as x1(Column1) + ... = b. Then we are setting 
            // x_(non_pivotal_col_index) = 1, and we want xj. If Cj isn't pivotal xj is just 0. Otherwise, (using the fact that the pivotal rows are exactly the first few rows) xj is just (b - non_pivotal_col)[row] where row is the row where the '1' is present in Cj.            
            row++; // set up for the next pivotal row.
        }
    }
    return res;
}

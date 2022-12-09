#include "Matrix.h"
#pragma once

class LS_Solver{
    /**
     * @brief class to solve systems of linear equations of the form Ax = b.
     * 
     */
    LS_Solver(){}
    /**
     * @brief finds a basis vector for the system by setting a particular non-pivotal column's corresponding (free) variable to 1 and all other free variables to 0.
     * 
     * @return Vector A particular basis vector for the solution set.
     */
    static Vector retrieve(const Vector &b, int non_pivotal_col_index, const Vector &non_pivotal_col, const std::vector<bool> &isPivotal);
public:
    /**
     * @brief Function to solve the system Ax = b. 
     * 
     * @return std::pair<Vector, std::vector<Vector>> the first element of the pair is a solution of Ax = b, the Vectors in the std::vector<Vector> form a basis of the solution set. If the function returns std::pair{b, A}, then the solutions of the system are of the form b+Ax, where x is a Vector with the appropriate dimensions. 
     */
    static std::pair<Vector, std::vector<Vector>> solve(const Matrix &A, const Vector &b);
};
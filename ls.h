#include "Matrix.h"
#pragma once

class LS_Solver{
    /**
     * @brief class to solve systems of linear equations of the form Ax = b.
     * 
     */
    LS_Solver(){}
    /**
     * @brief Retrieves the solution if the solution is guaranteed to be unique.
     * 
     * @return Vector The unique solution x to Ax = b
     */
    static Vector retrieve(const std::vector<bool> &isPivotal, int non_pivotal_col, const Vector &b);
public:
    /**
     * @brief Function to solve the system Ax = b. 
     * 
     * @return std::vector<Vector> returns a basis of the solution set, and an empty std::vector if the system is inconsistent.
     */
    static std::vector<Vector> solve(const Matrix &A, const Vector &b);
};
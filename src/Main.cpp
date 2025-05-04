/*  Author: <Thelet.Shevach@gmail.com>
 *  Main.cpp – Demonstration of SquareMat library features.
 */

 #include "SquareMat.h"
 #include <iostream>
 #include <iomanip>
 
 using mat::SquareMat;
 
 //------------------------------------------------------------------------------
 // Helper: Print a section header and matrix
 //------------------------------------------------------------------------------
 void printMatrixSection(const std::string& title, const SquareMat& M) {
     std::cout << "=== " << title << " ===\n";
     std::cout << M << "\n";
 }
 
 int main() {
     // --------------------------------------------------------------------------
     // 1) Construct matrices
     // --------------------------------------------------------------------------
     SquareMat A = SquareMat::from_string("1 2 3, 4 5 6, 7 8 9");
     SquareMat B(3, 1.0);
     SquareMat C = SquareMat::from_string(
         "3 0 1, 2 4 1, 4 2 1");  // custom 3×3 matrix
 
     printMatrixSection("Matrix A (from_string)", A);
     printMatrixSection("Matrix B (3×3 filled with 1.0)", B);
     printMatrixSection("Matrix C (custom 3×3)", C);
 
     // --------------------------------------------------------------------------
     // 2) Element access & update
     // --------------------------------------------------------------------------
     B[1][2] = 42.0;
     printMatrixSection("B after B[1][2] = 42", B);
 
     std::size_t row = 1, col = 2;
     double val = A[row][col];
     std::cout << "A[" << row << "][" << col << "] = "
               << val << "\n\n";
 
     // --------------------------------------------------------------------------
     // 3) Basic arithmetic operations
     // --------------------------------------------------------------------------
     printMatrixSection("A + B",        A + B);
     printMatrixSection("A % 5",        A % 5);
 
     SquareMat D = A; D %= 5;
     printMatrixSection("D = A; D %= 5", D);
 
     printMatrixSection("A % B",        A % B);
     D = A; D %= B;
     printMatrixSection("D = A; D %= B", D);
 
     printMatrixSection("A * B",        A * B);
     printMatrixSection("A ^ 2",        A ^ 2);
 
     // --------------------------------------------------------------------------
     // 4) Determinants
     // --------------------------------------------------------------------------
     std::cout << "det(A) = " << !A << "\n"
               << "det(C) = " << !C << "\n\n";
 
     // --------------------------------------------------------------------------
     // 5) Comparisons by sum of elements
     // --------------------------------------------------------------------------
     std::cout << (A >= B ? "A >= B\n" : "A < B\n");
     std::cout << (A == B ? "A == B\n" : "A != B\n");
     std::cout << "\n";
 
     // --------------------------------------------------------------------------
     // 6) Compound assignment examples
     // --------------------------------------------------------------------------
     SquareMat E = SquareMat::from_string("1 2, 3 4");
     printMatrixSection("E initial", E);
 
     E += SquareMat::from_string("2 1, 1 2");
     printMatrixSection("E += [[2,1],[1,2]]", E);
 
     E -= SquareMat::from_string("1 1, 1 1");
     printMatrixSection("E -= [[1,1],[1,1]]", E);
 
     E *= 2.0;
     printMatrixSection("E *= 2.0", E);
 
     E /= 2.0;
     printMatrixSection("E /= 2.0", E);
 
     E %= 2;
     printMatrixSection("E %= 2", E);
 
     E += 3;
     printMatrixSection("E += 3", E);
 
     E -= 1.5;
     printMatrixSection("E -= 1.5", E);
 
     // --------------------------------------------------------------------------
     // 7) Increment / decrement operations
     // --------------------------------------------------------------------------
     SquareMat F = A;
     printMatrixSection("F (copy of A)", F);
 
     ++F;
     printMatrixSection("++F (pre-increment)", F);
 
     F++;
     printMatrixSection("F++ (post-increment)", F);
 
     --F;
     printMatrixSection("--F (pre-decrement)", F);
 
     F--;
     printMatrixSection("F-- (post-decrement)", F);
 
     return 0;
 }
 
 
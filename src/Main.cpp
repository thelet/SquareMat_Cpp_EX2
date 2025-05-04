// Main.cpp
#include "SquareMat.h"
#include <iostream>

using mat::SquareMat;

int main() {
    // Build A (3×3 from string) and B (3×3 filled with 1.0)
    SquareMat A = SquareMat::from_string("1 2 3, 4 5 6, 7 8 9");
    SquareMat B(3, 1.0);
    SquareMat C = SquareMat::from_string("3 0 1 2 4, 1 4 2 1 1, 2 3 5 -6 3, 4 2 4 2 7, 1 2 4 0 2");

    // Each std::cout << M << "\n" uses operator<< row-by-row
    std::cout << "Matrix A:\n"
              << A << "\n\n";

    std::cout << "Matrix B:\n"
              << B << "\n\n";
    
    B[1][2] = 42.0;
    
    std::cout << "Matrix B after changing the cell at [1][2]:\n"
              << B << "\n\n";

    std::size_t row = 1, col = 2;      // zero-based indices
    double value = A[row][col];        // retrieves the element at (1,2)
          
    std::cout << "A[" << row << "][" << col << "] = "
              << value << std::endl;
    
    std::cout << "A + B:\n"
              << (A + B) << "\n\n";

    std::cout << "A % 5:\n"
              << (A % 5) << "\n\n";
    A %= 5;
    std::cout << "A after A %= 5:\n"
              << A << "\n\n";
    
    std::cout << "A % B:\n"
              << (A % B) << "\n\n";
    A %= B;
    std::cout << "A after A %= B:\n"
              << A << "\n\n";

    std::cout << "A * B:\n"
              << (A * B) << "\n\n";

    std::cout << "A ^ 2:\n"
              << (A ^ 2) << "\n\n";

    std::cout << "det(A) = " << !A << "\n";
    std::cout << "det(C) = " << !C << "\n";

    if (A >= B) {
        std::cout << "A is greater-or-equal to B ("
                  << A.total() << " ≥ " << B.total() << ")\n";
    }
    else{
        std::cout << "B is greater-or-equal to A("
        << B.total() << " ≥ " << A.total() << ")\n";
    }

    A[2][2] +=5;
    std::cout << "After A[2][2] += 5\n" << A << "\n\n";

    if (A == B) {
        std::cout << "A is-equal to B ("
                  << A.total() << " = " << B.total() << ")\n";
    }
    else{
        std::cout << "A is not equal to B("
        << A.total() << " !=" << B.total() << ")\n";
    }

    A += 2;
    std::cout << "After A += 2:\n" << A << "\n\n";
    
    // 2) Compound assignment: subtract B from A in-place
    A -= B;  // now A = [1 2;3 4] – [0 1;1 0] = [1 1;2 4]
    std::cout << "After A -= B:\n" << A << "\n\n";

    // Multiply A by itself
    A *= A;  // matrix-multiply: A = A × A
    std::cout << "After A *= A:\n" << A << "\n\n";

    // Scale by 0.5
    A *= 0.5;  // every cell halved
    std::cout << "After A *= 0.5:\n" << A << "\n\n";

    // 3) Increment / decrement
    ++A;    // add 1 to every cell (pre-increment)
    std::cout << "After ++A:\n" << A << "\n\n";

    A++;    // post-increment (old value returned, but mutated)
    std::cout << "After A++:\n" << A << "\n\n";

    --A;    // pre-decrement
    std::cout << "After --A:\n" << A << "\n\n";

    A--;    // post-decrement
    std::cout << "After A--:\n" << A << "\n\n";

    return 0;
}

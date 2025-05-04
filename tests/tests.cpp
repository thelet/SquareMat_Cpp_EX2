#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SquareMat.h"
#include <stdexcept>

using mat::SquareMat;
using std::invalid_argument;

// 1. Addition and subtraction (valid, mismatch)
TEST_CASE("Matrix addition and subtraction - valid") {
    SquareMat A = SquareMat::from_string("1 2 3,4 5 6,7 8 9");
    SquareMat B = SquareMat::from_string("9 8 7,6 5 4,3 2 1");
    CHECK((A + B) == SquareMat::from_string("10 10 10,10 10 10,10 10 10"));
    CHECK((B - A) == SquareMat::from_string("8 6 4,2 0 -2,-4 -6 -8"));
}

TEST_CASE("Matrix addition/subtraction dimension mismatch") {
    SquareMat A(2,1.0), B(3,2.0);
    CHECK_THROWS_AS(A + B, invalid_argument);
    CHECK_THROWS_AS(B - A, invalid_argument);
}

// 2. Unary negation
TEST_CASE("Unary negation") {
    SquareMat M = SquareMat::from_string("1 -2,0 3");
    CHECK((-M) == SquareMat::from_string("-1 2,0 -3"));
}

// 3. Matrix multiplication (valid, zero, mismatch)
TEST_CASE("Matrix multiplication valid and zero-matrix") {
    SquareMat C = SquareMat::from_string("1 2,3 4");
    SquareMat D = SquareMat::from_string("5 6,7 8");
    CHECK((C * D) == SquareMat::from_string("19 22,43 50"));
    SquareMat Z(2,0.0);
    CHECK((C * Z) == Z);
}

TEST_CASE("Matrix multiplication dimension mismatch") {
    SquareMat A(2,1.0), E(3,1.0);
    CHECK_THROWS_AS(A * E, invalid_argument);
    CHECK_THROWS_AS(E * A, invalid_argument);
}

// 4. Scalar multiplication/division (both orders, zero, negative)
TEST_CASE("Scalar multiplication and division") {
    SquareMat M = SquareMat::from_string("1 2,3 4");
    CHECK((M * 2) == SquareMat::from_string("2 4,6 8"));
    CHECK((2 * M) == SquareMat::from_string("2 4,6 8"));
    CHECK((M * -1.5) == SquareMat::from_string("-1.5 -3,-4.5 -6"));
    CHECK((M / 2) == SquareMat::from_string("0.5 1,1.5 2"));
    CHECK_THROWS_AS(M / 0, invalid_argument);
}

// 5. Element-wise modulo
TEST_CASE("Element-wise and scalar modulo") {
    SquareMat M = SquareMat::from_string("5 7,9 11");
    SquareMat N = SquareMat::from_string("2 3,4 5");
    CHECK((M % N) == SquareMat::from_string("10 21,36 55"));
    CHECK((M % 4) == SquareMat::from_string("1 3,1 3"));
}

// 6. Power operator
TEST_CASE("Power operator") {
    SquareMat D = SquareMat::from_string("2 0,0 3");
    CHECK((D ^ 0) == SquareMat::from_string("1 0,0 1"));
    CHECK((D ^ 1) == D);
    CHECK((D ^ 3) == SquareMat::from_string("8 0,0 27"));
}

// 7. Transpose
TEST_CASE("Transpose operator") {
    SquareMat M = SquareMat::from_string("1 2 3,4 5 6,7 8 9");
    CHECK((~M) == SquareMat::from_string("1 4 7,2 5 8,3 6 9"));
}

// 8. Element access and update
TEST_CASE("Element access and bounds checking") {
    SquareMat M = SquareMat::from_string("1 2,3 4");
    CHECK(M[0][1] == doctest::Approx(2));
    M[1][0] = 9;
    CHECK(M == SquareMat::from_string("1 2,9 4"));
    CHECK_THROWS_AS(M[2][0], invalid_argument);
    CHECK_THROWS_AS(M[0][2], invalid_argument);
}

// 9. Comparisons
TEST_CASE("Comparison operators") {
    SquareMat A(2,1.0), B(2,2.0);
    CHECK(A <  B);
    CHECK(A <= B);
    CHECK(!(A >  B));
    CHECK(!(A >= B));
    CHECK(A != B);
    CHECK( A == A);
}

// 10. Determinant
TEST_CASE("Determinant operator") {
    CHECK(!SquareMat::from_string("4 7,2 6") == doctest::Approx(10));
    CHECK(!SquareMat::from_string("1 0,0 1") == doctest::Approx(1));
}

// 11. Compound assignment operators
TEST_CASE("Compound assignment operators") {
    SquareMat A = SquareMat::from_string("1 2,3 4");
    SquareMat B = SquareMat::from_string("2 3,4 5");

    A += B;
    CHECK(A == SquareMat::from_string("3 5,7 9"));

    A -= B;
    CHECK(A == SquareMat::from_string("1 2,3 4"));

    A *= B;
    CHECK(A == SquareMat::from_string("10 13,22 29"));

    A /= 2;
    CHECK(A == SquareMat::from_string("5 6.5,11 14.5"));

    A %= B;
    CHECK(A == SquareMat::from_string("10 19.5,44 72.5"));

    // chaining element-wise modulo
    A = SquareMat::from_string("1 2,3 4");
    A %= 2;
    CHECK(A == SquareMat::from_string("1 0,1 0"));

    // scalar addition/subtraction on fresh matrix
    SquareMat C = SquareMat::from_string("1 2,3 4");
    C += 5;
    CHECK(C == SquareMat::from_string("6 7,8 9"));
    C -= 3;
    CHECK(C == SquareMat::from_string("3 4,5 6"));
}

// 12. Constructor and parsing errors Constructor and parsing errors
TEST_CASE("Constructor and from_string errors") {
    CHECK_THROWS_AS(SquareMat(0), invalid_argument);
    CHECK_THROWS_AS(SquareMat::from_string("1 2 3"), invalid_argument);
}

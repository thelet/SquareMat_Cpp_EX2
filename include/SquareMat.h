/*  Author: <Thelet.Shevach@gmail.com
 *  SquareMat.h – public API & inline helpers.
 */
 #ifndef SQUARE_MAT_H
 #define SQUARE_MAT_H
 
 #include <cstddef>
 #include <iostream>
 #include <stdexcept>
 #include <string>
 
 namespace mat {
 
 class SquareMat {
     std::size_t n;    // dimension (n×n)
     double*    data;  // heap array of length n*n
 
     //─── Private helpers ──────────────────────────────────────
     void   copy_from(const SquareMat& other);      // deep-copy
     double sum()          const;                   // sum of all elements
     double determinant_gauss() const;              // O(n³) determinant
 
     // raw cell access
     double&       cell(std::size_t r, std::size_t c)       { return data[r*n + c]; }
     const double& cell(std::size_t r, std::size_t c) const { return data[r*n + c]; }
 
 public:
     //─── Rule of Three ───────────────────────────────────────
     /// fill-value constructor
     explicit SquareMat(std::size_t dim, double val = 0.0);
     /// from C-array
     SquareMat(std::size_t dim, const double* raw);
     SquareMat(const SquareMat&);                // copy ctor
     SquareMat& operator=(const SquareMat&);     // copy assign
     ~SquareMat();                                // destructor
 
     //─── Static factory ─────────────────────────────────────
     /** Parse string "a b c, d e f, g h i" into a 3×3 matrix. */
     static SquareMat from_string(const std::string& spec);
 
     //─── Element access via [][ ] with bounds-check ─────────
     class Row {
         double* ptr;
         std::size_t len;
     public:
         Row(double* p, std::size_t l) : ptr(p), len(l) {}
         double&       operator[](std::size_t c) {
             if (c >= len) throw std::invalid_argument("column index out of range");
             return ptr[c];
         }
         const double& operator[](std::size_t c) const {
             if (c >= len) throw std::invalid_argument("column index out of range");
             return ptr[c];
         }
     };
     Row       operator[](std::size_t r) {
         if (r >= n) throw std::invalid_argument("row index out of range");
         return Row(data + r*n, n);
     }
     const Row operator[](std::size_t r) const {
         if (r >= n) throw std::invalid_argument("row index out of range");
         return Row(data + r*n, n);
     }
 
     std::size_t size()  const { return n; }     // dimension
     double      total() const { return sum(); } // alias for tests
 
     //─── Arithmetic (non-mutating) ──────────────────────────
     SquareMat operator+ (const SquareMat&) const; // mat+mat
     SquareMat operator- (const SquareMat&) const; // mat-mat
     SquareMat operator- ()                    const; // unary -
     SquareMat operator* (const SquareMat&) const; // mat×mat
     SquareMat operator* (double)           const; // mat×scalar
     friend SquareMat operator*(double s, const SquareMat& m) { return m*s; } // scalar×mat
     SquareMat operator/ (double)           const; // mat/scalar
     SquareMat operator% (const SquareMat&) const; // element-wise
     SquareMat operator% (int k)            const; // element mod k
     SquareMat operator^ (unsigned int p)   const; // power
     SquareMat operator+ (double)           const; // mat+scalar
     SquareMat operator- (double)           const; // mat-scalar
 
     //─── Compound assignment (mutating) ─────────────────────
     SquareMat& operator+=(const SquareMat&);
     SquareMat& operator-=(const SquareMat&);
     SquareMat& operator*=(const SquareMat&);
     SquareMat& operator*=(double);
     SquareMat& operator/=(double);
     SquareMat& operator%=(const SquareMat&);
     SquareMat& operator%=(int);
     SquareMat& operator+=(double);
     SquareMat& operator-=(double);
 
     //─── Increment / Decrement ──────────────────────────────
     SquareMat& operator++();      // pre-increment (+1 each cell)
     SquareMat  operator++(int);   // post-increment
     SquareMat& operator--();      // pre-decrement
     SquareMat  operator--(int);   // post-decrement
 
     //─── Transpose & Determinant ────────────────────────────
     SquareMat operator~ () const; // transpose
     double    operator! () const; // determinant
 
     //─── Comparisons (by sum of elements) ───────────────────
     bool operator==(const SquareMat&) const;
     bool operator!=(const SquareMat&) const;
     bool operator< (const SquareMat&) const;
     bool operator<=(const SquareMat&) const;
     bool operator> (const SquareMat&) const;
     bool operator>=(const SquareMat&) const;
 
     //─── I/O ─────────────────────────────────────────────────
     friend std::ostream& operator<<(std::ostream&, const SquareMat&);
     friend std::istream& operator>>(std::istream&, SquareMat&);
     /// Convenience print + newline
     void print(std::ostream& out = std::cout) const { out << *this << '\n'; }
 };
 
 } // namespace mat
 
 #endif // SQUARE_MAT_H
 
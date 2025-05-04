# SquareMat — Comprehensive Square Matrix Library

**Author:** Thelet.Shevach@gmail.com

## 📜 Overview

`SquareMat` is a C++ library for square real-valued matrices, built from the ground up without any STL containers. It demonstrates

- Operator overloading (arithmetic, comparison, I/O, indexing)
- Custom dynamic memory management (`new[]`/`delete[]`)
- Rule-of-Three (deep copy, assignment, destructor)
- Exception safety and bounds checking
- Determinant calculation via Gaussian elimination
- Exponentiation by squaring
- Thorough unit tests (doctest)

This repo includes a clean demo (`Main.cpp`) and a rigorous test suite.

---

## 🗂️ Project Structure

```
project-root/
├── include/
│   └── SquareMat.h        # Public API + inline helpers
├── src/
│   ├── SquareMat_core.cpp # Constructors, destructor, from_string, helpers
│   ├── SquareMat_math.cpp # Arithmetic (+, -, *, /, %, ^), scalar ops & compounds
│   ├── SquareMat_cmp.cpp  # Comparison operators (==, !=, <, <=, >, >=)
│   ├── SquareMat_io.cpp   # I/O (operator<<, operator>>, print)
│   └── Main.cpp           # Organized demo of all features
├── tests/
│   └── tests.cpp          # doctest suite covering every operator & error case
├── obj/                   # Object files (auto-generated)
├── bin/                   # Binaries (Main, test)
├── Makefile               # Build targets: Main, test, valgrind, clean
└── README.md              # This file
```

---

## 🎯 Features & API

### Construction & Memory

- `SquareMat(size_t dim, double val = 0.0)` — fill-value ctor
- `SquareMat(size_t dim, const double* raw)` — from C-array
- `SquareMat(const SquareMat&)` / `operator=` / `~SquareMat()` — deep copy and clean-up
- `static SquareMat from_string(const string&)` — parse e.g. "1 2,3 4" into 2×2

### Element Access

- `m[r][c]` with bounds checking (`invalid_argument` on out-of-range)
- `size()` returns dimension `n`
- `total()` returns sum of all elements (for tests & comparisons)

### Arithmetic Operators (Non-Mutating)

- **Matrix–Matrix:** `+`, `-`, `%` (Hadamard), `*` (product)
- **Scalar:** `*`, `/`, `%` (int mod), `+`, `-`
- **Unary:** `-` (negation), `~` (transpose), `^` (power)

### Compound Assignments (Mutating)

- `+=`, `-=`, `*=`, `/=`, `%=`, for both matrix and scalar variants

### Increment & Decrement

- `++m`, `m++`, `--m`, `m--` (add/subtract 1 to every element)

### Determinant & Comparison

- `!m` — determinant via Gaussian elimination (O(n³))
- `==, !=, <, <=, >, >=` — compare by **sum** of elements

### I/O

- `operator<<` — prints each row on its own line, space-separated
- `operator>>` — reads `n` then `n*n` values
- `print()` — convenience wrapper

---

## 🛠️ Building & Testing

```bash
# Build & run demo
make Main
./bin/Main

# Build & run unit tests
make test

# Memory-leak check via Valgrind
make valgrind

# Clean artifacts
make clean
```

All unit tests pass and Valgrind reports **zero** leaks.

---

## 📖 Demo Highlights (Main.cpp)

The organized `Main.cpp` illustrates:

1. Matrix construction
2. Element access & mutation
3. Arithmetic: +, %, \*, ^
4. Determinants
5. Comparisons
6. Compound assignments
7. Pre/post increments

Each operation is presented with a labeled section for clarity.

---

## 🧪 Testing Strategy

`tests/tests.cpp` (doctest) covers:

- Valid & invalid addition, subtraction, multiplication
- Scalar operations (zero, negative, order)
- Modulo (matrix vs scalar, int mod)
- Power, transpose, determinant
- Bounds-check on `[][]`
- Comparisons by sum
- Compound assignments for matrix and scalar
- Constructor errors and parsing invalid inputs

---

## 🎓 Implementation Notes

- Manual `new[]`/`delete[]`, no STL containers
- Strong exception safety
- Bounds checking in row proxy
- Efficient power via exponentiation-by-squaring
- Determinant via in-place Gaussian elimination

---

**Enjoy exploring** the `SquareMat` library! Feel free to fork & extend.
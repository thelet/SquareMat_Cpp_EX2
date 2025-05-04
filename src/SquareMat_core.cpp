/*  Author: <Thelet.Shevach@gmail.com
 *  SquareMat_core.cpp : core class functions.
 */

#include "SquareMat.h"
#include <sstream>
#include <cmath>
#include <stdexcept>

using std::size_t;
using std::invalid_argument;

namespace mat {

void SquareMat::copy_from(const SquareMat& o) {
    n = o.n;
    data = new double[n*n];
    for (size_t i = 0; i < n*n; ++i) data[i] = o.data[i];
}

double SquareMat::sum() const {
    double s = 0.0;
    for (size_t i = 0; i < n*n; ++i) s += data[i];
    return s;
}

SquareMat::SquareMat(size_t dim, double val)
 : n(dim), data(nullptr)
{
    if (n == 0) throw invalid_argument("size must be >0");
    data = new double[n*n];
    for (size_t i = 0; i < n*n; ++i) data[i] = val;
}

SquareMat::SquareMat(size_t dim, const double* raw)
 : n(dim), data(nullptr)
{
    if (n == 0) throw invalid_argument("size must be >0");
    data = new double[n*n];
    for (size_t i = 0; i < n*n; ++i) data[i] = raw[i];
}

SquareMat::SquareMat(const SquareMat& o) { copy_from(o); }

SquareMat& SquareMat::operator=(const SquareMat& o) {
    if (this != &o) {
        delete[] data;
        copy_from(o);
    }
    return *this;
}

SquareMat::~SquareMat() {
    delete[] data;
}

SquareMat SquareMat::from_string(const std::string& spec) {
    std::string tmp = spec;
    for (char& c : tmp) if (c == ',') c = ' ';
    std::stringstream ss(tmp);

    double x; size_t count = 0;
    while (ss >> x) ++count;
    if (count == 0) throw invalid_argument("empty spec");

    size_t dim = static_cast<size_t>(std::sqrt(count));
    if (dim*dim != count) throw invalid_argument("not a square count");

    ss.clear(); ss.seekg(0);
    SquareMat M(dim);
    for (size_t i = 0; i < count; ++i) ss >> M.data[i];
    return M;
}

double SquareMat::determinant_gauss() const {
    if (n == 0) return 1.0;
    double* tmp = new double[n*n];
    for (size_t i = 0; i < n*n; ++i) tmp[i] = data[i];

    double det = 1.0;
    for (size_t k = 0; k < n; ++k) {
        size_t piv = k;
        for (size_t i = k+1; i < n; ++i)
            if (std::fabs(tmp[i*n + k]) > std::fabs(tmp[piv*n + k]))
                piv = i;
        if (std::fabs(tmp[piv*n + k]) < 1e-12) { det = 0; break; }
        if (piv != k) {
            for (size_t j = 0; j < n; ++j)
                std::swap(tmp[k*n+j], tmp[piv*n+j]);
            det = -det;
        }
        det *= tmp[k*n + k];
        double inv = 1.0 / tmp[k*n + k];
        for (size_t j = k; j < n; ++j) tmp[k*n + j] *= inv;
        for (size_t i = k+1; i < n; ++i) {
            double factor = tmp[i*n + k];
            for (size_t j = k; j < n; ++j)
                tmp[i*n+j] -= factor * tmp[k*n+j];
        }
    }
    delete[] tmp;
    return det;
}

SquareMat& SquareMat::operator++()    { for (size_t i = 0; i < n*n; ++i) ++data[i]; return *this; }
SquareMat  SquareMat::operator++(int) { SquareMat t(*this); ++(*this); return t; }
SquareMat& SquareMat::operator--()    { for (size_t i = 0; i < n*n; ++i) --data[i]; return *this; }
SquareMat  SquareMat::operator--(int) { SquareMat t(*this); --(*this); return t; }

SquareMat SquareMat::operator~() const {
    SquareMat r(n);
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            r.cell(j,i) = cell(i,j);
    return r;
}

double SquareMat::operator!() const {
    return determinant_gauss();
}

} // namespace mat

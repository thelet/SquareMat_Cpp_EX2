/*  Author: <Thelet.Shevach@gmail.com
 *  SquareMat_math.cpp : arithmetics operations .
 */

#include "SquareMat.h"
#include <cmath>
#include <stdexcept>

using std::size_t;
using std::invalid_argument;

namespace mat {

#define MATCH(o) if (n != (o).n) throw invalid_argument("size mismatch");

SquareMat SquareMat::operator+(const SquareMat& o) const {
    MATCH(o);
    SquareMat r(n);
    for (size_t i = 0; i < n*n; ++i) r.data[i] = data[i] + o.data[i];
    return r;
}

SquareMat SquareMat::operator-(const SquareMat& o) const {
    MATCH(o);
    SquareMat r(n);
    for (size_t i = 0; i < n*n; ++i) r.data[i] = data[i] - o.data[i];
    return r;
}

SquareMat SquareMat::operator-() const {
    SquareMat r(n);
    for (size_t i = 0; i < n*n; ++i) r.data[i] = -data[i];
    return r;
}

SquareMat SquareMat::operator*(const SquareMat& o) const {
    MATCH(o);
    SquareMat r(n,0.0);
    for (size_t i=0;i<n;++i)
        for (size_t k=0;k<n;++k) {
            double a = cell(i,k);
            for (size_t j=0;j<n;++j)
                r.cell(i,j) += a * o.cell(k,j);
        }
    return r;
}

SquareMat SquareMat::operator*(double s) const {
    SquareMat r(n);
    for (size_t i=0;i<n*n;++i) r.data[i] = data[i]*s;
    return r;
}

SquareMat SquareMat::operator/(double s) const {
    if (std::fabs(s)<1e-12) throw invalid_argument("division by zero");
    SquareMat r(n);
    for (size_t i=0;i<n*n;++i) r.data[i] = data[i]/s;
    return r;
}

SquareMat SquareMat::operator%(const SquareMat& o) const {
    MATCH(o);
    SquareMat r(n);
    for (size_t i=0;i<n*n;++i) r.data[i] = data[i]*o.data[i];
    return r;
}

SquareMat SquareMat::operator%(int k) const {
    SquareMat r(n);
    for (size_t i=0;i<n*n;++i) r.data[i] = std::fmod(data[i], double(k));
    return r;
}

SquareMat SquareMat::operator^(unsigned int p) const {
    if (p==0) {
        SquareMat id(n,0.0);
        for (size_t i=0;i<n;++i) id.cell(i,i)=1.0;
        return id;
    }
    SquareMat base(*this), res=base; --p;
    while (p) {
        if (p&1) res=res*base;
        base=base*base;
        p>>=1;
    }
    return res;
}

// compound matrix-matrix
SquareMat& SquareMat::operator+=(const SquareMat& o) {
    MATCH(o);
    for (size_t i=0;i<n*n;++i) data[i]+=o.data[i];
    return *this;
}
SquareMat& SquareMat::operator-=(const SquareMat& o) {
    MATCH(o);
    for (size_t i=0;i<n*n;++i) data[i]-=o.data[i];
    return *this;
}
SquareMat& SquareMat::operator*=(const SquareMat& o) {
    MATCH(o);
    SquareMat tmp = (*this) * o;
    return *this = tmp;
}
SquareMat& SquareMat::operator%=(const SquareMat& o) {
    MATCH(o);
    for (size_t i=0;i<n*n;++i) data[i]*=o.data[i];
    return *this;
}

// compound scalar
SquareMat& SquareMat::operator*=(double s) {
    for (size_t i=0;i<n*n;++i) data[i]*=s;
    return *this;
}
SquareMat& SquareMat::operator/=(double s) {
    if (std::fabs(s)<1e-12) throw invalid_argument("division by zero");
    for (size_t i=0;i<n*n;++i) data[i]/=s;
    return *this;
}
SquareMat& SquareMat::operator%=(int k) {
    for (size_t i=0;i<n*n;++i) data[i]=std::fmod(data[i], double(k));
    return *this;
}
SquareMat& SquareMat::operator+=(double s) {
    for (size_t i=0;i<n*n;++i) data[i]+=s;
    return *this;
}
SquareMat& SquareMat::operator-=(double s) {
    for (size_t i=0;i<n*n;++i) data[i]-=s;
    return *this;
}

} // namespace mat

/*  Author: <Thelet.Shevach@gmail.com
 *  SquareMat_io.cpp : I\O operations .
 */

#include "SquareMat.h"
#include <iostream>
#include <stdexcept>

namespace mat {

std::ostream& operator<<(std::ostream& out, const SquareMat& m) {
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m.size(); ++j)
            out << m[i][j] << (j+1<m.size()? ' ' : '\n');
    }
    return out;
}

std::istream& operator>>(std::istream& in, SquareMat& m) {
    size_t dim;
    if (!(in>>dim)) throw std::invalid_argument("failed to read dimension");
    SquareMat tmp(dim);
    for (size_t i=0;i<dim*dim;++i) {
        if (!(in>>tmp.data[i])) throw std::invalid_argument("failed to read data");
    }
    m = std::move(tmp);
    return in;
}

} // namespace mat

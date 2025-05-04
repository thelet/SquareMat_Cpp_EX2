/*  Author: <Thelet.Shevach@gmail.com
 *  SquareMat_cmp.cpp : comperison operations .
 */

#include "SquareMat.h"
#include <cmath>

namespace mat {

bool SquareMat::operator==(const SquareMat& o) const { return std::fabs(sum()-o.sum())<1e-9; }
bool SquareMat::operator!=(const SquareMat& o) const { return !(*this==o); }
bool SquareMat::operator< (const SquareMat& o) const { return sum() <  o.sum(); }
bool SquareMat::operator<=(const SquareMat& o) const { return sum() <= o.sum(); }
bool SquareMat::operator> (const SquareMat& o) const { return sum() >  o.sum(); }
bool SquareMat::operator>=(const SquareMat& o) const { return sum() >= o.sum(); }

} // namespace mat

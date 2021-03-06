//---------------------------------------------------------------------------
// symbolic_weight.cpp
//
// This file is part of Rhea.  Rhea is free software: you can redistribute
// it and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version 3
// of the License, or (at your option) any later version.
//
// Rhea is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
// more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Rhea.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2012-2014, nocte@hippie.nu
//---------------------------------------------------------------------------
#include "symbolic_weight.hpp"
#include <cassert>

namespace rhea
{

symbolic_weight::symbolic_weight()
{
    values_[0] = values_[1] = values_[2] = 0;
}

symbolic_weight::symbolic_weight(double w1, double w2, double w3)
{
    values_[0] = w1;
    values_[1] = w2;
    values_[2] = w3;
}

symbolic_weight symbolic_weight::zero()
{
    return symbolic_weight(0, 0, 0);
}

symbolic_weight& symbolic_weight::negate()
{
    for (double& v : values_)
        v = -v;

    return *this;
}

symbolic_weight& symbolic_weight::operator*=(double n)
{
    for (double& v : values_)
        v *= n;

    return *this;
}

symbolic_weight& symbolic_weight::operator/=(double n)
{
    assert(n != 0);
    for (double& v : values_)
        v /= n;

    return *this;
}

symbolic_weight& symbolic_weight::operator+=(const symbolic_weight& n)
{
    assert(levels() == n.levels());
    auto i1 = values_.begin();
    auto i2 = n.values_.begin();

    for (; i1 != values_.end(); ++i1, ++i2)
        *i1 += *i2;

    return *this;
}

symbolic_weight& symbolic_weight::operator-=(const symbolic_weight& n)
{
    assert(levels() == n.levels());
    auto i1 = values_.begin();
    auto i2 = n.values_.begin();

    for (; i1 != values_.end(); ++i1, ++i2)
        *i1 -= *i2;

    return *this;
}

bool symbolic_weight::operator<(const symbolic_weight& comp) const
{
    return values_ < comp.values_;
}

bool symbolic_weight::operator<=(const symbolic_weight& comp) const
{
    return values_ <= comp.values_;
}

bool symbolic_weight::operator==(const symbolic_weight& comp) const
{
    return values_ == comp.values_;
}

bool symbolic_weight::operator!=(const symbolic_weight& comp) const
{
    return values_ != comp.values_;
}

bool symbolic_weight::operator>=(const symbolic_weight& comp) const
{
    return values_ >= comp.values_;
}

bool symbolic_weight::operator>(const symbolic_weight& comp) const
{
    return values_ > comp.values_;
}

bool symbolic_weight::is_negative() const
{
    return values_ < zero().values_;
}

} // namespace rhea

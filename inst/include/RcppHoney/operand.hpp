// Copyright (C) 2016 Daniel C. Dillon
//
// This file is part of RcppHoney.
//
// RcppHoney is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// RcppHoney is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RcppHoney.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <Rcpp.h>
#include <stdint.h>
#include <cstddef>

namespace RcppHoney {

template< typename T, typename Iterator, typename Result >
class operand
{
public:
    typedef Iterator const_iterator;
    typedef const_iterator iterator;
    typedef Result result_type;

public:
    uint64_t length() const {
        return static_cast< const T * >(this)->length();
    }

    const_iterator begin() const {
        return static_cast< const T * >(this)->begin();
    }

    const_iterator end() const {
        return static_cast< const T * >(this)->end();
    }

    result_type operator[](ptrdiff_t n) const {
        return *(static_cast< const T * >(this)->begin() + n);
    }
};

} // namespace RcppHoney

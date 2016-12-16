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

#include <RcppHoneyForward.hpp>
#include <stdint.h>
#include <cstddef>

namespace RcppHoney {

template< typename T, typename T_ITER, typename T_RESULT >
class operand
{
public:
    typedef T_ITER const_iterator;
    typedef const_iterator iterator;
    typedef T_RESULT result_type;

public:
    dims_t dims() const {
        return static_cast< const T * >(this)->dims();
    }

    int64_t size() const {
        return static_cast< const T * >(this)->size();
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
    
    operator SEXP() const
    {
        const int RTYPE = Rcpp::traits::r_sexptype_traits< T_RESULT >::rtype;
        RcppHoney::dims_t dim = dims();
    
        if (dim.second == 0) {
            Rcpp::Shield< SEXP > x(Rf_allocVector(RTYPE, size()));
            std::copy(begin(), end(),
                Rcpp::internal::r_vector_start< RTYPE >(x));
            return x;
        } else {
            Rcpp::Shield< SEXP > x(Rf_allocMatrix(RTYPE, dim.first,
                dim.second));
            std::copy(begin(), end(),
                Rcpp::internal::r_vector_start< RTYPE >(x));
            return x;
        }
    }
};

} // namespace RcppHoney

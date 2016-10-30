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

#include <algorithm>
#include "../RcppHoneyForward.hpp"

namespace Rcpp {
namespace traits {

template< typename T, typename T_ITER, typename T_RESULT > SEXP wrap(
    const RcppHoney::operand< T, T_ITER, T_RESULT > &obj) {

    const int RTYPE = Rcpp::traits::r_sexptype_traits< T_RESULT >::rtype;
    RcppHoney::dims_t dims = obj.dims();

    if (dims.second == 0) {
        Shield< SEXP > x(Rf_allocVector(RTYPE, obj.size()));
        std::transform(obj.begin(), obj.end(), internal::r_vector_start< RTYPE >(x),
            internal::caster< T, T_RESULT >);
        return x;
    } else {
        Shield< SEXP > x(Rf_allocMatrix(RTYPE, dims.first, dims.second));
        std::transform(obj.begin(), obj.end(), internal::r_vector_start< RTYPE >(x),
            internal::caster< T, T_RESULT >);
        return x;
    }
}

} // namespace traits
} // namespace Rcpp

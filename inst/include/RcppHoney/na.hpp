// Copyright (C) 2016 Daniel C. Dillon
//
// This file is part of RcppHoney.
//
// Rcpp is free software: you can redistribute it and/or modify it
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

#include "r_headers.hpp"

namespace RcppHoney {

template< typename T >
struct na {};

template<>
struct na< int > {
    static const int VALUE() {return NA_INTEGER;}
    static const bool is_na(int val) {return NA_INTEGER == val;}
};

template<>
struct na< double > {
    static const double VALUE() {return NA_REAL;}
    static const bool is_na(double val) {return R_IsNA(val);}
};

} // namespace RcppHoney

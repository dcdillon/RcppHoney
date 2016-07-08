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

namespace RcppHoney {
namespace traits {

template< bool B, typename LHS = void, typename RHS = void >
struct if_else {};

template< typename LHS, typename RHS >
struct if_else< true, LHS, RHS > {
    typedef LHS type;
};

template< typename LHS, typename RHS >
struct if_else< false, LHS, RHS > {
    typedef RHS type;
};

} // namespace traits
} // namespace RcppHoney

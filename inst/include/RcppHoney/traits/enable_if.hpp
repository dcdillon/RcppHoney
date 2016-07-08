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

namespace RcppHoney {
namespace traits {

template< bool VAL, typename T >
struct enable_if {
};

template< typename T >
struct enable_if< true, T > {
    typedef T type;
};

} // namespace traits
} // namespace RcppHoney

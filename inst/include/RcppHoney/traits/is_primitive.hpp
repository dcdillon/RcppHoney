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

namespace RcppHoney {
namespace traits {

template< typename T >
struct is_primitive {
    static const bool value = false;
};

template<>
struct is_primitive< int > {
    static const bool value = true;
};

template<>
struct is_primitive< double > {
    static const bool value = true;
};

//template<>
//struct is_primitive< Rcomplex > {
//    static const bool value = true;
//};

} // namespace traits
} // namespace RcppHoney

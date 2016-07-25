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

#include "traits/integral_constant.hpp"
#include "traits/result_of.hpp"

namespace RcppHoney {

namespace hooks {

template< typename T >
T create_type();

traits::false_type is_hooked(...);

traits::true_type has_na(...);

traits::true_type needs_basic_operators(...);

traits::true_type needs_scalar_operators(...);

traits::int_constant< 1 > family(...);

template< typename T, typename U = typename T::const_iterator >
struct const_iterator {
    typedef typename T::const_iterator type;
};

} // namespace hooks

template< typename T, typename U = typename T::const_iterator >
struct hook {
    static const bool value = (sizeof(::RcppHoney::hooks::is_hooked(hooks::create_type< T >())) == sizeof(traits::true_type));
    static const bool NA = sizeof(hooks::has_na(hooks::create_type< T >())) == sizeof(traits::true_type);
    static const bool NEED_BASIC_OPERATORS = sizeof(hooks::needs_basic_operators(hooks::create_type< T>())) == sizeof(traits::true_type);
    static const bool NEED_SCALAR_OPERATORS = sizeof(hooks::needs_scalar_operators(hooks::create_type< T >())) == sizeof(traits::true_type);
    static const int FAMILY = sizeof(hooks::family(hooks::create_type< T >())) / sizeof(long); // this is suspect but should work
    typedef U const_iterator;
};


} // namespace RcppHoney

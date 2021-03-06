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

#include <RcppCommon.h>
#include "RcppHoney/traits/ctype.hpp"
#include "RcppHoney/traits/enable_if.hpp"
#include "RcppHoney/traits/if_else.hpp"
#include "RcppHoney/traits/integral_constant.hpp"
#include "RcppHoney/traits/is_primitive.hpp"
#include "RcppHoney/traits/result_of.hpp"
#include "RcppHoney/traits/widest_numeric_type.hpp"
#include <stdint.h>

namespace RcppHoney {

typedef std::pair< uint64_t, uint64_t > dims_t;

template< typename T, typename T_ITER, typename T_RESULT >
class operand;

template< typename LhsIterator, typename RhsIterator, typename Op,
    bool NA_VALUE >
class binary_operator;

namespace hooks {

static const int FAMILY_USER = 1024;

template< typename T, typename U = typename T::const_iterator >
struct const_iterator {
    typedef typename T::const_iterator type;
};


} // namespace hooks

} // namespace RcppHoney

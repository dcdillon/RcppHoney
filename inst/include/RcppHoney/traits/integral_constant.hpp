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

struct true_type {
    static const bool value = true;
};

struct false_type {
    static const bool value = false;
    char pad[64]; // makes sizeof(false_type) different than sizeof(true_type)
};

template< int VALUE >
struct int_constant {
    static const int value = VALUE;
    const long size[VALUE]; // makes sizeof(int_constant::size) == VALUE
};

} // namespace traits
} // namespace RcppHoney

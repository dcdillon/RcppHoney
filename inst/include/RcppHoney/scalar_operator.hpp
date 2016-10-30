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
#include <iterator>
#include <algorithm>
#include <cstddef>
#include "operand.hpp"

namespace RcppHoney {

template< typename T >
struct scalar_operator_iterator : public std::iterator< std::bidirectional_iterator_tag, T > {
private:
    T m_value;

public:
    inline scalar_operator_iterator() {}

    inline scalar_operator_iterator(const T &val) : m_value(val) {}

    inline T operator*() {
       return m_value;
    }

    inline scalar_operator_iterator &operator++() {
        return *this;
    }

    inline scalar_operator_iterator operator++(int) {
        return *this;
    }

    inline scalar_operator_iterator &operator--() {
         return *this;
    }

    inline scalar_operator_iterator operator--(int) {
        return *this;
    }

    inline bool operator==(const scalar_operator_iterator &rhs) const {
        return false;
    }

    inline bool operator!=(const scalar_operator_iterator &rhs) const {
        return !operator==(rhs);
    }
};

template< typename T >
struct scalar_operator_result_type {
    typedef T result_type;
};

template< typename T >
class scalar_operator : public operand< scalar_operator< T >, scalar_operator_iterator< T >, typename scalar_operator_result_type< T >::result_type > {
public:
    typedef typename scalar_operator_result_type< T >::result_type result_type;
    static const bool NA = false;

public:
    typedef scalar_operator_iterator< T > const_iterator;
    typedef const_iterator iterator;

private:
    T m_value;
public:
    scalar_operator(const T &val) :
        m_value(val) {}

    dims_t dims() const {return std::make_pair(-1, 0);}
    uint64_t size() const {return -1;}
    const_iterator begin() const {return const_iterator(m_value);}
    const_iterator end() const {return const_iterator(m_value);}
};

struct make_scalar_operator {
    template< typename T >
    scalar_operator< T > operator()(const T &obj) {
        return scalar_operator< T >(obj);
    }
};

} // namespace RcppHoney

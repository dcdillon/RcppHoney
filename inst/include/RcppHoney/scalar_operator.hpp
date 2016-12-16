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

#include <iterator>
#include <algorithm>
#include <cstddef>
#include "operand.hpp"

namespace RcppHoney {

template< typename T >
struct scalar_operator_iterator
    : public std::iterator< std::bidirectional_iterator_tag, T > {
private:
    T m_value;
    uint64_t m_count;

public:
    inline scalar_operator_iterator() {}

    inline scalar_operator_iterator(const T &val) : m_value(val), m_count(0) {}

    inline scalar_operator_iterator(const T &val, const uint64_t count)
        : m_value(val), m_count(count) {}
        
    inline T operator*() {
       return m_value;
    }

    inline scalar_operator_iterator &operator++() {
        ++m_count;
        return *this;
    }

    inline scalar_operator_iterator operator++(int) {
        scalar_operator_iterator i = *this;
        operator++();
        return i;
    }

    inline scalar_operator_iterator &operator--() {
        --m_count;
        return *this;
    }

    inline scalar_operator_iterator operator--(int) {
        scalar_operator_iterator i = *this;
        operator--();
        return i;
    }

    inline bool operator==(const scalar_operator_iterator &rhs) const {
        return m_count == rhs.m_count;
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
class scalar_operator
    : public operand<
        scalar_operator< T >,
        scalar_operator_iterator< T >,
        typename scalar_operator_result_type< T >::result_type
    > {
public:
    typedef typename scalar_operator_result_type< T >::result_type result_type;
    static const bool NA = false;

public:
    typedef scalar_operator_iterator< T > const_iterator;
    typedef const_iterator iterator;

private:
    T m_value;
    dims_t m_dims;
    
public:
    scalar_operator(const T &val) : m_value(val) {
        m_dims.first = -1;
        m_dims.second = 0;
    }
    
    scalar_operator(const T &val, uint64_t maxSize) : m_value(val) {
        m_dims.first = maxSize;
        m_dims.second = 0;
    }

    dims_t dims() const {return m_dims;}
    uint64_t size() const {return m_dims.first;}
    const_iterator begin() const {return const_iterator(m_value);}
    const_iterator end() const {return const_iterator(m_value, m_dims.first);}
};

struct make_scalar_operator {
    template< typename T >
    scalar_operator< T > operator()(const T &obj) {
        return scalar_operator< T >(obj);
    }
    
    template< typename T >
    scalar_operator< T > operator()(const T &obj, uint64_t count) {
        return scalar_operator< T >(obj, count);
    }
};

} // namespace RcppHoney

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

#include "operand.hpp"
#include <algorithm>
#include <iterator>

namespace RcppHoney {

template< typename T >
struct scalar_iterator : public std::iterator< std::random_access_iterator_tag, T > {
private:
    T m_value;
    bool m_end;

public:
    inline scalar_iterator() : m_end(true) {}

    inline scalar_iterator(const T &val, bool end = false) : m_value(val), m_end(end) {}

    inline T operator*() {
       return m_value;
    }

    inline T *operator->() {
        return &m_value;
    }

    inline scalar_iterator &operator+=(const typename std::iterator<std::random_access_iterator_tag, T>::difference_type n) {
        m_end = true;
        return *this;
    }

    inline scalar_iterator operator+(const typename std::iterator<std::random_access_iterator_tag, T>::difference_type n) const {
        scalar_iterator i = *this;
        i.m_end = true;
        return i;
    }

    inline scalar_iterator &operator-=(const typename std::iterator<std::random_access_iterator_tag, T>::difference_type n) {
        if (m_end) {
            m_end = false;
        }

        return *this;
    }

    inline scalar_iterator operator-(const typename std::iterator<std::random_access_iterator_tag, T>::difference_type n) const {
        scalar_iterator i = *this;
        i.m_end = false;
        return i;
    }

    inline scalar_iterator &operator++() {
        m_end = true;
        return *this;
    }

    inline scalar_iterator operator++(int) {
        scalar_iterator i = *this;
        operator++();
        return i;
    }

    inline scalar_iterator &operator--() {
        m_end = false;
        return *this;
    }

    inline scalar_iterator operator--(int) {
        scalar_iterator i = *this;
        operator--();
        return i;
    }

    inline bool operator==(const scalar_iterator &rhs) const {
        return m_end == rhs.m_end;
    }

    inline bool operator!=(const scalar_iterator &rhs) const {
        return !operator==(rhs);
    }

    friend inline ptrdiff_t operator-(const scalar_iterator &lhs, const scalar_iterator &rhs) {
        return ptrdiff_t(lhs.m_end) - ptrdiff_t(rhs.m_end);
    }
};

template< typename T >
struct scalar_result_type {
    typedef T result_type;
};

template< typename T >
class scalar : public operand< scalar< T >, scalar_iterator< T >, typename scalar_result_type< T >::result_type > {
public:
    typedef typename scalar_result_type< T >::result_type result_type;
    static const bool NA = false;

public:
    typedef scalar_iterator< T > const_iterator;
    typedef const_iterator iterator;

private:
    T m_value;
public:
    scalar(const T &val) :
        m_value(val) {}

    uint64_t length() const {return 1;}
    const_iterator begin() const {return const_iterator(m_value);}
    const_iterator end() const {return const_iterator(m_value, true);}

    operator bool() { return !!m_value; }
};

struct make_scalar {
    template< typename T >
    scalar< T > operator()(const T &obj) {
        return scalar< T >(obj);
    }
};

} // namespace RcppHoney

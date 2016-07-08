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

template< typename InputIterator, typename Op, bool NA_VALUE >
struct unary_operator_iterator : public std::iterator< std::random_access_iterator_tag, typename Op::return_type > {
private:
    InputIterator m_pos;
    const Op *m_operator;
    typename Op::return_type *m_value;

public:
    inline unary_operator_iterator() : m_operator(NULL), m_value(NULL) {}

    inline unary_operator_iterator(const InputIterator &pos, const Op *op) : m_pos(pos), m_operator(op), m_value(NULL) {}

    inline unary_operator_iterator(const unary_operator_iterator &rhs) : m_pos(rhs.m_pos), m_operator(rhs.m_operator), m_value(NULL) {}

    inline ~unary_operator_iterator() {
        if (m_value != NULL) {
            delete m_value;
        }
    }

    inline unary_operator_iterator &operator=(const unary_operator_iterator &rhs) {
        m_pos = rhs.m_pos;
        m_operator = rhs.m_operator;
    }

    inline typename Op::return_type operator*() {
       return (*m_operator)(m_pos);
    }

    inline typename Op::return_type *operator->() {
        if (m_value == NULL) {
            m_value = new typename Op::return_type((*m_operator)(m_pos));
        } else {
            *m_value = (*m_operator)(m_pos);
        }

        return m_value;
    }

    inline unary_operator_iterator &operator+=(const typename std::iterator<std::random_access_iterator_tag, typename Op::return_type>::difference_type n) {
        m_pos += n;
        return *this;
    }

    inline unary_operator_iterator operator+(const typename std::iterator<std::random_access_iterator_tag, typename Op::return_type>::difference_type n) const {
        unary_operator_iterator i = *this;
        i += n;
        return i;
    }

    inline unary_operator_iterator &operator-=(const typename std::iterator<std::random_access_iterator_tag, typename Op::return_type>::difference_type n) {
        m_pos -= n;
        return *this;
    }

    inline unary_operator_iterator operator-(const typename std::iterator<std::random_access_iterator_tag, typename Op::return_type>::difference_type n) const {
        unary_operator_iterator i = *this;
        i -= n;
        return i;
    }

    inline unary_operator_iterator &operator++() {
        ++m_pos;
        return *this;
    }

    inline unary_operator_iterator operator++(int) {
        unary_operator_iterator i = *this;
        operator++();
        return i;
    }

    inline unary_operator_iterator &operator--() {
        --m_pos;
         return *this;
    }

    inline unary_operator_iterator operator--(int) {
        unary_operator_iterator i = *this;
        operator--();
        return *this;
    }

    inline bool operator==(const unary_operator_iterator &rhs) const {
        return m_pos == rhs.m_pos;
    }

    inline bool operator!=(const unary_operator_iterator &rhs) const {
        return !operator==(rhs);
    }

    inline typename Op::return_type operator[](ptrdiff_t n) const {
        return *(*this + n);
    }

    friend inline ptrdiff_t operator-(const unary_operator_iterator &lhs, const unary_operator_iterator &rhs) {
        return lhs.m_pos - rhs.m_pos;
    }
};

template< typename InputIterator, typename Op, bool NA_VALUE >
struct unary_operator_result_type {
    typedef typename Op::return_type result_type;
};

template< typename InputIterator, typename Op, bool NA_VALUE >
class unary_operator : public operand< unary_operator< InputIterator, Op, NA_VALUE >, unary_operator_iterator< InputIterator, Op, NA_VALUE >, typename unary_operator_result_type< InputIterator, Op, NA_VALUE >::result_type > {
public:
    typedef typename unary_operator_result_type< InputIterator, Op, NA_VALUE >::result_type result_type;
    static const bool NA = NA_VALUE;

public:
    typedef unary_operator_iterator< InputIterator, Op, NA_VALUE > const_iterator;
    typedef const_iterator iterator;

private:
    InputIterator m_begin;
    InputIterator m_end;
    std::size_t m_length;
    Op m_operator;

public:
    unary_operator(const InputIterator &begin, const InputIterator &end, const Op &op) :
        m_begin(begin), m_end(end), m_length(end - begin), m_operator(op) {}

    uint64_t length() const {return m_length;}
    const_iterator begin() const {return const_iterator(m_begin, &m_operator);}
    const_iterator end() const {return const_iterator(m_end, &m_operator);}
};

template< bool NA >
struct make_unary_operator {
    template< typename T, typename Op >
    unary_operator< typename T::const_iterator, Op, NA > operator()(const T &obj, const Op &op) {
        return unary_operator< typename T::const_iterator, Op, NA >(obj.begin(), obj.end(), op);
    }
};

} // namespace RcppHoney

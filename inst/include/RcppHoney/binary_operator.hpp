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
#include "hook.hpp"
#include "exceptions.hpp"

namespace RcppHoney {

template< typename LhsIterator, typename RhsIterator, typename Op,
    bool NA_VALUE >
struct binary_operator_iterator : public std::iterator<
    std::bidirectional_iterator_tag,
    typename Op::return_type
> {
private:
    LhsIterator m_lhsPos;
    RhsIterator m_rhsPos;
    typename Op::return_type m_value;
    bool m_dirty;
    const Op *m_operator;

public:
    inline binary_operator_iterator() : m_dirty(true), m_operator(NULL) {}

    inline binary_operator_iterator(const LhsIterator &lhsPos,
        const RhsIterator &rhsPos, const Op *op) : m_lhsPos(lhsPos),
            m_rhsPos(rhsPos), m_dirty(true), m_operator(op) {}

    inline typename Op::return_type operator*() {
       if (m_dirty) {
           m_value = (*m_operator)(m_lhsPos, m_rhsPos);
           m_dirty = false;
       }

       return m_value;
    }

    inline binary_operator_iterator &operator++() {
        ++m_lhsPos;
        ++m_rhsPos;
        m_dirty = true;
        return *this;
    }

    inline binary_operator_iterator operator++(int) {
        binary_operator_iterator i = *this;
        operator++();
        return i;
    }

    inline binary_operator_iterator &operator--() {
        --m_lhsPos;
        --m_rhsPos;
        m_dirty = true;
        return *this;
    }

    inline binary_operator_iterator operator--(int) {
        binary_operator_iterator i = *this;
        operator--();
        return this;
    }

    inline bool operator==(const binary_operator_iterator &rhs) const {
        return m_lhsPos == rhs.m_lhsPos
            || m_rhsPos == rhs.m_rhsPos;
    }

    inline bool operator!=(const binary_operator_iterator &rhs) const {
        return !operator==(rhs);
    }
};

template< typename LhsIterator, typename RhsIterator, typename Op,
    bool NA_VALUE >
struct binary_operator_result_type {
    typedef typename Op::return_type result_type;
};

template< typename LhsIterator, typename RhsIterator, typename Op, bool NA_VALUE >
class binary_operator : public operand<
    binary_operator< LhsIterator, RhsIterator, Op, NA_VALUE >,
    binary_operator_iterator< LhsIterator, RhsIterator, Op, NA_VALUE >,
    typename binary_operator_result_type<
        LhsIterator,
        RhsIterator,
        Op,
        NA_VALUE
    >::result_type
> {
public:
    typedef typename Op::return_type result_type;
    static const bool NA = NA_VALUE;

public:
    typedef binary_operator_iterator<
        LhsIterator,
        RhsIterator,
        Op,
        NA_VALUE
    > const_iterator;
    typedef const_iterator iterator;

private:
    LhsIterator m_lhsBegin;
    LhsIterator m_lhsEnd;
    RhsIterator m_rhsBegin;
    RhsIterator m_rhsEnd;
    dims_t m_dims;
    Op m_operator;

public:
    binary_operator(LhsIterator lhsBegin, LhsIterator lhsEnd, dims_t lhsDims,
        RhsIterator rhsBegin, RhsIterator rhsEnd, dims_t rhsDims, const Op &op) :
            m_lhsBegin(lhsBegin), m_lhsEnd(lhsEnd), m_rhsBegin(rhsBegin),
                m_rhsEnd(rhsEnd), m_operator(op) {

        m_dims = m_operator.result_dims(lhsDims, rhsDims);
    }

    dims_t dims() const {return m_dims;}
    int64_t size() const {
        return (m_dims.second != 0) ? m_dims.first * m_dims.second
            : m_dims.first;
    }
    const_iterator begin() const {
        return const_iterator(m_lhsBegin, m_rhsBegin, &m_operator);
    }
    
    const_iterator end() const {
        return const_iterator(m_lhsEnd, m_rhsEnd, &m_operator);
    }
};

template< bool NA >
struct make_binary_operator
{
    template< typename LHS, typename RHS, typename Op >
    binary_operator<
        typename LHS::const_iterator,
        typename RHS::const_iterator,
        Op,
        NA
    > operator()(const LHS &lhs, const RHS &rhs, const Op &op) {
        return binary_operator<
            typename LHS::const_iterator,
            typename RHS::const_iterator,
            Op,
            NA
        >(lhs.begin(), lhs.end(), hooks::extract_dims(lhs), rhs.begin(),
            rhs.end(), hooks::extract_dims(rhs), op);
    }
};

} // namespace RcppHoney

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

#include <RcppHoneyForward.hpp>
#include "traits/widest_numeric_type.hpp"
#include "traits/ctype.hpp"
#include "na.hpp"
#include "exceptions.hpp"
#include "scalar_operator.hpp"

namespace RcppHoney {

template< typename LhsIterator, typename RhsIterator, bool NA_VALUE >
class cbinder_result_type {
public:
    typedef typename std::iterator_traits< LhsIterator >::value_type lhs_type;
    typedef typename std::iterator_traits< RhsIterator >::value_type rhs_type;
    typedef typename traits::widest_numeric_type<
        lhs_type,
        rhs_type
    >::type result_type;
};

template< typename LhsIterator, typename RhsIterator, bool NA_VALUE >
class cbinder_iterator :
    public std::iterator< std::bidirectional_iterator_tag,
        typename cbinder_result_type<
            LhsIterator,
            RhsIterator,
            NA_VALUE
        >::result_type
    > {
            
public:
    typedef typename cbinder_result_type< LhsIterator,
        RhsIterator, NA_VALUE >::result_type result_type;
    typedef typename std::iterator_traits< LhsIterator >::value_type lhs_type;
    typedef typename std::iterator_traits< RhsIterator >::value_type rhs_type;
    
private:
    bool m_dirty;
    bool m_onLhs;
    LhsIterator m_lhsPos;
    LhsIterator m_lhsEnd;
    RhsIterator m_rhsPos;
    RhsIterator m_rhsEnd;
    result_type m_value;
    
public:
    inline cbinder_iterator() : m_dirty(true), m_onLhs(true) {}

    inline cbinder_iterator(const LhsIterator &lhsPos,
        const LhsIterator &lhsEnd, const RhsIterator &rhsPos,
            const RhsIterator &rhsEnd) : m_dirty(true),
                m_onLhs(lhsPos != lhsEnd), m_lhsPos(lhsPos), m_lhsEnd(lhsEnd),
                    m_rhsPos(rhsPos), m_rhsEnd(rhsEnd) {}

    inline result_type operator*() {
       if (m_dirty) {
           if (m_onLhs) {
               if (NA_VALUE) {
                   lhs_type val = *m_lhsPos;
                   
                   if (na<
                           typename traits::ctype< lhs_type >::type
                       >::is_na(val)) {
                   
                       m_value = na< result_type >::VALUE();
                   } else {
                       m_value = val;
                   }
               } else {
                   m_value = *m_lhsPos;
               }
           } else {
               if (NA_VALUE) {
                   rhs_type val = *m_rhsPos;
                   
                   if (na<
                           typename traits::ctype< rhs_type >::type
                       >::is_na(val)) {
                   
                       m_value = na< result_type >::VALUE();
                   } else {
                       m_value = val;
                   }
               } else {
                   m_value = *m_rhsPos;
               }
           }
           
           m_dirty = false;
       }

       return m_value;
    }

    inline cbinder_iterator &operator++() {
        if (m_onLhs) {
            ++m_lhsPos;
            
            if (m_lhsPos == m_lhsEnd) {
                m_onLhs = false;
            }
        } else {
            ++m_rhsPos;
        }
        
        m_dirty = true;

        return *this;
    }

    inline cbinder_iterator operator++(int) {
        cbinder_iterator i = *this;
        operator++();
        return i;
    }

    inline cbinder_iterator &operator--() {
        if (m_onLhs) {
            --m_lhsPos;
            
            if (m_lhsPos == m_lhsEnd) {
                m_onLhs = false;
            }
        } else {
            --m_rhsPos;
        }
        
        m_dirty = true;
        
        return *this;
    }

    inline cbinder_iterator operator--(int) {
        cbinder_iterator i = *this;
        operator--();
        return this;
    }

    inline bool operator==(const cbinder_iterator &rhs) const {
        if (m_onLhs) {
            return m_lhsPos == rhs.m_lhsPos;
        } else {
            return m_rhsPos == rhs.m_rhsPos;
        }
    }

    inline bool operator!=(const cbinder_iterator &rhs) const {
        return !operator==(rhs);
    }
};
    
template< typename LhsIterator, typename RhsIterator, bool NA_VALUE >
class cbinder :
    public operand<
        cbinder< LhsIterator, RhsIterator, NA_VALUE >,
        cbinder_iterator< LhsIterator, RhsIterator, NA_VALUE >,
        typename cbinder_result_type<
            LhsIterator,
            RhsIterator,
            NA_VALUE
        >::result_type
    > {
        
public:
    typedef cbinder_iterator< LhsIterator, RhsIterator, NA_VALUE > const_iterator;
    typedef const_iterator iterator;
    typedef typename cbinder_result_type<
        LhsIterator,
        RhsIterator,
        NA_VALUE
    >::result_type result_type;
    
    static const bool NA = NA_VALUE;
    
private:
    LhsIterator m_lhsBegin;
    LhsIterator m_lhsEnd;
    RhsIterator m_rhsBegin;
    RhsIterator m_rhsEnd;
    dims_t m_dims;
    
public:
    cbinder(LhsIterator lhsBegin, LhsIterator lhsEnd, dims_t lhsDims,
        RhsIterator rhsBegin, RhsIterator rhsEnd, dims_t rhsDims) :
            m_lhsBegin(lhsBegin), m_lhsEnd(lhsEnd), m_rhsBegin(rhsBegin),
                m_rhsEnd(rhsEnd) {
                    
        if (lhsDims.first == -1) {
            if (rhsDims.first > 0) {
                m_dims.first = rhsDims.first
                    + ((rhsDims.second == 0) ? 1 : rhsDims.second);
            } else {
                throw bounds_exception();
            }
        } else if (rhsDims.first == -1) {
            if (lhsDims.first > 0) {
                m_dims.first = lhsDims.first
                    + ((lhsDims.second == 0) ? 1 : lhsDims.second);
            } else {
                throw bounds_exception();
            }
        } else if (lhsDims.second == 0 && rhsDims.second == 0) {
            if (lhsDims.first == rhsDims.first) {
                m_dims.first = lhsDims.first;
                m_dims.second = 2;
            } else {
                throw bounds_exception();
            }
        }
        else if (lhsDims.second == 0) {
            if (lhsDims.first == rhsDims.first) {
                m_dims.first = lhsDims.first;
                m_dims.second = rhsDims.second + 1;
            } else {
                throw bounds_exception();
            }
        } else if (rhsDims.second == 0) {
            if (lhsDims.first == rhsDims.first) {
                m_dims.first = lhsDims.first;
                m_dims.second = lhsDims.second + 1;
            } else {
                throw bounds_exception();
            }
        } else if (lhsDims.first == rhsDims.first) {
            m_dims.first = lhsDims.first;
            m_dims.second = lhsDims.second + rhsDims.second;
        } else {
            throw bounds_exception();
        }
    }
    
    dims_t dims() const {return m_dims;}
    int64_t size() const {
        return (m_dims.second != 0) ? m_dims.first * m_dims.second
            : m_dims.first;
    }
    
    const_iterator begin() const {
        return const_iterator(m_lhsBegin, m_lhsEnd, m_rhsBegin, m_rhsEnd);
    }
    
    const_iterator end() const {
        return const_iterator(m_lhsEnd, m_lhsEnd, m_rhsEnd, m_rhsEnd);
    }
};

template< bool NA >
struct make_cbinder
{
    template< typename LHS, typename RHS >
    cbinder< typename LHS::const_iterator, typename RHS::const_iterator, NA >
        operator()(const LHS &lhs, const RHS &rhs) {

        return cbinder<
            typename LHS::const_iterator,
            typename RHS::const_iterator,
            NA
        >(lhs.begin(), lhs.end(), hooks::extract_dims(lhs), rhs.begin(),
            rhs.end(), hooks::extract_dims(rhs));
    }
};

template< typename T, typename T_ITER, typename T_RESULT, typename U,
    typename U_ITER, typename U_RESULT >
RcppHoney::cbinder< T_ITER, U_ITER, (T::NA || U::NA) >
cbind(const RcppHoney::operand< T, T_ITER, T_RESULT > &lhs,
    const RcppHoney::operand< U, U_ITER, U_RESULT > &rhs) {
    return RcppHoney::make_cbinder< (T::NA || U::NA) >()(lhs, rhs);
}

template< typename T, typename T_ITER, typename T_RESULT, typename U >
typename RcppHoney::traits::enable_if<
    RcppHoney::traits::is_primitive< U >::value,
    RcppHoney::cbinder<
        T_ITER,
        typename RcppHoney::scalar_operator< U >::const_iterator,
        T::NA
    >
>::type
cbind(const RcppHoney::operand< T, T_ITER, T_RESULT > &lhs, const U &rhs) {
    return RcppHoney::make_cbinder< T::NA >()(lhs,
        RcppHoney::make_scalar_operator()(rhs, lhs.dims().first));
}

template< typename T, typename U, typename U_ITER, typename U_RESULT >
typename RcppHoney::traits::enable_if<
    RcppHoney::traits::is_primitive< T >::value,
    RcppHoney::cbinder<
        typename RcppHoney::scalar_operator< T >::const_iterator,
        U_ITER,
        U::NA
    >
>::type
cbind(const T &lhs, const RcppHoney::operand< U, U_ITER, U_RESULT > &rhs) {
    return RcppHoney::make_cbinder< U::NA >()(
        RcppHoney::make_scalar_operator()(lhs, rhs.dims().first), rhs);
}

template< typename T, typename U >
typename RcppHoney::traits::enable_if<
    (RcppHoney::hook< T >::value && RcppHoney::hook< U >::value),
    RcppHoney::cbinder<
        typename RcppHoney::hook< T >::const_iterator,
        typename RcppHoney::hook< U >::const_iterator,
        (RcppHoney::hook< T >::NA || RcppHoney::hook< U >::NA)
    >
>::type
cbind(const T &lhs, const U &rhs) {
    return RcppHoney::make_cbinder<
        (RcppHoney::hook< T >::NA || RcppHoney::hook< U >::NA)
    >()(lhs, rhs);
}
template< typename T, typename T_ITER, typename T_RESULT, typename U >
typename RcppHoney::traits::enable_if< RcppHoney::hook< U >::value,
    RcppHoney::cbinder<
        T_ITER,
        typename RcppHoney::hook< U >::const_iterator,
        (T::NA || RcppHoney::hook< U >::NA)
    >
>::type
cbind(const RcppHoney::operand< T, T_ITER, T_RESULT > &lhs, const U &rhs) {
    return RcppHoney::make_cbinder< (T::NA || RcppHoney::hook< U >::NA) >()(
        lhs,
        rhs);
}
template< typename T, typename U, typename U_ITER, typename U_RESULT >
typename RcppHoney::traits::enable_if< RcppHoney::hook< T >::value,
    RcppHoney::cbinder<
        typename RcppHoney::hook< T >::const_iterator,
        U_ITER,
        (U::NA || RcppHoney::hook< T >::NA)
    >
>::type
cbind(const T &lhs, const RcppHoney::operand< U, U_ITER, U_RESULT > &rhs) {
    return RcppHoney::make_cbinder< (U::NA || RcppHoney::hook< T >::NA) >()(
        lhs,
        rhs);
}
template< typename T, typename U >
typename RcppHoney::traits::enable_if<
    RcppHoney::traits::is_primitive< T >::value
    && RcppHoney::hook< U >::value,
    RcppHoney::cbinder<
        typename RcppHoney::scalar_operator< T >::const_iterator,
        typename RcppHoney::hook< U >::const_iterator,
        RcppHoney::hook< U >::NA
    >
>::type
cbind(const T &lhs, const U &rhs) {
    dims_t dims = RcppHoney::hooks::extract_dims(rhs);
    return RcppHoney::make_cbinder< RcppHoney::hook< U >::NA >()(
        RcppHoney::make_scalar_operator()(lhs, dims.first),
        rhs);
}
template< typename T, typename U >
typename RcppHoney::traits::enable_if<
    RcppHoney::traits::is_primitive< U >::value
    && RcppHoney::hook< T >::value,
    RcppHoney::cbinder<
        typename RcppHoney::hook< T >::const_iterator,
        typename RcppHoney::scalar_operator< U >::const_iterator,
        RcppHoney::hook< T >::NA
    >
>::type
cbind(const T &lhs, const U &rhs) {
    dims_t dims = RcppHoney::hooks::extract_dims(lhs);
    return RcppHoney::make_cbinder< RcppHoney::hook< T >::NA >()(
        lhs,
        RcppHoney::make_scalar_operator()(rhs, dims.first));
}
    
} // namespace RcppHoney
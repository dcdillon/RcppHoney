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

#include <cmath>
#include "traits/widest_numeric_type.hpp"
#include "traits/ctype.hpp"
#include "na.hpp"
#include "exceptions.hpp"

namespace RcppHoney {
namespace functors {
    
struct unary_result_dims
{
    inline dims_t result_dims(const dims_t &rhs) const {
        return rhs;
    }
};

struct binary_result_dims
{
    inline dims_t result_dims(const dims_t &lhs, const dims_t &rhs) const {
        if (lhs.first == -1) {
            return rhs;
        }
        else if (rhs.first == -1) {
            return lhs;
        }
        else if (lhs == rhs) {
            return lhs;
        } else {
            throw bounds_exception();
        }
    }
};
    
template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct plus : public binary_result_dims {
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    typedef typename traits::widest_numeric_type<
        lhs_value_type,
        rhs_value_type
    >::type return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return *lhs + *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs + *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct minus : public binary_result_dims {
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    typedef typename traits::widest_numeric_type<
        lhs_value_type,
        rhs_value_type
    >::type return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return *lhs - *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs - *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct times : public binary_result_dims {
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    typedef typename traits::widest_numeric_type<
        lhs_value_type,
        rhs_value_type
    >::type return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return *lhs * *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs * *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct divided_by : public binary_result_dims {
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    typedef typename traits::widest_numeric_type<
        lhs_value_type,
        rhs_value_type
    >::type return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return *lhs / *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs / *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA >
struct greater : public binary_result_dims {
    typedef int return_type;
    
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return *lhs > *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs > *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA >
struct greater_equal : public binary_result_dims {
    typedef int return_type;
    
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return *lhs >= *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs >= *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA >
struct less : public binary_result_dims {
    typedef int return_type;
    
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return *lhs < *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs < *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA >
struct less_equal : public binary_result_dims {
    typedef int return_type;
    
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return *lhs <= *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs <= *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA >
struct equal : public binary_result_dims {
    typedef int return_type;
    
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return *lhs == *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs == *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA >
struct not_equal : public binary_result_dims {
    typedef int return_type;
    
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return *lhs != *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs != *rhs;
        }
    }
};

template< typename RhsIterator, bool NA = true >
struct unary_minus : public unary_result_dims {
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type return_type;
    
    inline return_type operator()(RhsIterator &rhs) const {
        if (NA) {
            if (!is_na(*rhs)) {
                return -(*rhs);
            }

            return na< return_type >::VALUE();
        } else {
            return -(*rhs);
        }
    }
};

template< typename RhsIterator, bool NA = true >
struct unary_not : public unary_result_dims {
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type return_type;
    
    inline return_type operator()(RhsIterator &rhs) const {
        if (NA) {
            if (!is_na(*rhs)) {
                return !(*rhs);
            }

            return na< return_type >::VALUE();
        } else {
            return !(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct exp : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::exp(*rhs);
            }
        } else {
            return std::exp(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct log : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::log(*rhs);
            }
        } else {
            return std::log(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct sqrt : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::sqrt(*rhs);
            }
        } else {
            return std::sqrt(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct acos : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::acos(*rhs);
            }
        } else {
            return std::acos(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct asin : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::asin(*rhs);
            }
        } else {
            return std::asin(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct atan : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::atan(*rhs);
            }
        } else {
            return std::atan(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct ceil : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::ceil(*rhs);
            }
        } else {
            return std::ceil(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct cos : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::cos(*rhs);
            }
        } else {
            return std::cos(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct cosh : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::cosh(*rhs);
            }
        } else {
            return std::cosh(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct floor : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::floor(*rhs);
            }
        } else {
            return std::floor(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct log10 : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::log10(*rhs);
            }
        } else {
            return std::log10(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct sin : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::sin(*rhs);
            }
        } else {
            return std::sin(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct sinh : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::sinh(*rhs);
            }
        } else {
            return std::sinh(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct tan : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::tan(*rhs);
            }
        } else {
            return std::tan(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct tanh : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::tanh(*rhs);
            }
        } else {
            return std::tanh(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct abs : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::abs(*rhs);
            }
        } else {
            return std::abs(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct gamma : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return ::Rf_gammafn(*rhs);
            }
        } else {
            return ::Rf_gammafn(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct lgamma : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return ::Rf_lgammafn(*rhs);
            }
        } else {
            return ::Rf_lgammafn(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct digamma : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return ::Rf_digamma(*rhs);
            }
        } else {
            return ::Rf_digamma(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct trigamma : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return ::Rf_trigamma(*rhs);
            }
        } else {
            return ::Rf_trigamma(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct tetragamma : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return ::Rf_tetragamma(*rhs);
            }
        } else {
            return ::Rf_tetragamma(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct pentagamma : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return ::Rf_pentagamma(*rhs);
            }
        } else {
            return ::Rf_pentagamma(*rhs);
        }
    }
};

#if __cplusplus >= 201103L

template< typename Iterator, bool NA >
struct expm1 : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::expm1(*rhs);
            }
        } else {
            return std::expm1(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct log1p : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return std::log1p(*rhs);
            }
        } else {
            return std::log1p(*rhs);
        }
    }
};

#endif

template< typename Iterator, bool NA >
struct factorial : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return ::Rf_gammafn(*rhs + 1.0);
            }
        } else {
            return ::Rf_gammafn(*rhs + 1.0);
        }
    }
};

template< typename Iterator, bool NA >
struct lfactorial : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return ::Rf_lgammafn(*rhs + 1.0);
            }
        } else {
            return ::Rf_lgammafn(*rhs + 1.0);
        }
    }
};

template< typename Iterator, bool NA >
struct trunc : public unary_result_dims {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return ::Rf_ftrunc(*rhs);
            }
        } else {
            return ::Rf_ftrunc(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct diff {
    typedef typename std::iterator_traits< Iterator >::value_type return_type;

    return_type operator()(Iterator &current) const {
        Iterator prev = current;
        --prev;

        if (m_previousIterator != prev) {
            m_previousIterator = prev;
            m_previousValue = *m_previousIterator;
        }

        if (NA) {
            if (either_na(*current, m_previousValue)) {
                return na< return_type >::VALUE();
            } else {
                const return_type retval = *current - m_previousValue;
                m_previousIterator = current;
                m_previousValue = *current;
                return retval;
            }
        } else {
            const return_type retval = *current - m_previousValue;
            m_previousIterator = current;
            m_previousValue = *current;
            return retval;
        }
    }
    
    inline dims_t result_dims(const dims_t &rhs) const {
        return dims_t(rhs.first - 1, rhs.second);
    }

private:
    mutable Iterator m_previousIterator;
    mutable return_type m_previousValue;
};


template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct pow : public binary_result_dims {
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    typedef double return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return std::pow(*lhs, *rhs);
            }

            return na< return_type >::VALUE();
        } else {
            return std::pow(*lhs, *rhs);
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct choose : public binary_result_dims {
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    typedef double return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return ::Rf_choose(*lhs, *rhs);
            }

            return na< return_type >::VALUE();
        } else {
            return ::Rf_choose(*lhs, *rhs);
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct lchoose : public binary_result_dims {
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    typedef double return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return ::Rf_lchoose(*lhs, *rhs);
            }

            return na< return_type >::VALUE();
        } else {
            return ::Rf_lchoose(*lhs, *rhs);
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct beta : public binary_result_dims {
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    typedef double return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return ::Rf_beta(*lhs, *rhs);
            }

            return na< return_type >::VALUE();
        } else {
            return ::Rf_beta(*lhs, *rhs);
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct lbeta : public binary_result_dims {
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    typedef double return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return ::Rf_lbeta(*lhs, *rhs);
            }

            return na< return_type >::VALUE();
        } else {
            return ::Rf_lbeta(*lhs, *rhs);
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct psigamma : public binary_result_dims {
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    typedef double return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return ::Rf_psigamma(*lhs, *rhs);
            }

            return na< return_type >::VALUE();
        } else {
            return ::Rf_psigamma(*lhs, *rhs);
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct round : public binary_result_dims {
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    typedef double return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return ::Rf_fround(*lhs, *rhs);
            }

            return na< return_type >::VALUE();
        } else {
            return ::Rf_fround(*lhs, *rhs);
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct signif : public binary_result_dims {
    typedef typename std::iterator_traits<
        LhsIterator
    >::value_type lhs_value_type;
    
    typedef typename std::iterator_traits<
        RhsIterator
    >::value_type rhs_value_type;
    
    typedef double return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!either_na(*lhs, *rhs)) {
                return ::Rf_fprec(*lhs, *rhs);
            }

            return na< return_type >::VALUE();
        } else {
            return ::Rf_fprec(*lhs, *rhs);
        }
    }
};

} // namespace functors
} // namespace RcppHoney

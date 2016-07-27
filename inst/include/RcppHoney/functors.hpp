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
#include <cmath>
#include "traits/widest_numeric_type.hpp"
#include "traits/ctype.hpp"
#include "na.hpp"

namespace RcppHoney {
namespace functors {
template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct plus {
    typedef typename std::iterator_traits< LhsIterator >::value_type lhs_value_type;
    typedef typename std::iterator_traits< RhsIterator >::value_type rhs_value_type;
    typedef typename traits::widest_numeric_type< lhs_value_type, rhs_value_type >::type return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!na< typename traits::ctype< lhs_value_type >::type >::is_na(*lhs)
                && !na< typename traits::ctype< rhs_value_type >::type >::is_na(*rhs)) {
                return *lhs + *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs + *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct minus {
    typedef typename std::iterator_traits< LhsIterator >::value_type lhs_value_type;
    typedef typename std::iterator_traits< RhsIterator >::value_type rhs_value_type;
    typedef typename traits::widest_numeric_type< lhs_value_type, rhs_value_type >::type return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!na< typename traits::ctype< lhs_value_type >::type >::is_na(*lhs)
                && !na< typename traits::ctype< rhs_value_type >::type >::is_na(*rhs)) {
                return *lhs - *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs - *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct times {
    typedef typename std::iterator_traits< LhsIterator >::value_type lhs_value_type;
    typedef typename std::iterator_traits< RhsIterator >::value_type rhs_value_type;
    typedef typename traits::widest_numeric_type< lhs_value_type, rhs_value_type >::type return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!na< typename traits::ctype< lhs_value_type >::type >::is_na(*lhs)
                && !na< typename traits::ctype< rhs_value_type >::type >::is_na(*rhs)) {
                return *lhs * *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs * *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct divided_by {
    typedef typename std::iterator_traits< LhsIterator >::value_type lhs_value_type;
    typedef typename std::iterator_traits< RhsIterator >::value_type rhs_value_type;
    typedef typename traits::widest_numeric_type< lhs_value_type, rhs_value_type >::type return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!na< typename traits::ctype< lhs_value_type >::type >::is_na(*lhs)
                && !na< typename traits::ctype< rhs_value_type >::type >::is_na(*rhs)) {
                return *lhs / *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs / *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA >
struct greater {
    typedef int return_type;
    typedef typename std::iterator_traits< LhsIterator >::value_type lhs_value_type;
    typedef typename std::iterator_traits< RhsIterator >::value_type rhs_value_type;
    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!na< typename traits::ctype< lhs_value_type >::type >::is_na(*lhs)
                && !na< typename traits::ctype< rhs_value_type >::type >::is_na(*rhs)) {

                return *lhs > *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs > *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA >
struct greater_equal {
    typedef int return_type;
    typedef typename std::iterator_traits< LhsIterator >::value_type lhs_value_type;
    typedef typename std::iterator_traits< RhsIterator >::value_type rhs_value_type;
    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!na< typename traits::ctype< lhs_value_type >::type >::is_na(*lhs)
                && !na< typename traits::ctype< rhs_value_type >::type >::is_na(*rhs)) {

                return *lhs >= *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs >= *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA >
struct less {
    typedef int return_type;
    typedef typename std::iterator_traits< LhsIterator >::value_type lhs_value_type;
    typedef typename std::iterator_traits< RhsIterator >::value_type rhs_value_type;
    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!na< typename traits::ctype< lhs_value_type >::type >::is_na(*lhs)
                && !na< typename traits::ctype< rhs_value_type >::type >::is_na(*rhs)) {

                return *lhs < *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs < *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA >
struct less_equal {
    typedef int return_type;
    typedef typename std::iterator_traits< LhsIterator >::value_type lhs_value_type;
    typedef typename std::iterator_traits< RhsIterator >::value_type rhs_value_type;
    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!na< typename traits::ctype< lhs_value_type >::type >::is_na(*lhs)
                && !na< typename traits::ctype< rhs_value_type >::type >::is_na(*rhs)) {

                return *lhs <= *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs <= *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA >
struct equal {
    typedef int return_type;
    typedef typename std::iterator_traits< LhsIterator >::value_type lhs_value_type;
    typedef typename std::iterator_traits< RhsIterator >::value_type rhs_value_type;
    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!na< typename traits::ctype< lhs_value_type >::type >::is_na(*lhs)
                && !na< typename traits::ctype< rhs_value_type >::type >::is_na(*rhs)) {

                return *lhs == *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs == *rhs;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA >
struct not_equal {
    typedef int return_type;
    typedef typename std::iterator_traits< LhsIterator >::value_type lhs_value_type;
    typedef typename std::iterator_traits< RhsIterator >::value_type rhs_value_type;
    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!na< typename traits::ctype< lhs_value_type >::type >::is_na(*lhs)
                && !na< typename traits::ctype< rhs_value_type >::type >::is_na(*rhs)) {

                return *lhs != *rhs;
            }

            return na< return_type >::VALUE();
        } else {
            return *lhs != *rhs;
        }
    }
};

template< typename RhsIterator, bool NA = true >
struct unary_minus {
    typedef typename std::iterator_traits< RhsIterator >::value_type return_type;
    inline return_type operator()(RhsIterator &rhs) const {
        if (NA) {
            if (!na< typename traits::ctype< return_type >::type >::is_na(*rhs)) {
                return -(*rhs);
            }

            return na< return_type >::VALUE();
        } else {
            return -(*rhs);
        }
    }
};

template< typename RhsIterator, bool NA = true >
struct unary_not {
    typedef typename std::iterator_traits< RhsIterator >::value_type return_type;
    inline return_type operator()(RhsIterator &rhs) const {
        if (NA) {
            if (!na< typename traits::ctype< return_type >::type >::is_na(*rhs)) {
                return !(*rhs);
            }

            return na< return_type >::VALUE();
        } else {
            return !(*rhs);
        }
    }
};

template< typename Iterator, bool NA >
struct exp {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct log {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct sqrt {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct acos {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct asin {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct atan {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct ceil {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct cos {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct cosh {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct floor {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct log10 {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct sin {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct sinh {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct tan {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct tanh {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct abs {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct gamma {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct lgamma {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct digamma {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct trigamma {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct tetragamma {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct pentagamma {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct expm1 {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct log1p {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct factorial {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct lfactorial {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
struct trunc {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
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
            if (na< typename traits::ctype< return_type >::type >::is_na(*current)
                || na< typename traits::ctype< return_type >::type >::is_na(m_previousValue)) {
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

private:
    mutable Iterator m_previousIterator;
    mutable return_type m_previousValue;
};

} // namespace functors
} // namespace RcppHoney

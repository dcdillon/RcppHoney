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
                return ::exp(*rhs);
            }
        } else {
            return ::exp(*rhs);
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
                return ::log(*rhs);
            }
        } else {
            return ::log(*rhs);
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
                return ::sqrt(*rhs);
            }
        } else {
            return ::sqrt(*rhs);
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
                return ::acos(*rhs);
            }
        } else {
            return ::acos(*rhs);
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
                return ::asin(*rhs);
            }
        } else {
            return ::asin(*rhs);
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
                return ::atan(*rhs);
            }
        } else {
            return ::atan(*rhs);
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
                return ::ceil(*rhs);
            }
        } else {
            return ::ceil(*rhs);
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
                return ::cos(*rhs);
            }
        } else {
            return ::cos(*rhs);
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
                return ::cosh(*rhs);
            }
        } else {
            return ::cosh(*rhs);
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
                return ::floor(*rhs);
            }
        } else {
            return ::floor(*rhs);
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
                return ::log10(*rhs);
            }
        } else {
            return ::log10(*rhs);
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
                return ::sin(*rhs);
            }
        } else {
            return ::sin(*rhs);
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
                return ::sinh(*rhs);
            }
        } else {
            return ::sinh(*rhs);
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
                return ::tan(*rhs);
            }
        } else {
            return ::tan(*rhs);
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
                return ::tanh(*rhs);
            }
        } else {
            return ::tanh(*rhs);
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
                return ::fabs(*rhs);
            }
        } else {
            return ::fabs(*rhs);
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

template< typename Iterator, bool NA >
struct expm1 {
    typedef double return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return ::expm1(*rhs);
            }
        } else {
            return ::expm1(*rhs);
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
                return ::log1p(*rhs);
            }
        } else {
            return ::log1p(*rhs);
        }
    }
};

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

} // namespace functors
} // namespace RcppHoney

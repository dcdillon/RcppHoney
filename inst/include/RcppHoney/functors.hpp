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

} // namespace functors
} // namespace RcppHoney

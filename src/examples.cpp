#include <RcppHoneyForward.hpp>
#include <vector>

// We have to declare our hooks before we include RcppHoney.hpp

namespace RcppHoney {
namespace hooks {

// define any user hooks here as follows
template< typename T, typename A >
traits::true_type is_hooked(const std::list< T, A > &val);

// set NA to true
template< typename T, typename A >
traits::true_type has_na(const std::list< T, A > &val);

// assert that we need to create basic operators
template< typename T, typename A >
RcppHoney::traits::true_type needs_basic_operators(const std::list< T, A > &val);

// assert that we need to create type + scalar operators
template< typename T, typename A >
RcppHoney::traits::true_type needs_scalar_operators(const std::list< T, A > &val);

// give this a family identifier (has to be unique and has to be > FAMILY_USER)
template< typename T, typename A >
RcppHoney::traits::int_constant< FAMILY_USER + 1 > family(const std::list< T, A > &val);

} // namespace hooks
} // namespace RcppHoney

#include <RcppHoney.hpp>

// Let's also add a couple custom honey functions
namespace RcppHoney {

// first define functors for them in the RcppHoney::functors namespace
namespace functors {

template< typename Iterator, bool NA >
struct my_unary_functor {
    typedef typename std::iterator_traits< Iterator >::value_type rhs_value_type;
    // since we're just adding a double to the input value the return type should be
    // the widest numeric type of rhs and double
    typedef typename traits::widest_numeric_type< rhs_value_type, double >::type return_type;
    return_type operator()(Iterator &rhs) const {
        if (NA) {
            if (na< typename traits::ctype< typename std::iterator_traits< Iterator >::value_type >::type >::is_na(*rhs)) {
                return na< return_type >::VALUE();
            } else {
                return *rhs + 1.0;
            }
        } else {
            return *rhs + 1.0;
        }
    }
};

template< typename LhsIterator, typename RhsIterator, bool NA = true >
struct my_binary_functor {
    typedef typename std::iterator_traits< LhsIterator >::value_type lhs_value_type;
    typedef typename std::iterator_traits< RhsIterator >::value_type rhs_value_type;

    // since we're just adding a double to the sum of the two inputs, the return type
    // should be the widest numeric type of lhs, rhs, and double
    typedef typename traits::widest_numeric_type<
        double,
        typename traits::widest_numeric_type< lhs_value_type, rhs_value_type >::type
    >::type return_type;

    inline return_type operator()(LhsIterator &lhs, RhsIterator &rhs) const {
        if (NA) {
            if (!na< typename traits::ctype< lhs_value_type >::type >::is_na(*lhs)
                    && !na< typename traits::ctype< rhs_value_type >::type >::is_na(*rhs)) {
                return *lhs + *rhs + 2.0;
            }

            return na< return_type >::VALUE();
        } else {
            return ::Rf_fprec(*lhs, *rhs);
        }
    }
};

} // namespace functors

// now we define the functions in th RcppHoney namespace
RCPP_HONEY_GENERATE_UNARY_FUNCTION(my_unary_function, my_unary_functor)
RCPP_HONEY_GENERATE_BINARY_FUNCTION(my_binary_function, my_binary_functor)

} // namespace RcppHoney

// [[Rcpp::export]]
Rcpp::NumericVector example_manually_hooked() {

    // we manually hooked std::list in to RcppHoney so we'll create one
    std::list< int > l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);

    // std::vector is already hooked in to RcppHoney in default_hooks.hpp so we'll
    // create one of those too
    std::vector< int > v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    // and for good measure, let's create an Rcpp::NumericVector which is also hooked by default
    Rcpp::NumericVector v2(v.begin(), v.end());

    // now do some weird operations incorporating both std::vector and std::list and some
    // RcppHoney functions, and our custom functions and return it.
    RcppHoney::NumericVector retval
        =  42 + RcppHoney::my_binary_function(v, l) + l + v + RcppHoney::log(v) - v - l
            + RcppHoney::sqrt(v) + -v2 + RcppHoney::my_unary_function(v) + 42;
    return retval;
}

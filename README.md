# RcppHoney [![Build Status](https://travis-ci.org/dcdillon/RcppHoney.svg?branch=master)](https://travis-ci.org/dcdillon/RcppHoney) [![License](http://img.shields.io/badge/license-GPL%20%28%3E=%202%29-brightgreen.svg?style=flat)](http://www.gnu.org/licenses/gpl-2.0.html) [![CRAN](http://www.r-pkg.org/badges/version/RcppHoney)](http://cran.r-project.org/package=RcppHoney) [![Downloads](http://cranlogs.r-pkg.org/badges/RcppHoney?color=brightgreen)](http://www.r-pkg.org/pkg/RcppHoney)

### Description

`RcppHoney` provides functions and operators with R semantics for any container type that has a `const_iterator`.  All operators and functions are implemented as expression templates to minimize temporary copies of containers.  It is integrated with `Rcpp::wrap` functionality so that results can easily be exported to `R`.

The goal is to provide full featured interoperability between any iterator based structures and `R` to reduce development time and simplify code.

`RcppHoney` is now in a beta state so the API should no longer be changing.

### Example

```c++
// [[Rcpp::plugins(cpp11)]]

// Tell Rcpp that we need RcppHoney

// [[Rcpp::depends(RcppHoney)]]

#include <RcppHoneyForward.hpp> // we have to do this because we're going to hook in a non-default structure
#include <list>

// We have to declare our hooks before we include RcppHoney.hpp
namespace RcppHoney {
namespace hooks {

// Hook in all std::list types (could be more specific)
template< typename T, typename A >
traits::true_type is_hooked(const std::list< T, A > &val);

// Tell RcppHoney that NA has meaning in std::list
template< typename T, typename A >
traits::true_type has_na(const std::list< T, A > &val);

// Tell RcppHoney that it needs to create basic (e.g. std::list + std::list) operators
template< typename T, typename A >
traits::true_type needs_basic_operators(const std::list< T, A > &val);

// Tell RcppHoney that it needs to create scalar (e.g. std::list + int/double) operators
template< typename T, typename A >
traits::true_type needs_scalar_operators(const std::list< T, A > &val);

// Tell RcppHoney that this set of types is part of the FAMILY_USER + 1 family.
// This is used in conjunction with needs_basic_operators.  If you have
// needs_basic_operators return RcppHoney::traits::false_type, then only types
// that are not part of the same family will have binary operators created
// between them.
template< typename T, typename A >
traits::int_constant< FAMILY_USER + 1 > family(const std::list< T, A > &val);

} // namespace hooks
} // namespace RcppHoney

#include <RcppHoney.hpp>

// Let's also add a couple custom honey functions
namespace RcppHoney {

// first define functors for them in the RcppHoney::functors namespace
namespace functors {

template< typename Iterator, bool NA >
struct my_unary_functor : public unary_result_dims {
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
struct my_binary_functor : binary_result_dims {
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
Rcpp::NumericVector rcpphoney_example() {

    // We manually hooked std::list in to RcppHoney so we'll create one
    std::list< int > l {1, 2, 3, 4, 5}; // c++11 for brevity here, but not required for RcppHoney

    // std::vector is already hooked in to RcppHoney in default_hooks.hpp so we'll
    // create one of those too
    std::vector< int > v {1, 2, 3, 4, 5}; // c++11 for brevity here, but not required for RcppHoney

    // And for good measure, let's create an Rcpp::NumericVector which is also hooked by default
    Rcpp::NumericVector v2(v.begin(), v.end());

    // Now do some weird operations incorporating std::vector, std::list, Rcpp::NumericVector
    // and some RcppHoney functions and return it.  The return value will be equal to the following
    // R snippet:
    //     v <- 1:5
    //     result <- v + v + log(v) - v - v + sqrt(v) + -v + (v + 1.0) + (v + v + 2.0)
    
    // We can store our result in any of RcppHoney::LogicalVector, RcppHoney::IntegerVector, or
    // RcppHoney::NumericVector and simply return it to R.  These classes inherit from their
    // Rcpp counterparts and add a new constructor.  The only copy of the data, in this case, is when
    // we assign our expression to retval.  Since it is then a "native" R type, returning it is a
    // shallow copy.  Alternatively we could write this as:
    //     return Rcpp::wrap(l + v + RcppHoney::log(v) - v - l + RcppHoney::sqrt(v) + -v2
    //         + RcppHoney::my_unary_function(l) + RcppHoney::my_binary_function(l, v);
    
    RcppHoney::NumericVector retval
        =  l + v + RcppHoney::log(v) - v - l + RcppHoney::sqrt(v) + -v2
            + RcppHoney::my_unary_function(l) + RcppHoney::my_binary_function(l, v);
    return retval;
}
```

### Installation

RcppHoney is now a in beta state!

RcppHoney is available via the [CRAN](http://cran.r-project.org) network,
and can be installed from within R via 

```R
install.packages("RcppHoney")
```

RcppHoney can also be installed from the github sources by running

```
git clone git@github.com:dcdillon/RcppHoney
R CMD INSTALL RcppHoney
```

### Authors

Daniel C. Dillon

### License

GPL (>= 2)

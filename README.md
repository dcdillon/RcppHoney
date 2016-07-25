# RcppHoney

### Description

`RcppHoney` provides functions and operators with R semantics for any container type that has a `const_iterator`.  All operators and functions are implemented as expression templates to minimize temporary copies of containers.  It is integrated with `Rcpp::wrap` functionality so that results can easily be exported to `R`.

The goal is to provide full featured interoperability between any iterator based structures and `R` to reduce development time and simplify code.

`RcppHoney` is in alpha state (so the API is still subject to change, but is way more stable than it was a week ago).

### Example

```c++
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
RcppHoney::traits::true_type needs_basic_operators(const std::list< T, A > &val);

// Tell RcppHoney that it needs to create scalar (e.g. std::list + int/double) operators
template< typename T, typename A >
RcppHoney::traits::true_type needs_scalar_operators(const std::list< T, A > &val);

// Tell RcppHoney that this set of types is part of the FAMILY_USER + 1 family.
// This is used in conjunction with needs_basic_operators.  If you have
// needs_basic_operators return RcppHoney::traits::false_type, then only types
// that are not part of the same family will have binary operators created
// between them.
template< typename T, typename A >
RcppHoney::traits::int_constant< FAMILY_USER + 1 > family(const std::list< T, A > &val);

} // namespace hooks
} // namespace RcppHoney

#include <RcppHoney.hpp>

// [[Rcpp::export]]
Rcpp::NumericVector example_manually_hooked() {

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
    //     result <- 1 + v + log(v) - v - 1 + sqrt(v) + -v
    
    // We can store our result in any of RcppHoney::LogicalVector, RcppHoney::IntegerVector, or
    // RcppHoney::NumericVector and simply return it to R.  These classes simply inherit from their
    // Rcpp counterparts and add a new constructor.  The only copy of the data, in this case, is when
    // we assign our expression to retval.  Since it is then a "native" R type, returning it is a
    // shallow copy.
    RcppHoney::NumericVector retval
        =  l + v + RcppHoney::log(v) - v - l + RcppHoney::sqrt(v) + -v2;
    return retval;
}
```

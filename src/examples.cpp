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
    // RcppHoney functions and return it.
    RcppHoney::NumericVector retval
        =  42 + l + v + RcppHoney::log(v) - v - l + RcppHoney::sqrt(v) + -v2 + 42;
    return retval;
}

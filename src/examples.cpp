#include <Rcpp.h>
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

// give this a family identifier
template< typename T, typename A >
RcppHoney::traits::int_constant< FAMILY_USER + 1 > family(const std::list< T, A > &val);

} // namespace hooks
} // namespace RcppHoney

#include <RcppHoney.hpp>

// [[Rcpp::export]]
Rcpp::NumericVector test_binary_operators(std::vector< int > v, std::vector< double > v2,
                                          Rcpp::IntegerVector v3, Rcpp::NumericVector v4) {

    // we're assuming that all input parameters are vectors of length 5
    std::set< int > s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);

    std::list< int > l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);

    /*return Rcpp::wrap(
        (1 + v)     // scalar + std::vector< int >
        + (v + 1)   // std::vector< int > + scalar
        + (v + v2)  // std::vector< int > + std::vector< double >
        + (v2 + v)  // std::vector< double > + std::vector< int >
        + (v + v3)  // std::vector< int > + IntegerVector
        + (v3 + v)
        + (v + v4)
        + (v4 + v)
        + (v + s)
        + (s + v)
        + (v + l)
        + (l + v)
    );*/

    RcppHoney::NumericVector retval = RcppHoney::diff(1 + l + 1 + s + (RcppHoney::log(v3) + v3)
        + RcppHoney::abs((RcppHoney::exp(v3) + v4)) + RcppHoney::log(v) + v2 + 1 + RcppHoney::sqrt(v) + 2);

    return retval;
}

// [[Rcpp::export]]
Rcpp::NumericVector test_unary_operators(std::vector< int > v) {
    return Rcpp::wrap(-v + v);
}

// [[Rcpp::export]]
Rcpp::NumericVector test_unary_functions(std::vector< int > v) {
    return Rcpp::wrap(RcppHoney::sqrt(RcppHoney::log(v) + RcppHoney::exp(v)));
}

// [[Rcpp::export]]
Rcpp::IntegerVector test_diff_function(std::vector< int > v) {
    return Rcpp::wrap(RcppHoney::diff(v));
}

// [[Rcpp::export]]
Rcpp::IntegerVector test_sugar_diff_function(Rcpp::IntegerVector v) {
    return Rcpp::diff(v);
}

// [[Rcpp::export]]
Rcpp::IntegerVector test_naive_diff_function(std::vector< int > v) {
    std::vector< int > x;
    x.reserve(v.size());

    std::vector< int >::iterator i = v.begin() + 1;

    for ( ; i != v.end(); ++i)
    {
        x.push_back(*i - (*(i - 1)));
    }

    return Rcpp::wrap(x);
}

// [[Rcpp::export]]
Rcpp::IntegerVector test_diff_function2() {
    std::vector< int > v(100000, 1);
    return Rcpp::wrap(RcppHoney::diff(v));
}

// [[Rcpp::export]]
Rcpp::IntegerVector test_sugar_diff_function2() {
    Rcpp::IntegerVector v(100000, 1);
    return Rcpp::diff(v);
}

// [[Rcpp::export]]
Rcpp::IntegerVector test_naive_diff_function2() {
    std::vector< int > v(100000, 1);
    std::vector< int > x;
    x.reserve(v.size());

    std::vector< int >::iterator i = v.begin() + 1;

    for ( ; i != v.end(); ++i)
    {
        x.push_back(*i - (*(i - 1)));
    }

    return Rcpp::wrap(x);
}

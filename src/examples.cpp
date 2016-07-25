#include <Rcpp.h>
#include <RcppHoneyForward.hpp>
#include <vector>

// We have to declare our hooks before we include RcppHoney.hpp

namespace RcppHoney {
namespace hooks {

// hooks for std::vector
template< typename T, typename A>
RcppHoney::traits::true_type is_hooked(const std::vector< T, A > &val);

// hooks for Rcpp::VectorBase
template< int RTYPE, bool NA, typename T >
RcppHoney::traits::true_type is_hooked(const Rcpp::VectorBase< RTYPE, NA, T > &val);

// return the appropriate NA value
template< int RTYPE, typename T >
RcppHoney::traits::false_type has_na(const Rcpp::VectorBase< RTYPE, false, T > &val);

template< int RTYPE, typename T >
RcppHoney::traits::true_type has_na(const Rcpp::VectorBase< RTYPE, true, T > &val);

// assert that we need to create basic operators
template< int RTYPE, bool NA, typename T >
RcppHoney::traits::true_type needs_basic_operators(const Rcpp::VectorBase< RTYPE, NA, T > &val);

template< int RTYPE, bool NA, typename T >
RcppHoney::traits::true_type needs_scalar_operators(const Rcpp::VectorBase< RTYPE, NA, T > &val);

template< int RTYPE, bool NA, typename T >
RcppHoney::traits::int_constant< 2 > family(const Rcpp::VectorBase< RTYPE, NA, T > &val);

} // namespace hooks
} // namespace RcppHoney

#include <RcppHoney.hpp>

// [[Rcpp::export]]
void test_hook() {
    Rcpp::Rcout << RcppHoney::hook< Rcpp::NumericVector >::FAMILY << std::endl;
    Rcpp::Rcout << sizeof(RcppHoney::hooks::is_hooked(RcppHoney::hooks::create_type< Rcpp::NumericVector >())) << std::endl;
    if (RcppHoney::hook< Rcpp::NumericVector >::value) {
        Rcpp::Rcout << "that works" << std::endl;
    }
}

// [[Rcpp::export]]
Rcpp::NumericVector test_binary_operators(std::vector< int > v, std::vector< double > v2,
                                          Rcpp::IntegerVector v3, Rcpp::NumericVector v4) {
    return Rcpp::wrap(1 + (RcppHoney::log(v3) + v3) + RcppHoney::abs((RcppHoney::exp(v3) + v4))
                          + RcppHoney::log(v) + v2 + 1 + RcppHoney::sqrt(v) + 2);
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

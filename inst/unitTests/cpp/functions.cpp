// [[Rcpp::depends(RcppHoney)]]

#include <RcppHoney.hpp>

// TEST FUNCTION PARAMETER TYPES

// [[Rcpp::export]]
Rcpp::NumericVector test_unary_function_hooked(std::vector< int > v) {
    return Rcpp::wrap(RcppHoney::log(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_unary_function_operand(std::vector< int > v) {
    return Rcpp::wrap(RcppHoney::log(v + v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_binary_function_hooked_scalar(std::vector< int > v1, double s) {
    return Rcpp::wrap(RcppHoney::pow(v1, s));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_binary_function_scalar_hooked(double s, std::vector< int > v1) {
    return Rcpp::wrap(RcppHoney::pow(s, v1));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_binary_function_hooked_hooked(std::vector< int > v1, std::vector< int > v2) {
    return Rcpp::wrap(RcppHoney::pow(v1, v2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_binary_function_hooked_other_hooked(std::vector< int > v1, Rcpp::NumericVector v2) {
    return Rcpp::wrap(RcppHoney::pow(v1, v2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_binary_function_other_hooked_hooked(Rcpp::NumericVector v1, std::vector< int > v2) {
    return Rcpp::wrap(RcppHoney::pow(v1, v2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_binary_function_operand_scalar(std::vector< int > v1, std::vector< int > v2, double s) {
    return Rcpp::wrap(RcppHoney::pow(v1 + v2, s));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_binary_function_scalar_operand(double s, std::vector< int > v1, std::vector< int > v2) {
    return Rcpp::wrap(RcppHoney::pow(s, v1 + v2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_binary_function_operand_hooked(std::vector< int > v1, std::vector< int > v2, Rcpp::NumericVector v3) {
    return Rcpp::wrap(RcppHoney::pow(v1 + v2, v3));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_binary_function_hooked_operand(Rcpp::NumericVector v1, std::vector< int > v2, std::vector< int > v3) {
    return Rcpp::wrap(RcppHoney::pow(v1, v2 + v3));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_binary_function_operand_operand(std::vector< int > v1, std::vector< int > v2) {
    return Rcpp::wrap(RcppHoney::pow(v1 + v2, v2 + v2));
}





// TEST INDIVIDUAL FUNCTIONS

// [[Rcpp::export]]
Rcpp::NumericVector test_log(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::log(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_exp(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::exp(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_sqrt(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::sqrt(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_acos(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::acos(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_asin(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::asin(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_atan(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::atan(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_ceil(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::ceil(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_cos(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::cos(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_cosh(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::cosh(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_floor(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::floor(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_log10(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::log10(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_sin(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::sin(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_sinh(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::sinh(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_tan(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::tan(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_tanh(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::tanh(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_abs(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::abs(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_gamma(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::gamma(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_lgamma(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::lgamma(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_digamma(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::digamma(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_trigamma(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::trigamma(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_tetragamma(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::tetragamma(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_pentagamma(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::pentagamma(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_factorial(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::factorial(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_lfactorial(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::lfactorial(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_trunc(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::trunc(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_diff(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::diff(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_pow(Rcpp::NumericVector v1, Rcpp::NumericVector v2) {
    return Rcpp::wrap(RcppHoney::pow(v1, v2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_choose(Rcpp::NumericVector v1, Rcpp::NumericVector v2) {
    return Rcpp::wrap(RcppHoney::choose(v1, v2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_lchoose(Rcpp::NumericVector v1, Rcpp::NumericVector v2) {
    return Rcpp::wrap(RcppHoney::lchoose(v1, v2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_beta(Rcpp::NumericVector v1, Rcpp::NumericVector v2) {
    return Rcpp::wrap(RcppHoney::beta(v1, v2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_lbeta(Rcpp::NumericVector v1, Rcpp::NumericVector v2) {
    return Rcpp::wrap(RcppHoney::lbeta(v1, v2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_psigamma(Rcpp::NumericVector v1, Rcpp::NumericVector v2) {
    return Rcpp::wrap(RcppHoney::psigamma(v1, v2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_round(Rcpp::NumericVector v1, Rcpp::NumericVector v2) {
    return Rcpp::wrap(RcppHoney::round(v1, v2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_signif(Rcpp::NumericVector v1, Rcpp::NumericVector v2) {
    return Rcpp::wrap(RcppHoney::signif(v1, v2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_cumsum(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::cumsum(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_cumsum_matrix(Rcpp::NumericMatrix m) {
    return Rcpp::wrap(RcppHoney::cumsum(m));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_cumsum_operand(Rcpp::NumericMatrix m) {
    return Rcpp::wrap(RcppHoney::cumsum(RcppHoney::log(m)));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_cumprod(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::cumprod(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_cumprod_matrix(Rcpp::NumericMatrix m) {
    return Rcpp::wrap(RcppHoney::cumprod(m));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_cumprod_operand(Rcpp::NumericMatrix m) {
    return Rcpp::wrap(RcppHoney::cumprod(RcppHoney::log(m)));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_cummin(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::cummin(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_cummin_matrix(Rcpp::NumericMatrix m) {
    return Rcpp::wrap(RcppHoney::cummin(m));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_cummin_operand(Rcpp::NumericMatrix m) {
    return Rcpp::wrap(RcppHoney::cummin(RcppHoney::log(m)));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_cummax(Rcpp::NumericVector v) {
    return Rcpp::wrap(RcppHoney::cummax(v));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_cummax_matrix(Rcpp::NumericMatrix m) {
    return Rcpp::wrap(RcppHoney::cummax(m));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_cummax_operand(Rcpp::NumericMatrix m) {
    return Rcpp::wrap(RcppHoney::cummax(RcppHoney::log(m)));
}

// [[Rcpp::export]]
Rcpp::NumericMatrix test_cbind_vector_scalar(std::vector< double > v,
    double s) {

    return Rcpp::wrap(RcppHoney::cbind(v, s));
}
// [[Rcpp::export]]
Rcpp::NumericMatrix test_cbind_scalar_vector(double s,
    std::vector< double > v) {

    return Rcpp::wrap(RcppHoney::cbind(s, v));
}

// [[Rcpp::export]]
Rcpp::NumericMatrix test_cbind_vector_vector(std::vector< double > v1,
    Rcpp::NumericVector v2) {

    return Rcpp::wrap(RcppHoney::cbind(v1, v2));
}

// [[Rcpp::export]]
Rcpp::NumericMatrix test_cbind_matrix_vector(Rcpp::NumericMatrix m,
    std::vector< double > v) {

    return Rcpp::wrap(RcppHoney::cbind(m, v));
}

// [[Rcpp::export]]
Rcpp::NumericMatrix test_cbind_vector_matrix(std::vector< double > v,
    Rcpp::NumericMatrix m) {

    return Rcpp::wrap(RcppHoney::cbind(v, m));
}

// [[Rcpp::export]]
Rcpp::NumericMatrix test_cbind_matrix_matrix(Rcpp::NumericMatrix m1,
    Rcpp::NumericMatrix m2) {

    return Rcpp::wrap(RcppHoney::cbind(m1, m2));
}
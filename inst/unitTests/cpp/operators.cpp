// [[Rcpp::depends(RcppHoney)]]

#include <RcppHoney.hpp>

// [[Rcpp::export]]
Rcpp::NumericVector test_hooked_plus_scalar(std::vector< int > v1, double s) {
    return Rcpp::wrap(v1 + s);
}

// [[Rcpp::export]]
Rcpp::NumericVector test_scalar_plus_hooked(double s, std::vector< int > v1) {
    return Rcpp::wrap(s + v1);
}

// [[Rcpp::export]]
Rcpp::NumericVector test_hooked_plus_hooked(std::vector< int > v1,
    std::vector< int > v2) {

    return Rcpp::wrap(v1 + v2);
}

// [[Rcpp::export]]
Rcpp::NumericVector test_hooked_plus_other_hooked(std::vector< int > v1,
    Rcpp::NumericVector v2) {

    return Rcpp::wrap(v1 + v2);
}

// [[Rcpp::export]]
Rcpp::NumericVector test_other_hooked_plus_hooked(Rcpp::NumericVector v1,
    std::vector< int > v2) {

    return Rcpp::wrap(v1 + v2);
}

// [[Rcpp::export]]
Rcpp::NumericVector test_operand_plus_scalar(std::vector< int > v1,
    std::vector< int > v2, double s) {

    return Rcpp::wrap((v1 + v2) + s);
}

// [[Rcpp::export]]
Rcpp::NumericVector test_scalar_plus_operand(double s, std::vector< int > v1,
    std::vector< int > v2) {

    return Rcpp::wrap(s + (v1 + v2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_operand_plus_hooked(std::vector< int > v1,
    std::vector< int > v2, Rcpp::NumericVector v3) {

    return Rcpp::wrap((v1 + v2) + v3);
}

// [[Rcpp::export]]
Rcpp::NumericVector test_hooked_plus_operand(Rcpp::NumericVector v1,
    std::vector< int > v2, std::vector< int > v3) {

    return Rcpp::wrap(v1 + (v2 + v3));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_operand_plus_operand(std::vector< int > v1,
    std::vector< int > v2) {

    return Rcpp::wrap((v1 + v2) + (v1 + v2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_unary_operator_hooked(std::vector< int > v) {
    return Rcpp::wrap(-v);
}

// [[Rcpp::export]]
Rcpp::NumericVector test_unary_operator_operand(std::vector< int > v) {
    return Rcpp::wrap(-(v + v));
}











// [[Rcpp::export]]
Rcpp::IntegerMatrix test_matrix_plus_scalar(Rcpp::IntegerMatrix m1, double s) {
    return Rcpp::wrap(m1 + s);
}

// [[Rcpp::export]]
Rcpp::IntegerMatrix test_scalar_plus_matrix(double s, Rcpp::IntegerMatrix m1) {
    return Rcpp::wrap(s + m1);
}

// [[Rcpp::export]]
Rcpp::NumericMatrix test_matrix_plus_matrix(Rcpp::NumericMatrix m1,
    Rcpp::NumericMatrix m2)
{
    return Rcpp::wrap(m1 + m2);
}

// [[Rcpp::export]]
Rcpp::NumericMatrix test_matrix_unary_operator(Rcpp::NumericMatrix m) {
    return Rcpp::wrap(-m);
}

// [[Rcpp::export]]
Rcpp::NumericMatrix test_matrix_unary_operator_operand(Rcpp::NumericMatrix m) {
    return Rcpp::wrap(-(m + m));
}
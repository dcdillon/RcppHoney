#include <RcppHoney.hpp>
#include <vector>


using namespace Rcpp;

// Create hooks for std::vector< int > and std::vector< double >

namespace RcppHoney {

template<>
class hook< std::vector< int > > : public std::vector< int > {
public:
    static const bool value = true;
    typedef std::vector< int >::const_iterator const_iterator;
    typedef std::vector< int >::iterator iterator;
    static const bool NA = true;

    template< typename T, typename T_ITER, typename T_RESULT >
    hook< std::vector< int > >(const operand< T, T_ITER, T_RESULT > &rhs) : std::vector< int >(rhs.begin(), rhs.end()) {}

    template< typename T, typename T_ITER, typename T_RESULT >
    hook< std::vector< int > > &operator=(const operand< T, T_ITER, T_RESULT > &rhs) {
        resize(rhs.end() - rhs.begin());

        iterator i = begin();
        T_ITER j = rhs.begin();

        for ( ; i != end() && j != rhs.end(); ++i, ++j) {
            *i = *j;
        }

        return *this;
    }
};

template<>
class hook< std::vector< double > > : public std::vector< double > {
public:
    static const bool value = true;
    typedef std::vector< double >::const_iterator const_iterator;
    typedef std::vector< double >::iterator iterator;
    static const bool NA = true;

    template< typename T, typename T_ITER, typename T_RESULT >
    hook< std::vector< double > >(const operand< T, T_ITER, T_RESULT > &rhs) : std::vector< double >(rhs.begin(), rhs.end()) {}

    template< typename T, typename T_ITER, typename T_RESULT >
    hook< std::vector< double > > &operator=(const operand< T, T_ITER, T_RESULT > &rhs) {
        resize(rhs.end() - rhs.begin());

        iterator i = begin();
        T_ITER j = rhs.begin();

        for ( ; i != end() && j != rhs.end(); ++i, ++j) {
            *i = *j;
        }

        return *this;
    }
};

} // namespace RcppHoney

// [[Rcpp::export]]
Rcpp::NumericVector test_binary_operators(std::vector< int > v, std::vector< double > v2) {
    return Rcpp::wrap(v + v2 + 1 + v + v + 2);
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
Rcpp::IntegerVector test_sugar_diff_function(IntegerVector v) {
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
    IntegerVector v(100000, 1);
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

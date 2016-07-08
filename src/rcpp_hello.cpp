#include <RcppHoney/operators.hpp>
#include <RcppHoney/functions.hpp>
#include <Rcpp.h>
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
std::vector< double > test_binary_operators(std::vector< int > v, std::vector< double > v2) {
    RcppHoney::hook< std::vector< double > > retval = v + v2 + 1 + v + v + 2;
    return retval;
}

// [[Rcpp::export]]
std::vector< int > test_unary_operators(std::vector< int > v) {
    RcppHoney::hook< std::vector< int > > retval = -v + v;
    return retval;
}

// [[Rcpp::export]]
std::vector< double > test_unary_functions(std::vector< int > v) {
    RcppHoney::hook< std::vector< double > > retval = RcppHoney::sqrt(RcppHoney::log(v) + RcppHoney::exp(v));
    return retval;
}

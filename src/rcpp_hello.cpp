#include <Rcpp.h>
#include <vector>

#include <RcppHoney/operand.hpp>
#include <RcppHoney/hook.hpp>
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

#include <RcppHoney/operators.hpp>

using namespace Rcpp;

// [[Rcpp::export]]
std::vector< double > test_vector(std::vector< int > v, std::vector< double > v2) {
    RcppHoney::hook< std::vector< double > > retval = v + v2 + 1 + v + v + 2;
    return retval;
}

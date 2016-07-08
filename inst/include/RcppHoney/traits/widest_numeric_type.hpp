#pragma once

#include <Rcpp/r/headers.h>
#include "ctype.hpp"
#include "if_else.hpp"

namespace RcppHoney {
namespace traits {

template < typename T >
struct numeric_index {};

template<>
struct numeric_index< bool > { static const char value = 0; };

template<>
struct numeric_index< short > { static const char value = 1; };

template<>
struct numeric_index< int > { static const char value = 2; };

template<>
struct numeric_index< long > { static const char value = 3; };

template<>
struct numeric_index< float > { static const char value = 5; };

template<>
struct numeric_index< double > { static const char value = 6; };

template<>
struct numeric_index< long double > { static const char value = 7; };

template<>
struct numeric_index< Rcomplex > { static const char value = 8; };

template< typename LHS, typename RHS >
struct widest_numeric_type {
    typedef typename if_else<
        (numeric_index< typename ctype< LHS >::type >::value > numeric_index< typename ctype< RHS >::type >::value),
        typename ctype< LHS >::type,
        typename ctype< RHS >::type >::type type;
};

} // namespace traits
} // namespace RcppHoney

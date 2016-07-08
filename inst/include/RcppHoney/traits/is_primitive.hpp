#pragma once

#include <Rcpp/r/headers.h>

namespace RcppHoney {
namespace traits {

template< typename T >
struct is_primitive {
    static const bool value = false;
};

template<>
struct is_primitive< int > {
    static const bool value = true;
};

template<>
struct is_primitive< double > {
    static const bool value = true;
};

template<>
struct is_primitive< Rcomplex > {
    static const bool value = true;
};

} // namespace traits
} // namespace RcppHoney

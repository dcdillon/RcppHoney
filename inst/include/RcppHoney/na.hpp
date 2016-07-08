#pragma once

#include "r_headers.hpp"

namespace RcppHoney {

template< typename T >
struct na {};

template<>
struct na< int > {
    static const int VALUE() {return NA_INTEGER;}
    static const bool is_na(int val) {return NA_INTEGER == val;}
};

template<>
struct na< double > {
    static const double VALUE() {return NA_REAL;}
    static const bool is_na(double val) {return R_IsNA(val);}
};

} // namespace RcppHoney

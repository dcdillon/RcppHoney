// Copyright (C) 2016 Daniel C. Dillon
//
// This file is part of RcppHoney.
//
// RcppHoney is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// RcppHoney is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RcppHoney.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <Rcpp.h>
#include "operand.hpp"
#include "scalar_operator.hpp"
#include "unary_operator.hpp"
#include "binary_operator.hpp"
#include "functors.hpp"
#include "hook.hpp"
#include "traits/enable_if.hpp"

namespace RcppHoney {

#define RCPP_HONEY_GENERATE_UNARY_FUNCTION(_FNAME_)                                     \
template< typename T, typename T_ITER, typename T_RESULT >                              \
unary_operator< T_ITER, functors:: _FNAME_ < T_ITER, T::NA >, T::NA >                   \
_FNAME_ (const operand< T, T_ITER, T_RESULT > &rhs) {                                   \
    return make_unary_operator< T::NA >()(rhs, functors:: _FNAME_ < T_ITER, T::NA >()); \
}                                                                                       \
                                                                                        \
template< typename T >                                                                  \
typename traits::enable_if<                                                             \
    hook< T >::value,                                                                   \
    unary_operator<                                                                     \
        typename hook< T >::const_iterator,                                             \
        functors:: _FNAME_ < typename hook< T >::const_iterator, hook< T >::NA >,       \
        hook< T >::NA                                                                   \
    >                                                                                   \
>::type                                                                                 \
_FNAME_ (const T &rhs) {                                                                \
    return make_unary_operator< hook< T >::NA >()(                                      \
        rhs,                                                                            \
        functors:: _FNAME_ < typename hook< T >::const_iterator, hook< T >::NA >());    \
}

RCPP_HONEY_GENERATE_UNARY_FUNCTION(log)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(exp)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(sqrt)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(acos)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(asin)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(atan)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(ceil)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(cos)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(cosh)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(floor)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(log10)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(sin)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(sinh)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(tan)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(tanh)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(abs)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(gamma)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(lgamma)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(digamma)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(trigamma)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(tetragamma)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(pentagamma)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(expm1)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(log1p)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(factorial)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(lfactorial)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(trunc)



// diff
template< typename T, typename T_ITER, typename T_RESULT >                              
unary_operator< T_ITER, functors::diff< T_ITER, T::NA >, T::NA >                   
diff(const operand< T, T_ITER, T_RESULT > &rhs) {                                   
    return unary_operator< T_ITER, functors::diff< T_ITER, T::NA >, T::NA >(
        rhs.begin() + 1, rhs.end(), functors::diff< T_ITER, T::NA >());
}                                                                                       
                                                                                        
template< typename T >                                                                  
typename traits::enable_if<                                                             
    hook< T >::value,                                                                   
    unary_operator<                                                                     
        typename hook< T >::const_iterator,                                             
        functors::diff< typename hook< T >::const_iterator, hook< T >::NA >,       
        hook< T >::NA                                                                   
    >                                                                                   
>::type                                                                                 
diff(const T &rhs) {                                                                
    return unary_operator<                                                                     
        typename hook< T >::const_iterator,                                             
        functors::diff< typename hook< T >::const_iterator, hook< T >::NA >,       
        hook< T >::NA                                                                   
    >(rhs.begin() + 1, rhs.end(),
        functors::diff< typename hook< T >::const_iterator, hook< T >::NA >());
}

} // namespace RcppHoney

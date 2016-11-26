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

#include "operand.hpp"
#include "scalar_operator.hpp"
#include "unary_operator.hpp"
#include "binary_operator.hpp"
#include "functors.hpp"
#include "hook.hpp"
#include "traits/enable_if.hpp"
#include "traits/is_primitive.hpp"

namespace RcppHoney {

#define RCPP_HONEY_GENERATE_UNARY_FUNCTION(_FNAME_, _FUNCTOR_)                            \
template< typename T, typename T_ITER, typename T_RESULT >                                \
unary_operator< T_ITER, functors:: _FUNCTOR_ < T_ITER, T::NA >, T::NA >                   \
_FNAME_ (const operand< T, T_ITER, T_RESULT > &rhs) {                                     \
    return make_unary_operator< T::NA >()(rhs, functors:: _FUNCTOR_ < T_ITER, T::NA >()); \
}                                                                                         \
                                                                                          \
template< typename T >                                                                    \
typename traits::enable_if<                                                               \
    hook< T >::value,                                                                     \
    unary_operator<                                                                       \
        typename hook< T >::const_iterator,                                               \
        functors:: _FUNCTOR_ < typename hook< T >::const_iterator, hook< T >::NA >,       \
        hook< T >::NA                                                                     \
    >                                                                                     \
>::type                                                                                   \
_FNAME_ (const T &rhs) {                                                                  \
    return make_unary_operator< hook< T >::NA >()(                                        \
        rhs,                                                                              \
        functors:: _FUNCTOR_ < typename hook< T >::const_iterator, hook< T >::NA >());    \
}

#define RCPP_HONEY_GENERATE_BINARY_FUNCTION(_FNAME_, _FUNCTOR_)                                                        \
template< typename T, typename T_ITER, typename T_RESULT, typename U, typename U_ITER, typename U_RESULT >             \
RcppHoney::binary_operator< T_ITER, U_ITER,                                                                            \
    RcppHoney::functors:: _FUNCTOR_ < T_ITER, U_ITER, (T::NA || U::NA) >,                                              \
    (T::NA || U::NA)                                                                                                   \
>                                                                                                                      \
_FNAME_ (const RcppHoney::operand< T, T_ITER, T_RESULT > &lhs,                                                         \
    const RcppHoney::operand< U, U_ITER, U_RESULT > &rhs) {                                                            \
                                                                                                                       \
    return RcppHoney::make_binary_operator< (T::NA || U::NA) >()(                                                      \
        lhs, rhs,                                                                                                      \
        RcppHoney::functors:: _FUNCTOR_ < T_ITER, U_ITER, (T::NA || U::NA) >());                                       \
}                                                                                                                      \
                                                                                                                       \
template< typename T, typename T_ITER, typename T_RESULT, typename U >                                                 \
typename RcppHoney::traits::enable_if< RcppHoney::traits::is_primitive< U >::value,                                    \
    RcppHoney::binary_operator< T_ITER, typename RcppHoney::scalar_operator< U >::const_iterator,                      \
        RcppHoney::functors:: _FUNCTOR_ < T_ITER, typename RcppHoney::scalar_operator< U >::const_iterator, T::NA >,   \
        T::NA                                                                                                          \
    >                                                                                                                  \
>::type                                                                                                                \
_FNAME_ (const RcppHoney::operand< T, T_ITER, T_RESULT > &lhs, const U &rhs) {                                         \
    return RcppHoney::make_binary_operator< T::NA >()(lhs, RcppHoney::make_scalar_operator()(rhs),                     \
        RcppHoney::functors:: _FUNCTOR_ < T_ITER, typename RcppHoney::scalar_operator< U >::const_iterator, T::NA >());\
}                                                                                                                      \
                                                                                                                       \
template< typename T, typename U, typename U_ITER, typename U_RESULT >                                                 \
typename RcppHoney::traits::enable_if< RcppHoney::traits::is_primitive< T >::value,                                    \
    RcppHoney::binary_operator< typename RcppHoney::scalar_operator< T >::const_iterator, U_ITER,                      \
        RcppHoney::functors:: _FUNCTOR_ < typename RcppHoney::scalar_operator< T >::const_iterator, U_ITER, U::NA >,   \
        U::NA                                                                                                          \
    >                                                                                                                  \
>::type                                                                                                                \
_FNAME_ (const T &lhs, const RcppHoney::operand< U, U_ITER, U_RESULT > &rhs) {                                         \
    return RcppHoney::make_binary_operator< U::NA >()(RcppHoney::make_scalar_operator()(lhs), rhs,                     \
        RcppHoney::functors:: _FUNCTOR_ < typename RcppHoney::scalar_operator< T >::const_iterator, U_ITER, U::NA >());\
}                                                                                                                      \
                                                                                                                       \
template< typename T, typename U >                                                                                     \
typename RcppHoney::traits::enable_if<                                                                                 \
    (RcppHoney::hook< T >::value && RcppHoney::hook< U >::value),                                                      \
    RcppHoney::binary_operator<                                                                                        \
        typename RcppHoney::hook< T >::const_iterator,                                                                 \
        typename RcppHoney::hook< U >::const_iterator,                                                                 \
        RcppHoney::functors:: _FUNCTOR_ <                                                                              \
            typename RcppHoney::hook< T >::const_iterator,                                                             \
            typename RcppHoney::hook< U >::const_iterator,                                                             \
            (RcppHoney::hook< T >::NA || RcppHoney::hook< U >::NA)                                                     \
        >,                                                                                                             \
        (RcppHoney::hook< T >::NA || RcppHoney::hook< U >::NA)                                                         \
    >                                                                                                                  \
>::type                                                                                                                \
_FNAME_ (const T &lhs, const U &rhs) {                                                                                 \
    return RcppHoney::make_binary_operator< (RcppHoney::hook< T >::NA || RcppHoney::hook< U >::NA) >()(                \
        lhs,                                                                                                           \
        rhs,                                                                                                           \
        RcppHoney::functors:: _FUNCTOR_ <                                                                              \
            typename RcppHoney::hook< T >::const_iterator,                                                             \
            typename RcppHoney::hook< U >::const_iterator,                                                             \
            (RcppHoney::hook< T >::NA || RcppHoney::hook< U >::NA)                                                     \
        >());                                                                                                          \
}                                                                                                                      \
                                                                                                                       \
template< typename T, typename T_ITER, typename T_RESULT, typename U >                                                 \
typename RcppHoney::traits::enable_if< RcppHoney::hook< U >::value,                                                    \
    RcppHoney::binary_operator<                                                                                        \
        T_ITER,                                                                                                        \
        typename RcppHoney::hook< U >::const_iterator,                                                                 \
        RcppHoney::functors:: _FUNCTOR_ <                                                                              \
            T_ITER,                                                                                                    \
            typename RcppHoney::hook< U >::const_iterator,                                                             \
            (T::NA || RcppHoney::hook< U >::NA)                                                                        \
        >,                                                                                                             \
        (T::NA || RcppHoney::hook< U >::NA)                                                                            \
    >                                                                                                                  \
>::type                                                                                                                \
_FNAME_ (const RcppHoney::operand< T, T_ITER, T_RESULT > &lhs, const U &rhs) {                                         \
    return RcppHoney::make_binary_operator< (T::NA || RcppHoney::hook< U >::NA) >()(                                   \
        lhs,                                                                                                           \
        rhs,                                                                                                           \
        RcppHoney::functors:: _FUNCTOR_ <                                                                              \
            T_ITER,                                                                                                    \
            typename RcppHoney::hook< U >::const_iterator,                                                             \
            (T::NA || RcppHoney::hook< U >::NA)                                                                        \
        >());                                                                                                          \
}                                                                                                                      \
                                                                                                                       \
template< typename T, typename U, typename U_ITER, typename U_RESULT >                                                 \
typename RcppHoney::traits::enable_if< RcppHoney::hook< T >::value,                                                    \
    RcppHoney::binary_operator<                                                                                        \
        typename RcppHoney::hook< T >::const_iterator,                                                                 \
        U_ITER,                                                                                                        \
        RcppHoney::functors:: _FUNCTOR_ <                                                                              \
            typename RcppHoney::hook< T >::const_iterator,                                                             \
            U_ITER,                                                                                                    \
            (U::NA || RcppHoney::hook< T >::NA)                                                                        \
        >,                                                                                                             \
        (U::NA || RcppHoney::hook< T >::NA)                                                                            \
    >                                                                                                                  \
>::type                                                                                                                \
_FNAME_ (const T &lhs, const RcppHoney::operand< U, U_ITER, U_RESULT > &rhs) {                                         \
    return RcppHoney::make_binary_operator< (U::NA || RcppHoney::hook< T >::NA) >()(                                   \
        lhs,                                                                                                           \
        rhs,                                                                                                           \
        RcppHoney::functors:: _FUNCTOR_ <                                                                              \
            typename RcppHoney::hook< T >::const_iterator,                                                             \
            U_ITER,                                                                                                    \
            (U::NA || RcppHoney::hook< T >::NA)                                                                        \
        >());                                                                                                          \
}                                                                                                                      \
                                                                                                                       \
template< typename T, typename U >                                                                                     \
typename RcppHoney::traits::enable_if<                                                                                 \
    RcppHoney::traits::is_primitive< T >::value                                                                        \
    && RcppHoney::hook< U >::value,                                                                                    \
    RcppHoney::binary_operator<                                                                                        \
        typename RcppHoney::scalar_operator< T >::const_iterator,                                                      \
        typename RcppHoney::hook< U >::const_iterator,                                                                 \
        RcppHoney::functors:: _FUNCTOR_ <                                                                              \
            typename RcppHoney::scalar_operator< T >::const_iterator,                                                  \
            typename RcppHoney::hook< U >::const_iterator,                                                             \
            RcppHoney::hook< U >::NA                                                                                   \
        >,                                                                                                             \
        RcppHoney::hook< U >::NA                                                                                       \
    >                                                                                                                  \
>::type                                                                                                                \
_FNAME_ (const T &lhs, const U &rhs) {                                                                                 \
    return RcppHoney::make_binary_operator< RcppHoney::hook< U >::NA >()(                                              \
        RcppHoney::make_scalar_operator()(lhs),                                                                        \
        rhs,                                                                                                           \
        RcppHoney::functors:: _FUNCTOR_ <                                                                              \
            typename RcppHoney::scalar_operator< T >::const_iterator,                                                  \
            typename RcppHoney::hook< U >::const_iterator,                                                             \
            RcppHoney::hook< U >::NA                                                                                   \
        >());                                                                                                          \
}                                                                                                                      \
                                                                                                                       \
template< typename T, typename U >                                                                                     \
typename RcppHoney::traits::enable_if<                                                                                 \
    RcppHoney::traits::is_primitive< U >::value                                                                        \
    && RcppHoney::hook< T >::value,                                                                                    \
    RcppHoney::binary_operator<                                                                                        \
        typename RcppHoney::hook< T >::const_iterator,                                                                 \
        typename RcppHoney::scalar_operator< U >::const_iterator,                                                      \
        RcppHoney::functors:: _FUNCTOR_ <                                                                              \
            typename RcppHoney::hook< T >::const_iterator,                                                             \
            typename RcppHoney::scalar_operator< U >::const_iterator,                                                  \
            RcppHoney::hook< T >::NA                                                                                   \
        >,                                                                                                             \
        RcppHoney::hook< T >::NA                                                                                       \
    >                                                                                                                  \
>::type                                                                                                                \
_FNAME_ (const T &lhs, const U &rhs) {                                                                                 \
    return RcppHoney::make_binary_operator< RcppHoney::hook< T >::NA >()(                                              \
        lhs,                                                                                                           \
        RcppHoney::make_scalar_operator()(rhs),                                                                        \
        RcppHoney::functors:: _FUNCTOR_ <                                                                              \
            typename RcppHoney::hook< T >::const_iterator,                                                             \
            typename RcppHoney::scalar_operator< U >::const_iterator,                                                  \
            RcppHoney::hook< T >::NA                                                                                   \
        >());                                                                                                          \
}

RCPP_HONEY_GENERATE_UNARY_FUNCTION(log, log)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(exp, exp)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(sqrt, sqrt)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(acos, acos)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(asin, asin)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(atan, atan)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(ceil, ceil)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(cos, cos)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(cosh, cosh)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(floor, floor)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(log10, log10)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(sin, sin)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(sinh, sinh)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(tan, tan)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(tanh, tanh)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(abs, abs)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(gamma, gamma)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(lgamma, lgamma)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(digamma, digamma)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(trigamma, trigamma)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(tetragamma, tetragamma)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(pentagamma, pentagamma)

#if __cplusplus >= 201103L
RCPP_HONEY_GENERATE_UNARY_FUNCTION(expm1, expm1)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(log1p, log1p)
#endif

RCPP_HONEY_GENERATE_UNARY_FUNCTION(factorial, factorial)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(lfactorial, lfactorial)
RCPP_HONEY_GENERATE_UNARY_FUNCTION(trunc, trunc)




RCPP_HONEY_GENERATE_BINARY_FUNCTION(pow, pow)
RCPP_HONEY_GENERATE_BINARY_FUNCTION(choose, choose)
RCPP_HONEY_GENERATE_BINARY_FUNCTION(lchoose, lchoose)
RCPP_HONEY_GENERATE_BINARY_FUNCTION(beta, beta)
RCPP_HONEY_GENERATE_BINARY_FUNCTION(lbeta, lbeta)
RCPP_HONEY_GENERATE_BINARY_FUNCTION(psigamma, psigamma)
RCPP_HONEY_GENERATE_BINARY_FUNCTION(round, round)
RCPP_HONEY_GENERATE_BINARY_FUNCTION(signif, signif)



// diff
template< typename T, typename T_ITER, typename T_RESULT >
unary_operator< T_ITER, functors::diff< T_ITER, T::NA >, T::NA >
diff(const operand< T, T_ITER, T_RESULT > &rhs) {

    if (rhs.dims().second != 0) {
        throw bounds_exception();
    }

    T_ITER begin = rhs.begin();
    ++begin;
    return unary_operator< T_ITER, functors::diff< T_ITER, T::NA >, T::NA >(
        begin, rhs.end(), rhs.dims(), functors::diff< T_ITER, T::NA >());
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
    dims_t dims = hooks::extract_dims(rhs);

    if (dims.second != 0) {
        throw bounds_exception();
    }

    typename hook< T >::const_iterator begin = rhs.begin();
    ++begin;

    return unary_operator<
        typename hook< T >::const_iterator,
        functors::diff< typename hook< T >::const_iterator, hook< T >::NA >,
        hook< T >::NA
    >(begin, rhs.end(), dims,
        functors::diff< typename hook< T >::const_iterator, hook< T >::NA >());
}

} // namespace RcppHoney

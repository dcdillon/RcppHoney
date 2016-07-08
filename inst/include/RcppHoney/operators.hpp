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

#define RCPP_HONEY_GENERATE_BINARY_OPERATOR(_OP_, _FUNCTOR_)                                                           \
template< typename T, typename T_ITER, typename T_RESULT, typename U, typename U_ITER, typename U_RESULT >             \
inline RcppHoney::binary_operator< T_ITER, U_ITER,                                                                     \
    RcppHoney::functors:: _FUNCTOR_ < T_ITER, U_ITER, (T::NA || U::NA) >,                                              \
    (T::NA || U::NA)                                                                                                   \
>                                                                                                                      \
operator _OP_ (const RcppHoney::operand< T, T_ITER, T_RESULT > &lhs,                                                   \
    const RcppHoney::operand< U, U_ITER, U_RESULT > &rhs) {                                                            \
                                                                                                                       \
    return RcppHoney::make_binary_operator< (T::NA || U::NA) >()(                                       \
        lhs, rhs,                                                                                                      \
        RcppHoney::functors:: _FUNCTOR_ < T_ITER, U_ITER, (T::NA || U::NA) >());                                       \
}                                                                                                                      \
                                                                                                                       \
template< typename T, typename T_ITER, typename T_RESULT, typename U >                                                 \
inline typename RcppHoney::traits::enable_if< RcppHoney::traits::is_primitive< U >::value,                             \
    RcppHoney::binary_operator< T_ITER, typename RcppHoney::scalar_operator< U >::const_iterator,                      \
        RcppHoney::functors:: _FUNCTOR_ < T_ITER, typename RcppHoney::scalar_operator< U >::const_iterator, T::NA >,   \
        T::NA                                                                                                          \
    >                                                                                                                  \
>::type                                                                                                                \
operator _OP_ (const RcppHoney::operand< T, T_ITER, T_RESULT > &lhs, const U &rhs) {                                   \
    return RcppHoney::make_binary_operator< T::NA >()(lhs, RcppHoney::make_scalar_operator()(rhs),                     \
        RcppHoney::functors:: _FUNCTOR_ < T_ITER, typename RcppHoney::scalar_operator< U >::const_iterator, T::NA >());\
}                                                                                                                      \
                                                                                                                       \
template< typename T, typename U, typename U_ITER, typename U_RESULT >                                                 \
inline typename RcppHoney::traits::enable_if< RcppHoney::traits::is_primitive< T >::value,                             \
    RcppHoney::binary_operator< typename RcppHoney::scalar_operator< T >::const_iterator, U_ITER,                      \
        RcppHoney::functors:: _FUNCTOR_ < typename RcppHoney::scalar_operator< T >::const_iterator, U_ITER, U::NA >,   \
        U::NA                                                                                                          \
    >                                                                                                                  \
>::type                                                                                                                \
operator _OP_ (const T &lhs, const RcppHoney::operand< U, U_ITER, U_RESULT > &rhs) {                                   \
    return RcppHoney::make_binary_operator< U::NA >()(RcppHoney::make_scalar_operator()(lhs),                          \
        RcppHoney::functors:: _FUNCTOR_ < typename RcppHoney::scalar_operator< T >::const_iterator, U_ITER, U::NA >());\
}                                                                                                                      \
                                                                                                                       \
template< typename T, typename U >                                                                                     \
inline typename RcppHoney::traits::enable_if< RcppHoney::hook< T >::value,                                             \
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
operator _OP_ (const T &lhs, const U &rhs) {                                                                           \
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
inline typename RcppHoney::traits::enable_if< RcppHoney::hook< U >::value,                                             \
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
operator _OP_ (const RcppHoney::operand< T, T_ITER, T_RESULT > &lhs, const U &rhs) {                                   \
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
inline typename RcppHoney::traits::enable_if< RcppHoney::hook< T >::value,                                             \
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
operator _OP_ (const T &lhs, const RcppHoney::operand< U, U_ITER, U_RESULT > &rhs) {                                   \
    return RcppHoney::make_binary_operator< (U::NA || RcppHoney::hook< T >::NA) >()(                                   \
        lhs,                                                                                                           \
        rhs,                                                                                                           \
        RcppHoney::functors:: _FUNCTOR_ <                                                                              \
            typename RcppHoney::hook< T >::const_iterator,                                                             \
            U_ITER,                                                                                                    \
            (U::NA || RcppHoney::hook< T >::NA)                                                                        \
        >());                                                                                                          \
}


RCPP_HONEY_GENERATE_BINARY_OPERATOR(+, plus)
RCPP_HONEY_GENERATE_BINARY_OPERATOR(-, minus)
RCPP_HONEY_GENERATE_BINARY_OPERATOR(*, times)
RCPP_HONEY_GENERATE_BINARY_OPERATOR(/, divided_by)
RCPP_HONEY_GENERATE_BINARY_OPERATOR(>, greater)
RCPP_HONEY_GENERATE_BINARY_OPERATOR(>=, greater_equal)
RCPP_HONEY_GENERATE_BINARY_OPERATOR(<, less)
RCPP_HONEY_GENERATE_BINARY_OPERATOR(<=, less_equal)
RCPP_HONEY_GENERATE_BINARY_OPERATOR(==, equal)
RCPP_HONEY_GENERATE_BINARY_OPERATOR(!=, not_equal)

#define RCPP_HONEY_GENERATE_UNARY_OPERATOR(_OP_, _FUNCTOR_)                                                             \
template< typename T, typename T_ITER, typename T_RESULT >                                                              \
RcppHoney::unary_operator< T_ITER, RcppHoney::functors:: _FUNCTOR_ < T_ITER, T::NA >, T::NA >                           \
operator _OP_ (const RcppHoney::operand< T, T_ITER, T_RESULT > &rhs) {                                                  \
    return RcppHoney::make_unary_operator< T::NA >()(rhs, RcppHoney::functors:: _FUNCTOR_ < T_ITER, T::NA >());         \
}                                                                                                                       \
                                                                                                                        \
template< typename T >                                                                                                  \
typename RcppHoney::traits::enable_if<                                                                                  \
    RcppHoney::hook< T >::value,                                                                                        \
    RcppHoney::unary_operator<                                                                                          \
        typename RcppHoney::hook< T >::const_iterator,                                                                  \
        RcppHoney::functors:: _FUNCTOR_ < typename RcppHoney::hook< T >::const_iterator, RcppHoney::hook< T >::NA >,    \
        RcppHoney::hook< T >::NA                                                                                        \
    >                                                                                                                   \
>::type                                                                                                                 \
operator _OP_ (const T &rhs) {                                                                                          \
    return RcppHoney::make_unary_operator< RcppHoney::hook< T >::NA >()(rhs,                                            \
        RcppHoney::functors::unary_minus< typename RcppHoney::hook< T >::const_iterator, RcppHoney::hook< T >::NA >()); \
}

RCPP_HONEY_GENERATE_UNARY_OPERATOR(-, unary_minus)
RCPP_HONEY_GENERATE_UNARY_OPERATOR(!, unary_not)

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

namespace RcppHoney {
namespace hooks {

// hooks for std::vector
template< typename T, typename A>
RcppHoney::traits::true_type is_hooked(const std::vector< T, A > &val);

// hooks for std::set
template< typename T, typename C, typename A >
RcppHoney::traits::true_type is_hooked(const std::set< T, C, A > &val);

// hooks for Rcpp::VectorBase
template< int RTYPE, bool NA, typename T >
RcppHoney::traits::true_type is_hooked(
    const Rcpp::VectorBase< RTYPE, NA, T > &val);

// return the appropriate NA value
template< int RTYPE, typename T >
RcppHoney::traits::false_type has_na(
    const Rcpp::VectorBase< RTYPE, false, T > &val);

template< int RTYPE, typename T >
RcppHoney::traits::true_type has_na(
    const Rcpp::VectorBase< RTYPE, true, T > &val);

// assert that we need to create basic operators
template< int RTYPE, bool NA, typename T >
RcppHoney::traits::true_type needs_basic_operators(
    const Rcpp::VectorBase< RTYPE, NA, T > &val);

// assert that we need to create type + scalar operators
template< int RTYPE, bool NA, typename T >
RcppHoney::traits::true_type needs_scalar_operators(
    const Rcpp::VectorBase< RTYPE, NA, T > &val);

// call this family 2
template< int RTYPE, bool NA, typename T >
RcppHoney::traits::int_constant< 2 > family(
    const Rcpp::VectorBase< RTYPE, NA, T > &val);







// hooks for Rcpp::VectorBase
template< int RTYPE, template< class > class StoragePolicy >
RcppHoney::traits::true_type is_hooked(
    const Rcpp::Matrix< RTYPE, StoragePolicy > &val);

// return the appropriate NA value
template< int RTYPE, template< class > class StoragePolicy >
RcppHoney::traits::true_type has_na(
    const Rcpp::Matrix< RTYPE, StoragePolicy > &val);

// assert that we need to create basic operators
template< int RTYPE, template< class > class StoragePolicy >
RcppHoney::traits::true_type needs_basic_operators(
    const Rcpp::Matrix< RTYPE, StoragePolicy > &val);

// assert that we need to create type + scalar operators
template< int RTYPE, template< class > class StoragePolicy >
RcppHoney::traits::true_type needs_scalar_operators(
    const Rcpp::Matrix< RTYPE, StoragePolicy > &val);

// call this family 3
template< int RTYPE, template< class > class StoragePolicy >
RcppHoney::traits::int_constant< 3 > family(
    const Rcpp::Matrix< RTYPE, StoragePolicy > &val);

template< int RTYPE, template< class > class StoragePolicy >
dims_t extract_dims(
    const Rcpp::Matrix< RTYPE, StoragePolicy > &obj)
{
    return dims_t(obj.nrow(), obj.ncol());
}

template< typename T, typename T_ITER, typename T_RESULT >
dims_t extract_dims(const operand< T, T_ITER, T_RESULT > &obj) {
    return obj.dims();
}

} // namespace hooks
} // namespace RcppHoney

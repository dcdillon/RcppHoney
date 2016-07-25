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
#include <algorithm>

namespace RcppHoney {

class LogicalVector : public Rcpp::LogicalVector {
public:
    template< typename T, typename T_ITER, typename T_RESULT >
    LogicalVector(const operand< T, T_ITER, T_RESULT > &rhs)
        : Rcpp::LogicalVector(rhs.size()) {
            std::copy(rhs.begin(), rhs.end(), begin());
    }
};

class IntegerVector : public Rcpp::IntegerVector {
public:
    template< typename T, typename T_ITER, typename T_RESULT >
    IntegerVector(const operand< T, T_ITER, T_RESULT > &rhs)
        : Rcpp::IntegerVector(rhs.size()) {
            std::copy(rhs.begin(), rhs.end(), begin());
    }
};

class NumericVector : public Rcpp::NumericVector {
public:
    template< typename T, typename T_ITER, typename T_RESULT >
    NumericVector(const operand< T, T_ITER, T_RESULT > &rhs)
        : Rcpp::NumericVector(rhs.size()) {
            std::copy(rhs.begin(), rhs.end(), begin());
    }
};

} // namespace RcppHoney

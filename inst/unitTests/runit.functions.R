#!/usr/bin/r -t
#
# Copyright (C) 2016 Daniel C. Dillon
#
# This file is part of RcppHoney.
#
# RcppHoney is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# RcppHoney is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with RcppHoney.  If not, see <http://www.gnu.org/licenses/>.

.setUp <- RcppHoney:::unit_test_setup("functions.cpp", "RcppHoney")

pow <- function(x, y) {x ^ y}

test.unary.function <- function() {
    v <- 1:100
    checkEquals(log(v), test_unary_function_hooked(v))
    checkEquals(log(v + v), test_unary_function_operand(v))
}

test.binary.function.hooked.and.scalar <- function() {
    v <- 1:5
    s <- 2
    checkEquals(pow(v, s), test_binary_function_hooked_scalar(v, s))
    checkEquals(pow(s, v), test_binary_function_scalar_hooked(s, v))
}

test.binary.function.hooked.and.hooked <- function() {
    v <- 1:5
    checkEquals(pow(v, v), test_binary_function_hooked_hooked(v, v))
    checkEquals(pow(v, v), test_binary_function_hooked_other_hooked(v, v))
    checkEquals(pow(v, v), test_binary_function_other_hooked_hooked(v, v))
}

test.binary.function.operand.and.scalar <- function() {
    v <- 1:5
    s <- 2
    checkEquals(pow((v + v), s), test_binary_function_operand_scalar(v, v, s))
    checkEquals(pow(s, (v + v)), test_binary_function_scalar_operand(s, v, v))
}

test.binary.function.operand.and.hooked <- function() {
    v <- 1:5
    checkEquals(pow((v + v), v), test_binary_function_operand_hooked(v, v, v))
    checkEquals(pow(v, (v + v)), test_binary_function_hooked_operand(v, v, v))
}

test.binary.function.operand.and.operand <- function() {
    v <- 1:4
    checkEquals(pow(v + v, v + v), test_binary_function_operand_operand(v, v))
}

test.na.unary.function <- function() {
    v <- 1:100
    v <- c(v, NA)
    checkEquals(log(v), test_unary_function_hooked(v))
    checkEquals(log(v + v), test_unary_function_operand(v))
}

test.na.binary.function.hooked.and.scalar <- function() {
    v <- 1:5
    v <- c(v, NA)
    s <- 2
    checkEquals(pow(v, s), test_binary_function_hooked_scalar(v, s))
    checkEquals(pow(s, v), test_binary_function_scalar_hooked(s, v))
}

test.na.binary.function.hooked.and.hooked <- function() {
    v <- 1:5
    v <- c(v, NA)
    checkEquals(pow(v, v), test_binary_function_hooked_hooked(v, v))
    checkEquals(pow(v, v), test_binary_function_hooked_other_hooked(v, v))
    checkEquals(pow(v, v), test_binary_function_other_hooked_hooked(v, v))
}

test.na.binary.function.operand.and.scalar <- function() {
    v <- 1:5
    v <- c(v, NA)
    s <- 2
    checkEquals(pow((v + v), s), test_binary_function_operand_scalar(v, v, s))
    checkEquals(pow(s, (v + v)), test_binary_function_scalar_operand(s, v, v))
}

test.na.binary.function.operand.and.hooked <- function() {
    v <- 1:5
    v <- c(v, NA)
    checkEquals(pow((v + v), v), test_binary_function_operand_hooked(v, v, v))
    checkEquals(pow(v, (v + v)), test_binary_function_hooked_operand(v, v, v))
}

test.na.binary.function.operand.and.operand <- function() {
    v <- 1:4
    v <- c(v, NA)
    checkEquals(pow(v + v, v + v), test_binary_function_operand_operand(v, v))
}





test.unary.functions <- function() {
    v <- c(.1, .2, .3, .4, .5, .6, .7, .8, .9, 1)
    checkEquals(log(v), test_log(v))
    checkEquals(exp(v), test_exp(v))
    checkEquals(sqrt(v), test_sqrt(v))
    checkEquals(acos(v), test_acos(v))
    checkEquals(asin(v), test_asin(v))
    checkEquals(atan(v), test_atan(v))
    checkEquals(ceiling(v), test_ceil(v))
    checkEquals(cos(v), test_cos(v))
    checkEquals(cosh(v), test_cosh(v))
    checkEquals(floor(v), test_floor(v))
    checkEquals(log10(v), test_log10(v))
    checkEquals(sin(v), test_sin(v))
    checkEquals(sinh(v), test_sinh(v))
    checkEquals(tan(v), test_tan(v))
    checkEquals(tanh(v), test_tanh(v))
    checkEquals(abs(v), test_abs(v))
    checkEquals(gamma(v), test_gamma(v))
    checkEquals(lgamma(v), test_lgamma(v))
    checkEquals(digamma(v), test_digamma(v))
    checkEquals(trigamma(v), test_trigamma(v))
    checkEquals(psigamma(v, 2), test_tetragamma(v))
    checkEquals(psigamma(v, 3), test_pentagamma(v))
    checkEquals(factorial(v), test_factorial(v))
    checkEquals(lfactorial(v), test_lfactorial(v))
    checkEquals(trunc(v), test_trunc(v))
}

test.binary.functions <- function() {
    v1 <- c(.1, .2, .3, .4, .5, .6, .7, .8, .9, 1)
    v2 <- 1:10
    checkEquals(pow(v1, v2), test_pow(v1, v2))
    checkEquals(choose(v1, v2), test_choose(v1, v2))
    checkEquals(lchoose(v1, v2), test_lchoose(v1, v2))
    checkEquals(beta(v1, v2), test_beta(v1, v2))
    checkEquals(lbeta(v1, v2), test_lbeta(v1, v2))
    checkEquals(psigamma(v1, v2), test_psigamma(v1, v2))
    checkEquals(round(v1, v2), test_round(v1, v2))
    checkEquals(signif(v1, v2), test_signif(v1, v2))
}

test.na.unary.functions <- function() {
    v <- c(.1, .2, .3, .4, NA, .5, .6, .7, .8, .9, 1, NA)
    checkEquals(log(v), test_log(v))
    checkEquals(exp(v), test_exp(v))
    checkEquals(sqrt(v), test_sqrt(v))
    checkEquals(acos(v), test_acos(v))
    checkEquals(asin(v), test_asin(v))
    checkEquals(atan(v), test_atan(v))
    checkEquals(ceiling(v), test_ceil(v))
    checkEquals(cos(v), test_cos(v))
    checkEquals(cosh(v), test_cosh(v))
    checkEquals(floor(v), test_floor(v))
    checkEquals(log10(v), test_log10(v))
    checkEquals(sin(v), test_sin(v))
    checkEquals(sinh(v), test_sinh(v))
    checkEquals(tan(v), test_tan(v))
    checkEquals(tanh(v), test_tanh(v))
    checkEquals(abs(v), test_abs(v))
    checkEquals(gamma(v), test_gamma(v))
    checkEquals(lgamma(v), test_lgamma(v))
    checkEquals(digamma(v), test_digamma(v))
    checkEquals(trigamma(v), test_trigamma(v))
    checkEquals(psigamma(v, 2), test_tetragamma(v))
    checkEquals(psigamma(v, 3), test_pentagamma(v))
    checkEquals(factorial(v), test_factorial(v))
    checkEquals(lfactorial(v), test_lfactorial(v))
    checkEquals(trunc(v), test_trunc(v))
}

test.na.binary.functions <- function() {
    v1 <- c(.1, .2, .3, .4, .5, NA, .6, .7, .8, .9, 1, NA)
    v2 <- 1:12
    checkEquals(pow(v1, v2), test_pow(v1, v2))
    checkEquals(choose(v1, v2), test_choose(v1, v2))
    checkEquals(lchoose(v1, v2), test_lchoose(v1, v2))
    checkEquals(beta(v1, v2), test_beta(v1, v2))
    checkEquals(lbeta(v1, v2), test_lbeta(v1, v2))
    checkEquals(psigamma(v1, v2), test_psigamma(v1, v2))
    checkEquals(round(v1, v2), test_round(v1, v2))
    checkEquals(signif(v1, v2), test_signif(v1, v2))
}
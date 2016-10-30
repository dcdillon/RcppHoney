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

.setUp <- RcppHoney:::unit_test_setup("operators.cpp", "RcppHoney")

test.hooked.and.scalar <- function() {
    v <- 1:100
    m <- matrix(1:100, 10, 10)
    s <- 15
    checkEquals(v + s, test_hooked_plus_scalar(v, s))
    checkEquals(s + v, test_scalar_plus_hooked(s, v))
    checkEquals(m + s, test_matrix_plus_scalar(m, s))
    checkEquals(s + m, test_scalar_plus_matrix(s, m))
}

test.hooked.and.hooked <- function() {
    v <- 1:100
    checkEquals(v + v, test_hooked_plus_hooked(v, v))
    checkEquals(v + v, test_hooked_plus_other_hooked(v, v))
    checkEquals(v + v, test_other_hooked_plus_hooked(v, v))
}

test.operand.and.scalar <- function() {
    v <- 1:100
    s <- 15
    checkEquals((v + v) + s, test_operand_plus_scalar(v, v, s))
    checkEquals(s + (v + v), test_scalar_plus_operand(s, v, v))
}

test.operand.and.hooked <- function() {
    v <- 1:100
    checkEquals((v + v) + v, test_operand_plus_hooked(v, v, v))
    checkEquals(v + (v + v), test_hooked_plus_operand(v, v, v))
}

test.operand.and.operand <- function() {
    v <- 1:100
    checkEquals((v + v) + (v + v), test_operand_plus_operand(v, v))
}

test.unary.operator <- function() {
    v <- 1:100
    checkEquals(-v, test_unary_operator_hooked(v))
    checkEquals(-(v + v), test_unary_operator_operand(v))
}

test.na.hooked.and.scalar <- function() {
    v <- 1:100
    v <- c(v, NA)
    s <- 15
    checkEquals(v + s, test_hooked_plus_scalar(v, s))
    checkEquals(s + v, test_scalar_plus_hooked(s, v))
}

test.na.hooked.and.hooked <- function() {
    v <- 1:100
    v <- c(v, NA)
    checkEquals(v + v, test_hooked_plus_hooked(v, v))
    checkEquals(v + v, test_hooked_plus_other_hooked(v, v))
    checkEquals(v + v, test_other_hooked_plus_hooked(v, v))
}

test.na.operand.and.scalar <- function() {
    v <- 1:100
    v <- c(v, NA)
    s <- 15
    checkEquals((v + v) + s, test_operand_plus_scalar(v, v, s))
    checkEquals(s + (v + v), test_scalar_plus_operand(s, v, v))
}

test.na.operand.and.hooked <- function() {
    v <- 1:100
    v <- c(v, NA)
    checkEquals((v + v) + v, test_operand_plus_hooked(v, v, v))
    checkEquals(v + (v + v), test_hooked_plus_operand(v, v, v))
}

test.na.operand.and.operand <- function() {
    v <- 1:100
    v <- c(v, NA)
    checkEquals((v + v) + (v + v), test_operand_plus_operand(v, v))
}

test.na.unary.operator <- function() {
    v <- 1:100
    v <- c(v, NA)
    checkEquals(-v, test_unary_operator_hooked(v))
    checkEquals(-(v + v), test_unary_operator_operand(v))
}
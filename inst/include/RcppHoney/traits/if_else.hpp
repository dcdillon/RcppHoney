#pragma once

namespace RcppHoney {
namespace traits {

template< bool B, typename LHS = void, typename RHS = void >
struct if_else {};

template< typename LHS, typename RHS >
struct if_else< true, LHS, RHS > {
    typedef LHS type;
};

template< typename LHS, typename RHS >
struct if_else< false, LHS, RHS > {
    typedef RHS type;
};

} // namespace traits
} // namespace RcppHoney

#pragma once

namespace RcppHoney {
namespace traits {

template< bool VAL, typename T >
struct enable_if {
};

template< typename T >
struct enable_if< true, T > {
    typedef T type;
};

} // namespace traits
} // namespace RcppHoney

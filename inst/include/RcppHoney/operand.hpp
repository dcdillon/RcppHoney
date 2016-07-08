#pragma once

#include <stdint.h>

namespace RcppHoney {

template< typename T, typename Iterator, typename Result >
class operand
{
public:
    typedef Iterator const_iterator;
    typedef const_iterator iterator;
    typedef Result result_type;
    
public:
    uint64_t length() const {
        return static_cast< const T * >(this)->length();
    }
    
    const_iterator begin() const {
        return static_cast< const T * >(this)->begin();
    }
    
    const_iterator end() const {
        return static_cast< const T * >(this)->end();
    }
    
    result_type operator[](ptrdiff_t n) const {
        return *(static_cast< const T * >(this)->begin() + n);
    }
};

} // namespace RcppHoney
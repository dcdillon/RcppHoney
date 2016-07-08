#pragma once

#include <iterator>
#include <algorithm>
#include "operand.hpp"

namespace RcppHoney {

template< typename T >
struct scalar_operator_iterator : public std::iterator< std::random_access_iterator_tag, T > {
private:
    T m_value;

public:
    inline scalar_operator_iterator() {}

    inline scalar_operator_iterator(const T &val) : m_value(val) {}

    inline T operator*() {
       return m_value;
    }

    inline T *operator->() {
        return &m_value;
    }

    inline scalar_operator_iterator &operator+=(const typename std::iterator<std::random_access_iterator_tag, T>::difference_type n) {
        return *this;
    }

    inline scalar_operator_iterator operator+(const typename std::iterator<std::random_access_iterator_tag, T>::difference_type n) const {
        return *this;
    }

    inline scalar_operator_iterator &operator-=(const typename std::iterator<std::random_access_iterator_tag, T>::difference_type n) {
        return *this;
    }

    inline scalar_operator_iterator operator-(const typename std::iterator<std::random_access_iterator_tag, T>::difference_type n) const {
        return *this;
    }

    inline scalar_operator_iterator &operator++() {
        return *this;
    }

    inline scalar_operator_iterator operator++(int) {
        return *this;
    }

    inline scalar_operator_iterator &operator--() {
         return *this;
    }

    inline scalar_operator_iterator operator--(int) {
        return *this;
    }

    inline bool operator==(const scalar_operator_iterator &rhs) const {
        return false;
    }

    inline bool operator!=(const scalar_operator_iterator &rhs) const {
        return !operator==(rhs);
    }

    friend inline ptrdiff_t operator-(const scalar_operator_iterator &lhs, const scalar_operator_iterator &rhs) {
        return 1;
    }
};

template< typename T >
struct scalar_operator_result_type {
    typedef T result_type;
};

template< typename T >
class scalar_operator : public operand< scalar_operator< T >, scalar_operator_iterator< T >, typename scalar_operator_result_type< T >::result_type > {
public:
    typedef typename scalar_operator_result_type< T >::result_type result_type;
    static const bool NA = false;

public:
    typedef scalar_operator_iterator< T > const_iterator;
    typedef const_iterator iterator;

private:
    T m_value;
public:
    scalar_operator(const T &val) :
        m_value(val) {}

    uint64_t length() const {return 1;}
    const_iterator begin() const {return const_iterator(m_value);}
    const_iterator end() const {return const_iterator(m_value);}
};

struct make_scalar_operator {
    template< typename T >
    scalar_operator< T > operator()(const T &obj) {
        return scalar_operator< T >(obj);
    }
};

} // namespace RcppHoney

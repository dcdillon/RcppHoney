#pragma once

#include <Rcpp/r/headers.h>

namespace RcppHoney {
namespace traits {

typedef struct {char a[1];} CTYPE_CHAR;
typedef struct {char a[2];} CTYPE_SHORT;
typedef struct {char a[3];} CTYPE_INT;
typedef struct {char a[4];} CTYPE_LONG;
typedef struct {char a[6];} CTYPE_FLOAT;
typedef struct {char a[7];} CTYPE_DOUBLE;
typedef struct {char a[8];} CTYPE_LONG_DOUBLE;
typedef struct {char a[9];} CTYPE_STRING;
typedef struct {char a[10];} CTYPE_UNSIGNED_CHAR;
typedef struct {char a[11];} CTYPE_UNSIGNED_SHORT;
typedef struct {char a[12];} CTYPE_UNSIGNED_INT;
typedef struct {char a[13];} CTYPE_UNSIGNED_LONG;
typedef struct {char a[15];} CTYPE_RCOMPLEX;
typedef struct {char a[128];} CTYPE_UNKNOWN;

template< std::size_t I >
struct ctype_helper { static const bool value = false; };

template<>
struct ctype_helper< sizeof(CTYPE_CHAR) > { typedef char type; static const bool value = true; };

template<>
struct ctype_helper< sizeof(CTYPE_SHORT) > { typedef short type; static const bool value = true; };

template<>
struct ctype_helper< sizeof(CTYPE_INT) > { typedef int type; static const bool value = true; };

template<>
struct ctype_helper< sizeof(CTYPE_LONG) > { typedef long type; static const bool value = true; };

template<>
struct ctype_helper< sizeof(CTYPE_FLOAT) > { typedef float type; static const bool value = true; };

template<>
struct ctype_helper< sizeof(CTYPE_DOUBLE) > { typedef double type; static const bool value = true; };

template<>
struct ctype_helper< sizeof(CTYPE_LONG_DOUBLE) > { typedef long double type; static const bool value = true; };

template<>
struct ctype_helper< sizeof(CTYPE_STRING) > { typedef std::string type; static const bool value = true; };

template<>
struct ctype_helper< sizeof(CTYPE_UNSIGNED_CHAR) > { typedef unsigned char type; static const bool value = true; };

template<>
struct ctype_helper< sizeof(CTYPE_UNSIGNED_SHORT) > { typedef unsigned short type; static const bool value = true; };

template<>
struct ctype_helper< sizeof(CTYPE_UNSIGNED_INT) > { typedef unsigned int type; static const bool value = true; };

template<>
struct ctype_helper< sizeof(CTYPE_UNSIGNED_LONG) > { typedef unsigned long type; static const bool value = true; };

template<>
struct ctype_helper< sizeof(CTYPE_RCOMPLEX) > { typedef Rcomplex type; static const bool value = true; };

template< typename T >
struct ctype
{
    static CTYPE_CHAR test(const char &);
    static CTYPE_SHORT test(const short &);
    static CTYPE_INT test(const int &);
    static CTYPE_LONG test(const long &);
    static CTYPE_FLOAT test(const float &);
    static CTYPE_DOUBLE test(const double &);
    static CTYPE_LONG_DOUBLE test(const long double &);
    static CTYPE_STRING test(const std::string &);
    static CTYPE_UNSIGNED_CHAR test(const unsigned char &);
    static CTYPE_UNSIGNED_SHORT test(const unsigned short &);
    static CTYPE_UNSIGNED_INT test(const unsigned int &);
    static CTYPE_UNSIGNED_LONG test(const unsigned long &);
    static CTYPE_RCOMPLEX test(const Rcomplex &);
    static CTYPE_UNKNOWN test(...);

    static T make();

    typedef typename ctype_helper< sizeof(test(make())) >::type type;
};

template< typename T >
struct decays_to_ctype
{
    static CTYPE_CHAR test(const char &);
    static CTYPE_SHORT test(const short &);
    static CTYPE_INT test(const int &);
    static CTYPE_LONG test(const long &);
    static CTYPE_FLOAT test(const float &);
    static CTYPE_DOUBLE test(const double &);
    static CTYPE_LONG_DOUBLE test(const long double &);
    static CTYPE_STRING test(const std::string &);
    static CTYPE_UNSIGNED_CHAR test(const unsigned char &);
    static CTYPE_UNSIGNED_SHORT test(const unsigned short &);
    static CTYPE_UNSIGNED_INT test(const unsigned int &);
    static CTYPE_UNSIGNED_LONG test(const unsigned long &);
    static CTYPE_RCOMPLEX test(const Rcomplex &);
    static CTYPE_UNKNOWN test(...);

    static T make();

    static const bool value = ctype_helper< sizeof(test(make())) >::value;
};

} // namespace traits
} // namespace RcppHoney

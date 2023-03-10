// Copyright 2023 Matt Borland
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHARCONV_DETAIL_BIT_LAYOUTS_HPP
#define BOOST_CHARCONV_DETAIL_BIT_LAYOUTS_HPP

#include <boost/charconv/detail/config.hpp>
#include <cstdint>
#include <cfloat>

// Layouts of floating point types as specified by IEEE 754

namespace boost { namespace charconv { namespace detail {

struct IEEEf2bits
{
#if BOOST_CHARCONV_ENDIAN_LITTLE_BYTE
    std::uint32_t mantissa : 23;
    std::uint32_t exponent : 8;
    std::uint32_t sign : 1;
#else // Big endian
    std::uint32_t sign : 1;
    std::uint32_t exponent : 8;
    std::uint32_t mantissa : 23;
#endif 
};

struct IEEEd2bits
{
#if BOOST_CHARCONV_ENDIAN_LITTLE_BYTE
    std::uint32_t mantissa_l : 32;
    std::uint32_t mantissa_h : 20;
    std::uint32_t exponent : 11;
    std::uint32_t sign : 1;
#else // Big endian
    std::uint32_t sign : 1;
    std::uint32_t exponent : 11;
    std::uint32_t mantissa_h : 20;
    std::uint32_t mantissa_l : 32;
#endif
};

// 80 bit long double (e.g. x86-64)
#if LDBL_MANT_DIG == 64 && LDBL_MAX_EXP == 16384

struct IEEEl2bits
{
#if BOOST_CHARCONV_ENDIAN_LITTLE_BYTE
    std::uint32_t mantissa_l : 32;
    std::uint32_t mantissa_h : 32;
    std::uint32_t exponent : 15;
    std::uint32_t sign : 1;
    std::uint32_t pad : 32;
#else // Big endian
    std::uint32_t pad : 32;
    std::uint32_t sign : 1;
    std::uint32_t exponent : 15;
    std::uint32_t mantissa_h : 32;
    std::uint32_t mantissa_l : 32;
#endif
};

#define BOOST_CHARCONV_LDBL_BITS 80

// 128 bit long double (e.g. s390x, ppcle64)
#elif LDBL_MANT_DIG == 113 && LDBL_MAX_EXP == 16384

struct IEEEl2bits
{
#if BOOST_CHARCONV_ENDIAN_LITTLE_BYTE
    std::uint64_t mantissa_l : 64;
    std::uint64_t mantissa_h : 48;
    std::uint32_t exponent : 15;
    std::uint32_t sign : 1;
#else // Big endian
    std::uint32_t sign : 1;
    std::uint32_t exponent : 15;
    std::uint64_t mantissa_h : 48;
    std::uint64_t mantissa_l : 64;
#endif
};

#define BOOST_CHARCONV_LDBL_BITS 128

// 64 bit long double (double == long double on ARM)
#elif LDBL_MANT_DIG == 53 && LDBL_MAX_EXP == 1024

struct IEEEl2bits
{
#if BOOST_CHARCONV_ENDIAN_LITTLE_BYTE
    std::uint32_t mantissa_l : 32;
    std::uint32_t mantissa_h : 20;
    std::uint32_t exponent : 11;
    std::uint32_t sign : 1;
#else // Big endian
    std::uint32_t sign : 1;
    std::uint32_t exponent : 11;
    std::uint32_t mantissa_h : 20;
    std::uint32_t mantissa_l : 32;
#endif
};

#define BOOST_CHARCONV_LDBL_BITS 64

#else // Unsupported long double representation
#  define BOOST_MATH_UNSUPPORTED_LONG_DOUBLE
#endif

}}} // Namespaces

#endif // BOOST_CHARCONV_DETAIL_BIT_LAYOUTS_HPP

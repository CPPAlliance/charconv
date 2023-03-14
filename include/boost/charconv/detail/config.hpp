// Copyright 2023 Matt Borland
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHARCONV_DETAIL_CONFIG_HPP
#define BOOST_CHARCONV_DETAIL_CONFIG_HPP

#include <boost/config.hpp>

// TODO: BOOST_ASSERT is currently unused. 
// Once library is complete remove this block, and Boost.Assert from the CML if still unused.
#ifndef BOOST_CHARCONV_STANDALONE
#  include <boost/assert.hpp>
#  define BOOST_CHARCONV_ASSERT(expr) BOOST_ASSERT(expr)
#  define BOOST_CHARCONV_ASSERT_MSG(expr, msg) BOOST_ASSERT_MSG(expr, msg)
#else // Use plain asserts
#  include <cassert>
#  define BOOST_CHARCONV_ASSERT(expr) assert(expr)
#  define BOOST_CHARCONV_ASSERT_MSG(expr, msg) assert((expr)&&(msg))
#endif

// Use 128 bit integers and supress warnings for using extensions
#if defined(BOOST_HAS_INT128)
#  define BOOST_CHARCONV_HAS_INT128
#  define BOOST_CHARCONV_INT128_MAX  (boost::int128_type)(((boost::uint128_type) 1 << 127) - 1)
#  define BOOST_CHARCONV_INT128_MIN  (-BOOST_CHARCONV_INT128_MAX - 1)
#  define BOOST_CHARCONV_UINT128_MAX ((2 * (boost::uint128_type) BOOST_CHARCONV_INT128_MAX) + 1)
#endif

#ifndef BOOST_NO_CXX14_CONSTEXPR
#  define BOOST_CHARCONV_CXX14_CONSTEXPR BOOST_CXX14_CONSTEXPR
#else
#  define BOOST_CHARCONV_CXX14_CONSTEXPR inline
#endif

#if defined(__GNUC__) && __GNUC__ == 5
#  define BOOST_CHARCONV_GCC5_CONSTEXPR inline
#else
#  define BOOST_CHARCONV_GCC5_CONSTEXPR BOOST_CHARCONV_CXX14_CONSTEXPR
#endif

// Determine endianness
#if defined(_WIN32)

#define BOOST_CHARCONV_ENDIAN_BIG_BYTE 0
#define BOOST_CHARCONV_ENDIAN_LITTLE_BYTE 1

#elif defined(__BYTE_ORDER__)

#define BOOST_CHARCONV_ENDIAN_BIG_BYTE (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define BOOST_CHARCONV_ENDIAN_LITTLE_BYTE (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

#else

#error Could not determine endian type. Please file an issue at https://github.com/cppalliance/charconv with your architecture

#endif // Determine endianness

// Inclue intrinsics if available
#if defined(_MSC_VER)
#  include <intrin.h>
#  if defined(_WIN64)
#    define BOOST_CHARCONV_HAS_MSVC_64BIT_INTRINSICS
#  else
#    define BOOST_CHARCONV_HAS_MSVC_32BIT_INTRINSICS
#  endif
#elif (defined(__x86_64__) || defined(__i386__))
#  include <x86intrin.h>
#  define BOOST_CHARCONV_HAS_X86_INTRINSICS
#elif defined(__ARM_NEON__)
#  include <arm_neon.h>
#  define BOOST_CHARCONV_HAS_ARM_INTRINSICS
#else
#  define BOOST_CHARCONV_HAS_NO_INTRINSICS
#endif

static_assert((BOOST_CHARCONV_ENDIAN_BIG_BYTE || BOOST_CHARCONV_ENDIAN_LITTLE_BYTE) &&
             !(BOOST_CHARCONV_ENDIAN_BIG_BYTE && BOOST_CHARCONV_ENDIAN_LITTLE_BYTE),
"Inconsistent endianness detected. Please file an issue at https://github.com/cppalliance/charconv with your architecture");

// Suppress additional buffer overrun check.
// I have no idea why MSVC thinks some functions here are vulnerable to the buffer overrun
// attacks. No, they aren't.
#if defined(__GNUC__) || defined(__clang__)
    #define BOOST_CHARCONV_SAFEBUFFERS
#elif defined(_MSC_VER)
    #define BOOST_CHARCONV_SAFEBUFFERS __declspec(safebuffers)
#else
    #define BOOST_CHARCONV_SAFEBUFFERS
#endif

#if defined(__has_builtin)
    #define BOOST_CHARCONV_HAS_BUILTIN(x) __has_builtin(x)
#else
    #define BOOST_CHARCONV_HAS_BUILTIN(x) false
#endif

#endif // BOOST_CHARCONV_DETAIL_CONFIG_HPP

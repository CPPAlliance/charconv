// Copyright 2023 Matt Borland
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHARCONV_DETAIL_COMPUTE_FLOAT80_HPP
#define BOOST_CHARCONV_DETAIL_COMPUTE_FLOAT80_HPP

#include <boost/charconv/detail/config.hpp>
#include <limits>
#include <cstdint>
#include <cmath>

namespace boost { namespace charconv { namespace detail {

inline long double compute_float80(std::int64_t power, boost::uint128_type i, bool negative, bool& success) noexcept
{
    long double return_val;

    return_val = static_cast<long double>(i * std::pow(10.0L, static_cast<long double>(power)));
    if (std::abs(return_val) > (std::numeric_limits<long double>::max)())
    {
        success = false;
        return negative ? -0.0L : 0.0L;
    }

    return_val = negative ? -return_val : return_val;

    success = true;
    return return_val;
}

}}} // Namespaces

#endif // BOOST_CHARCONV_DETAIL_COMPUTE_FLOAT80_HPP

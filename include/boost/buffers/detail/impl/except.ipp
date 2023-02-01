//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/buffers
//

#ifndef BOOST_BUFFERS_DETAIL_IMPL_EXCEPT_IPP
#define BOOST_BUFFERS_DETAIL_IMPL_EXCEPT_IPP

#include <boost/buffers/detail/except.hpp>
#include <boost/version.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>

namespace boost {
namespace buffers {
namespace detail {

void
throw_invalid_argument(
    source_location const& loc)
{
    throw_exception(
        std::invalid_argument(
            "invalid argument"), loc);
}

void
throw_length_error(
    source_location const& loc)
{
    throw_exception(
        std::length_error(
            "length error"), loc);
}

} // detail
} // buffers
} // boost

#endif

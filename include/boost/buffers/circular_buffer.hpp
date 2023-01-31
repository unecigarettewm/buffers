//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/buffers
//

#ifndef BOOST_BUFFERS_CIRCULAR_BUFFER_HPP
#define BOOST_BUFFERS_CIRCULAR_BUFFER_HPP

#include <boost/buffers/detail/config.hpp>
#include <boost/buffers/buffer_pair.hpp>

namespace boost {
namespace buffers {

class circular_buffer
{
    unsigned char* base_ = nullptr;
    std::size_t cap_ = 0;
    std::size_t in_pos_ = 0;
    std::size_t in_len_ = 0;
    std::size_t out_size_ = 0;

public:
    using const_buffers_type =
        const_buffer_pair;
    using mutable_buffers_type =
        mutable_buffer_pair;

    circular_buffer() = default;
    circular_buffer(
        circular_buffer const&) = default;
    circular_buffer& operator=(
        circular_buffer const&) = default;

    circular_buffer(
        void* base,
        std::size_t capacity) noexcept;

    std::size_t size() const noexcept;
    std::size_t max_size() const noexcept;
    std::size_t capacity() const noexcept;
    const_buffers_type data() const noexcept;
    mutable_buffers_type prepare(std::size_t n);
    void commit(std::size_t n);
    void consume(std::size_t n) noexcept;

    // VFALCO I'm not happy with this
    void uncommit(std::size_t n);
};

} // buffers
} // boost

#endif

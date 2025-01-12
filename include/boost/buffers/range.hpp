//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/buffers
//

#ifndef BOOST_BUFFERS_RANGE_HPP
#define BOOST_BUFFERS_RANGE_HPP

#include <boost/buffers/detail/config.hpp>
#include <boost/buffers/const_buffer.hpp>
#include <boost/buffers/mutable_buffer.hpp>
#include <boost/buffers/type_traits.hpp>
#include <type_traits>

namespace boost {
namespace buffers {
namespace detail {

struct begin_impl
{
    template<class MutableBuffer>
    auto
    operator()(
        MutableBuffer const& b) const noexcept ->
            typename std::enable_if<
            std::is_convertible<
                MutableBuffer const*,
                mutable_buffer const*>::value,
            mutable_buffer const*>::type
    {
        return static_cast<
            mutable_buffer const*>(
                std::addressof(b));
    }

    template<class ConstBuffer>
    auto
    operator()(
        ConstBuffer const& b) const noexcept ->
            typename std::enable_if<
            std::is_convertible<
                ConstBuffer const*,
                const_buffer const*>::value,
            const_buffer const*>::type
    {
        return static_cast<
            const_buffer const*>(
                std::addressof(b));
    }

    template<class BufferSequence>
    auto
    operator()(
        BufferSequence& bs) const noexcept ->
            typename std::enable_if<
            ! std::is_convertible<
                BufferSequence const*,
                const_buffer const*>::value &&
            ! std::is_convertible<
                BufferSequence const*,
                mutable_buffer const*>::value,
            decltype(bs.begin())>::type
    {
        return bs.begin();
    }

    template<class BufferSequence>
    auto
    operator()(
        BufferSequence const& bs) const noexcept ->
            typename std::enable_if<
            ! std::is_convertible<
                BufferSequence const*,
                const_buffer const*>::value &&
            ! std::is_convertible<
                BufferSequence const*,
                mutable_buffer const*>::value,
            decltype(bs.begin())>::type
    {
        return bs.begin();
    }
};

struct end_impl
{
    template<class MutableBuffer>
    auto
    operator()(
        MutableBuffer const& b) const noexcept ->
            typename std::enable_if<
            std::is_convertible<
                MutableBuffer const*,
                mutable_buffer const*>::value,
            mutable_buffer const*>::type
    {
        return static_cast<
            mutable_buffer const*>(
                std::addressof(b)) + 1;
    }

    template<class ConstBuffer>
    auto
    operator()(
        ConstBuffer const& b) const noexcept ->
            typename std::enable_if<
            std::is_convertible<
                ConstBuffer const*,
                const_buffer const*>::value,
            const_buffer const*>::type
    {
        return static_cast<
            const_buffer const*>(
                std::addressof(b)) + 1;
    }

    template<class BufferSequence>
    auto
    operator()(
        BufferSequence& bs) const noexcept ->
            typename std::enable_if<
            ! std::is_convertible<
                BufferSequence const*,
                const_buffer const*>::value &&
            ! std::is_convertible<
                BufferSequence const*,
                mutable_buffer const*>::value,
            decltype(bs.end())>::type
    {
        return bs.end();
    }

    template<class BufferSequence>
    auto
    operator()(
        BufferSequence const& bs) const noexcept ->
            typename std::enable_if<
            ! std::is_convertible<
                BufferSequence const*,
                const_buffer const*>::value &&
            ! std::is_convertible<
                BufferSequence const*,
                mutable_buffer const*>::value,
            decltype(bs.end())>::type
    {
        return bs.end();
    }
};

} // detail

/** Return an iterator to the beginning of the buffer sequence.
*/
constexpr detail::begin_impl begin{};

/** Return an iterator to the end of the buffer sequence.
*/
constexpr detail::end_impl end{};

//------------------------------------------------

namespace detail {

template<class T>
class iter_range
{
    using begin_type = decltype(
        buffers::begin(std::declval<T&>()));
    using end_type = decltype(
        buffers::end(std::declval<T&>()));

    begin_type begin_;
    end_type end_;

public:
    iter_range(T& t) noexcept
        : begin_(buffers::begin(t))
        , end_(buffers::end(t))
    {
    }

    begin_type
    begin() const noexcept
    {
        return begin_;
    }

    end_type
    end() const noexcept
    {
        return end_;
    }
};

struct range_impl
{
    template<class BufferSequence>
    auto
    operator()(
        BufferSequence&& bs) const noexcept ->
            iter_range<typename
                std::remove_reference<
                    BufferSequence>::type>
    {
        return { bs };
    }
};

} // detail

/** Return a range representing the buffer sequence.
*/
constexpr detail::range_impl range{};

} // buffers
} // boost

#endif

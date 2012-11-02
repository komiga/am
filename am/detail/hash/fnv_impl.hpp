/**
@file detail/hash/fnv_impl.hpp
@brief FNV hash and variations (implementations).

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
Although the AM implementations are under the MIT license, the FNV algorithms themselves are in the public domain and no copyright is claimed on them.
*/

#ifndef AM_DETAIL_HASH_FNV_IMPL_HPP_
#define AM_DETAIL_HASH_FNV_IMPL_HPP_

#include "../../config.hpp"

#include <algorithm>

namespace am {
namespace detail {
namespace hash {

/** @cond INTERNAL */

namespace {
template<::am::hash::HashSize S> struct fnv_internals;

template<> struct fnv_internals<::am::hash::HashSize::HS32> {
	typedef uint32_t value_type;
	static constexpr value_type prime=0x01000193;
	static constexpr value_type offset_basis=0x811c9dc5;
};

template<> struct fnv_internals<::am::hash::HashSize::HS64> {
	typedef uint64_t value_type;
	static constexpr value_type prime=0x00000100000001b3;
	static constexpr value_type offset_basis=0xcbf29ce484222325;
};
} // anonymous namespace

template<::am::hash::HashSize S>
struct fnv0_impl {
	typedef fnv_internals<S> internals;
	typedef typename internals::value_type value_type;

	static value_type calc(uint8_t const* const data, std::size_t const size) {
		value_type x=0x00;
		std::for_each(data, data+size, [&x](uint8_t const byte) {
			x*=internals::prime;
			x^=byte;
		});
		return x;
	}
};

template<::am::hash::HashSize S>
struct fnv1_impl {
	typedef fnv_internals<S> internals;
	typedef typename internals::value_type value_type;

	static value_type calc(uint8_t const* const data, std::size_t const size) {
		value_type x=internals::offset_basis;
		std::for_each(data, data+size, [&x](uint8_t const byte) {
			x*=internals::prime;
			x^=byte;
		});
		return x;
	}
};

template<::am::hash::HashSize S>
struct fnv1a_impl {
	typedef fnv_internals<S> internals;
	typedef typename internals::value_type value_type;

	static value_type calc(uint8_t const* const data, std::size_t const size) {
		value_type x=internals::offset_basis;
		std::for_each(data, data+size, [&x](uint8_t const byte) {
			x^=byte;
			x*=internals::prime;
		});
		return x;
	}
};

/** @endcond */ // INTERNAL

} // namespace hash
} // namespace detail
} // namespace am

#endif // AM_DETAIL_HASH_FNV_IMPL_HPP_

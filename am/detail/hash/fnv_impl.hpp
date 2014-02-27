/**
@file detail/hash/fnv_impl.hpp
@brief FNV (implementation).

@author Timothy Howard
@copyright 2012-2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
Although the AM implementations are under the MIT license,
the FNV algorithms themselves are in the public domain and
no copyright is claimed on them.
*/

#ifndef AM_DETAIL_HASH_FNV_IMPL_HPP_
#define AM_DETAIL_HASH_FNV_IMPL_HPP_

#include "../../config.hpp"

#include <algorithm>

namespace am {
namespace detail {
namespace hash {

/** @cond INTERNAL */

template<
	::am::hash::HashLength L
>
using fnv_hash_type = ::am::hash::common_hash_type<L>;

namespace {
template<
	::am::hash::HashLength L
>
struct fnv_internals;

template<>
struct fnv_internals< ::am::hash::HashLength::HL32> {
	static AM_CONSTEXPR uint32_t const prime = 0x01000193;
	static AM_CONSTEXPR uint32_t const offset_basis = 0x811c9dc5;
};

template<>
struct fnv_internals< ::am::hash::HashLength::HL64> {
	static AM_CONSTEXPR uint64_t const prime = 0x00000100000001b3;
	static AM_CONSTEXPR uint64_t const offset_basis = 0xcbf29ce484222325;
};

template<
	::am::hash::HashLength L
>
struct fnv0_internals {
	static AM_CONSTEXPR fnv_hash_type<L> const prime = fnv_internals<L>::prime;
	static AM_CONSTEXPR fnv_hash_type<L> const offset_basis = 0x00;
};

} // anonymous namespace

template<
	::am::hash::HashLength L
>
struct fnv0_impl {
	using internals = fnv0_internals<L>;
	using hash_type = fnv_hash_type<L>;

	static hash_type
	calc(
		uint8_t const* const data,
		std::size_t const size
	) {
		hash_type x = internals::offset_basis;
		std::for_each(
			data, data + size,
			[&x](uint8_t const byte) {
				x *= internals::prime;
				x ^= byte;
			}
		);
		return x;
	}

	static AM_CONSTEXPR hash_type
	calc_c_seq(
		char const* const data,
		std::size_t const size,
		std::size_t const index,
		hash_type const value
	) {
		return (index < size)
			? calc_c_seq(
				data, size,
				index + 1u,
				(value * internals::prime) ^ data[index]
			)
			: value
		;
	}
};

template<
	::am::hash::HashLength L
>
struct fnv1_impl {
	using internals = fnv_internals<L>;
	using hash_type = fnv_hash_type<L>;

	static hash_type
	calc(
		uint8_t const* const data,
		std::size_t const size
	) {
		hash_type x = internals::offset_basis;
		std::for_each(
			data, data + size,
			[&x](uint8_t const byte) {
				x *= internals::prime;
				x ^= byte;
			}
		);
		return x;
	}

	static AM_CONSTEXPR hash_type
	calc_c_seq(
		char const* const data,
		std::size_t const size,
		std::size_t const index,
		hash_type const value
	) {
		return (index < size)
			? calc_c_seq(
				data, size,
				index + 1u,
				(value * internals::prime) ^ data[index]
			)
			: value
		;
	}
};

template<
	::am::hash::HashLength L
>
struct fnv1a_impl {
	using internals = fnv_internals<L>;
	using hash_type = fnv_hash_type<L>;

	static hash_type
	calc(
		uint8_t const* const data,
		std::size_t const size
	) {
		hash_type x = internals::offset_basis;
		std::for_each(
			data, data+size,
			[&x](uint8_t const byte) {
				x ^= byte;
				x *= internals::prime;
			}
		);
		return x;
	}

	static AM_CONSTEXPR hash_type
	calc_c_seq(
		char const* const data,
		std::size_t const size,
		std::size_t const index,
		hash_type const value
	) {
		return (index < size)
			? calc_c_seq(
				data, size,
				index + 1u,
				(value ^ data[index]) * internals::prime
			)
			: value
		;
	}
};

template<
	class Impl
>
static AM_CONSTEXPR typename Impl::hash_type
calc_c_adaptor(
	char const* const data,
	std::size_t const size
) {
	return Impl::calc_c_seq(
		data,
		size,
		0u,
		Impl::internals::offset_basis
	);
}

/** @endcond */ // INTERNAL

} // namespace hash
} // namespace detail
} // namespace am

#endif // AM_DETAIL_HASH_FNV_IMPL_HPP_

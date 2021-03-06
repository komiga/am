/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief FNV (implementation).
Although the AM implementations are under the MIT license,
the FNV algorithms themselves are in the public domain and
no copyright is claimed on them.
*/

#pragma once

#include "../../config.hpp"
#include "../../hash/common.hpp"

namespace am {
namespace detail {
namespace hash {

/** @cond INTERNAL */

#define AM_HASH_FNV_RESTRICT_LENGTH(hash_length)		\
	AM_STATIC_ASSERT(									\
		::am::hash::HashLength::HL32 <= hash_length &&	\
		::am::hash::HashLength::HL64 >= hash_length,	\
		"FNV is not implemented for hash lengths"		\
		" less than 32 bits or greater than 64 bits"	\
	)

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
	static constexpr uint32_t const prime = 0x01000193;
	static constexpr uint32_t const offset_basis = 0x811c9dc5;
};

template<>
struct fnv_internals< ::am::hash::HashLength::HL64> {
	static constexpr uint64_t const prime = 0x00000100000001b3;
	static constexpr uint64_t const offset_basis = 0xcbf29ce484222325;
};

template<
	::am::hash::HashLength L
>
struct fnv0_internals {
	static constexpr fnv_hash_type<L> const prime = fnv_internals<L>::prime;
	static constexpr fnv_hash_type<L> const offset_basis = 0;
};

template<
	::am::hash::HashLength L
>
struct fnv_state {
	fnv_hash_type<L> value;
	unsigned size;
};

} // anonymous namespace

template<
	::am::hash::HashLength L,
	class Internals,
	class Impl
>
struct fnv_shared_impl {
	AM_HASH_FNV_RESTRICT_LENGTH(L);

	using internals = Internals;
	using hash_type = fnv_hash_type<L>;
	using state_type = fnv_state<L>;

	static void
	state_init(state_type& s) {
		s.value = internals::offset_basis;
		s.size = 0;
	}

	static hash_type
	state_value(state_type const& s) {
		return s.value;
	}

	static unsigned
	state_size(state_type const& s) {
		return s.size;
	}

	static inline hash_type
	calc(
		uint8_t const* const data,
		unsigned const size
	) {
		state_type s;
		state_init(s);
		Impl::state_add(s, data, size);
		return state_value(s);
	}

	static constexpr hash_type
	calc_ce_seq(
		char const* const data,
		unsigned const size
	) {
		return Impl::calc_ce_seq(data, size, 0, internals::offset_basis);
	}
};

template<
	::am::hash::HashLength L
>
struct fnv0_impl
	: fnv_shared_impl<L, fnv0_internals<L>, fnv0_impl<L>>
{
	static constexpr auto const hash_length = L;
	using internals = fnv0_internals<L>;
	using hash_type = fnv_hash_type<L>;
	using state_type = fnv_state<L>;
	using fnv_shared_impl<L, internals, fnv0_impl<L>>::calc_ce_seq;

	static void
	state_add(
		state_type& s,
		uint8_t const* const data,
		unsigned const size
	) {
		for (unsigned i = 0; i < size; ++i) {
			s.value *= internals::prime;
			s.value ^= data[i];
		}
		s.size += size;
	}

	static constexpr hash_type
	calc_ce_seq(
		char const* const data,
		unsigned const size,
		unsigned const index,
		hash_type const value
	) {
		return (index < size)
			? calc_ce_seq(
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
struct fnv1_impl
	: fnv_shared_impl<L, fnv_internals<L>, fnv1_impl<L>>
{
	static constexpr auto const hash_length = L;
	using internals = fnv_internals<L>;
	using hash_type = fnv_hash_type<L>;
	using state_type = fnv_state<L>;
	using fnv_shared_impl<L, internals, fnv1_impl<L>>::calc_ce_seq;

	static void
	state_add(
		state_type& s,
		uint8_t const* const data,
		unsigned const size
	) {
		for (unsigned i = 0; i < size; ++i) {
			s.value *= internals::prime;
			s.value ^= data[i];
		}
		s.size += size;
	}

	static constexpr hash_type
	calc_ce_seq(
		char const* const data,
		unsigned const size,
		unsigned const index,
		hash_type const value
	) {
		return (index < size)
			? calc_ce_seq(
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
struct fnv1a_impl
	: fnv_shared_impl<L, fnv_internals<L>, fnv1a_impl<L>>
{
	static constexpr auto const hash_length = L;
	using internals = fnv_internals<L>;
	using hash_type = fnv_hash_type<L>;
	using state_type = fnv_state<L>;
	using fnv_shared_impl<L, internals, fnv1a_impl<L>>::calc_ce_seq;

	static void
	state_add(
		state_type& s,
		uint8_t const* const data,
		unsigned const size
	) {
		for (unsigned i = 0; i < size; ++i) {
			s.value ^= data[i];
			s.value *= internals::prime;
		}
		s.size += size;
	}

	static constexpr hash_type
	calc_ce_seq(
		char const* const data,
		unsigned const size,
		unsigned const index,
		hash_type const value
	) {
		return (index < size)
			? calc_ce_seq(
				data, size,
				index + 1u,
				(value ^ data[index]) * internals::prime
			)
			: value
		;
	}
};

/** @endcond */ // INTERNAL

} // namespace hash
} // namespace detail

/** @cond INTERNAL */
namespace hash {

template<HashLength L>
struct impl_is_stateful<detail::hash::fnv0_impl<L>> {
	static constexpr bool const value = true;
};
template<HashLength L>
struct impl_is_stateful<detail::hash::fnv1_impl<L>> {
	static constexpr bool const value = true;
};
template<HashLength L>
struct impl_is_stateful<detail::hash::fnv1a_impl<L>> {
	static constexpr bool const value = true;
};

} // namespace hash
/** @endcond */ // INTERNAL

} // namespace am

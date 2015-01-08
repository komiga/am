/**
@file
@brief FNV.

@author Timothy Howard
@copyright 2012-2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include "../config.hpp"
#include "./common.hpp"
#include "../detail/hash/fnv_impl.hpp"

namespace am {
namespace hash {

/**
	@addtogroup hash
	@{
*/
/**
	@defgroup fnv FNV
	@details
	The <strong>Fowler-Noll-Vo</strong> (<strong>FNV</strong>)
	hashing algorithm has three popular versions:

	- <strong>FNV-0</strong>:
	  the first FNV (using an @c offset_basis of @c 0 -- given a
	  0-size input, it will return @c 0).
	- <strong>FNV-1</strong>:
	  the same as FNV-0, but with an arbitrary non-zero
	  @c offset_basis (0-size input will yield a non-zero hash).
	- <strong>FNV-1a</strong>:
	  an alternate version of FNV-1 with the multiplication and XOR
	  operations swapped; this alternate version has much better
	  avalanche characteristics.

	FNV-1a is the recommended version.

	@remarks Only lengths @c HashLength::HL32 and @c HL64 are supplied.

	@note Although the AM implementations are under the MIT license,
	the FNV algorithms themselves are in the public domain and no
	copyright is claimed on them.
	@{
*/

/**
	FNV-0 hash implementation.
*/
template<HashLength L>
using fnv0 = detail::hash::fnv0_impl<L>;

/**
	FNV-1 hash implementation.
*/
template<HashLength L>
using fnv1 = detail::hash::fnv1_impl<L>;

/**
	FNV-1a hash implementation.
*/
template<HashLength L>
using fnv1a = detail::hash::fnv1a_impl<L>;

/**
	FNV-0 hash combiner.
*/
template<HashLength L>
using fnv0_combiner = hash::generic_combiner<hash::fnv0<L>>;

/**
	FNV-1 hash combiner.
*/
template<HashLength L>
using fnv1_combiner = hash::generic_combiner<hash::fnv1<L>>;

/**
	FNV-1a hash combiner.
*/
template<HashLength L>
using fnv1a_combiner = hash::generic_combiner<hash::fnv1a<L>>;

/** @} */ // end of doc-group fnv
/** @} */ // end of doc-group hash

namespace literals {

// Why, Doxygen, why?
/**
	@addtogroup hash
	@{
*/
/**
	@addtogroup literals
	@{
*/

/**
	32-bit FNV-1a literal.

	@returns The FNV-1a hash of the given string.
	@param data C-string.
	@param size Size in bytes of @a data.
*/
inline constexpr typename hash::fnv1a<HashLength::HL32>::hash_type
operator"" _fnv1a_32(
	char const* const data,
	std::size_t const size
) {
	return hash::calc_ce<hash::fnv1a<HashLength::HL32>>(data, size);
}

/**
	64-bit FNV-1a literal.

	@returns The FNV-1a hash of the given string.
	@param data C-string.
	@param size Size in bytes of @a data.
*/
inline constexpr typename hash::fnv1a<HashLength::HL64>::hash_type
operator"" _fnv1a_64(
	char const* const data,
	std::size_t const size
) {
	return hash::calc_ce<hash::fnv1a<HashLength::HL64>>(data, size);
}

/** @} */ // end of doc-group literals
/** @} */ // end of doc-group hash

} // namespace literals
} // namespace hash
} // namespace am

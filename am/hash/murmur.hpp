/**
@file hash/murmur.hpp
@brief Murmur.

@author Timothy Howard
@copyright 2012-2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include "../config.hpp"
#include "./common.hpp"
#include "../detail/hash/murmur_impl.hpp"

namespace am {
namespace hash {

/**
	@addtogroup hash
	@{
*/
/**
	@defgroup murmur Murmur
	@details
	The Murmur hashes are general-purpose public domain algorithms
	created by Austin Appleby.

	AM implements <strong>MurmurHash2</strong> (32-bit and both 64-bit
	versions) and <strong>MurmurHash3</strong> (32-bit).

	There are a few quirks of the algorithms and of the AM
	implementations:

	- MurmurHash2 is not portable; it will give different output on
	  different system endians.
	- The two 64-bit MurmurHash2 versions do not produce the same
	  output.
	- The original MurmurHash2 will be used for @c murmur2<HL32>, and
	  MurmurHash64A will be used for @c murmur2<HL64>;
	  see @c murmur2_64b for MurmurHash64B (which only deals
	  in @c HL64).

	@remarks Only lengths @c HashLength::HL32 and @c HashLength::HL64
	are supplied for @c murmur2; only @c HashLength::HL32 is supplied
	for @c murmur3.

	@note Although the AM implementations are under the MIT license,
	the Murmur algorithms themselves are in the public domain and no
	copyright is claimed on them.
	@{
*/

/**
	MurmurHash2 & MurmurHash64A hash implementation.

	@note Uses MurmurHash2 for 32-bit hash length and MurmurHash64A
	(64-bit MurmurHash2 for x64 processors) for 64-bit hash length.
*/
template<HashLength L>
using murmur2 = detail::hash::murmur2_impl<L>;

/**
	MurmurHash64B hash implementation.

	@note Alternate 64-bit MurmurHash2 for x86 processors.
*/
using murmur2_64b = detail::hash::murmur2_64b_impl<am::hash::HashLength::HL64>;

/**
	MurmurHash3 hash implementation.
*/
using murmur3 = detail::hash::murmur3_impl<am::hash::HashLength::HL32>;

/** @} */ // end of doc-group murmur
/** @} */ // end of doc-group hash

} // namespace hash
} // namespace am

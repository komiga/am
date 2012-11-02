/**
@file hash/common.hpp
@brief Common hashy things.

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_HASH_COMMON_HPP_
#define AM_HASH_COMMON_HPP_

#include "../config.hpp"

namespace am {
namespace hash {

/**
	@addtogroup hash
	@{
*/

/**
	Hash lengths.
*/
enum HashLength {
	/** 8-bit hash length. */
	HL8=1,
	/** 32-bit hash length. */
	HL32=4,
	/** 64-bit hash length. */
	HL64=8,
	/** 128-bit hash length. */
	HL128=16,
	/** 256-bit hash length. */
	HL256=32,
	/** 512-bit hash length. */
	HL512=64,
	/** 1024-bit hash length. */
	HL1024=128
};

/** @cond INTERNAL */
template<HashLength L> struct common_hash_type_impl {
	typedef struct {
		union {
			uint8_t data[static_cast<unsigned int>(L)];
			uint32_t chunks[static_cast<unsigned int>(L)>>2];
		};
	} type;
};
template<> struct common_hash_type_impl<HashLength::HL8> {typedef uint8_t type;};
template<> struct common_hash_type_impl<HashLength::HL32> {typedef uint32_t type;};
template<> struct common_hash_type_impl<HashLength::HL64> {typedef uint64_t type;};

template<HashLength L> using common_hash_type=typename common_hash_type_impl<L>::type;
/** @endcond */

/** @} */ // end of doc-group hash

} // namespace hash
} // namespace am

#endif // AM_HASH_COMMON_HPP_

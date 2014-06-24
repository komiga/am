/**
@file hash/common.hpp
@brief Common hashy things.

@author Timothy Howard
@copyright 2012-2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

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
enum HashLength : unsigned {
	/** 8-bit hash length. */
	HL8 = 1u,
	/** 32-bit hash length. */
	HL32 = 4u,
	/** 64-bit hash length. */
	HL64 = 8u,
	/** 128-bit hash length. */
	HL128 = 16u,
	/** 256-bit hash length. */
	HL256 = 32u,
	/** 512-bit hash length. */
	HL512 = 64u,
	/** 1024-bit hash length. */
	HL1024 = 128u
};

/** @cond INTERNAL */
template<
	HashLength L
>
struct common_hash_type_impl {
	struct type {
		union {
			uint8_t data[static_cast<unsigned>(L)];
			uint32_t chunks[static_cast<unsigned>(L) >> 2];
		};
	};
};

template<>
struct common_hash_type_impl<HashLength::HL8> {
	using type = uint8_t;
};
template<>
struct common_hash_type_impl<HashLength::HL32> {
	using type = uint32_t;
};
template<>
struct common_hash_type_impl<HashLength::HL64> {
	using type = uint64_t;
};

template<
	HashLength L
>
using common_hash_type = typename common_hash_type_impl<L>::type;
/** @endcond */

/** @} */ // end of doc-group hash

} // namespace hash
} // namespace am

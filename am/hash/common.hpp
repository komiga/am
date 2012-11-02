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
	Hash sizes.
*/
enum HashSize {
	/** 8-bit hash size. */
	HS8=1,
	/** 32-bit hash size. */
	HS32=4,
	/** 64-bit hash size. */
	HS64=8,
	/** 128-bit hash size. */
	HS128=16,
	/** 256-bit hash size. */
	HS256=32,
	/** 512-bit hash size. */
	HS512=64,
	/** 1024-bit hash size. */
	HS1024=128
};

/** @} */ // end of doc-group hash

} // namespace hash
} // namespace am

#endif // AM_HASH_COMMON_HPP_

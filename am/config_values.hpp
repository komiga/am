/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief Configuration values.
*/

#pragma once

namespace am {

/**
	@addtogroup config
	@{
*/
/**
	@name Linear configuration
	@{
*/

/** Low arithmetic type precision. */
#define AM_PRECISION_LOW	1
/** Medium arithmetic type precision. */
#define AM_PRECISION_MEDIUM	2
/** High arithmetic type precision. */
#define AM_PRECISION_HIGH	3

/** No types. */
#define AM_FLAG_TYPE_NONE	0
/** Floating-point type. */
#define AM_FLAG_TYPE_FLOAT	1 << 0
/** Signed integer type. */
#define AM_FLAG_TYPE_INT	1 << 1
/** Unsigned integer type. */
#define AM_FLAG_TYPE_UINT	1 << 2
/** All types. */
#define AM_FLAG_TYPE_ALL	\
	(AM_FLAG_TYPE_FLOAT | AM_FLAG_TYPE_INT | AM_FLAG_TYPE_UINT)

/** @} */ // end of name-group Linear configuration
/** @} */ // end of doc-group config

} // namespace am
